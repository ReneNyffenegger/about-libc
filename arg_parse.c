//
//  Adapted from
//    https://www.gnu.org/software/libc/manual/html_node/Argp-Example-4.html#Argp-Example-4
//

#include <stdlib.h>
#include <error.h>
#include <argp.h>

const char *argp_program_version     = "arg-parse 0.99";
const char *argp_program_bug_address = "<bug-me-not@some.address.xyz>";

static char program_documentation[] =
"arg_parse - a program that parses arguments. I won't argue over it's usefulness. \
This text is displayed with --help or -h \
Note, how the text is automatically broken \
\vThis text is displayed *after* the options \
Line breakes can be forced with a\nbackslash n. \
Did it work?";

/* A description of the arguments we accept. */
static char args_doc[] = "ARG1 [STRING...]";

/* Keys for options without short-options. */
#define NSO  1

/* The options we understand. */
static struct argp_option options[] = {
//    Option name    , Arg.   , Options            ,  Doc string for options       , group
// long        short , Name   ,                    ,                               ,
// ----------,-------,--------,--------------------,-------------------------------, ---
  {"foo"     ,  'f'  ,  0     , 0                  , "Do the foo"                  , 0 },
  {"bar"     ,  'b'  ,  0     , OPTION_ALIAS       ,  NULL                         , 0 },
  {"string"  ,  's'  , "STR" , 0                   , "Specify a string"            , 0 },
   // 
  { 0        ,   0   ,  0     , 0                  , "What does this mean?"        , 1 },
  {"num"     ,  'n'  , "NUM"  , OPTION_ARG_OPTIONAL, "a NUMber (default 10)"       , 1 },
  {"no-short",   NSO ,  0     , 0                  , "No short option available"   , 1 },
   //
  { 0 }
};

/* Used by main to communicate with option_callback. */
struct arguments {
  int    foo;                      /* -f */
  char  *arg1;                     /* arg1 */
  char **strings;                  /* [string…] */
  char  *string;                   /* -sSomeString */
  int    repeat_count;             /* count arg to ‘--repeat’ */
  int    no_short_opt;
};

static error_t option_callback (int key, char *arg, struct argp_state *state) {
// This function is called for each option

  // Get 6th paramter of argp_parse
  struct arguments *arguments = state->input;

  switch (key) {

    case 'f': case 'b':
      arguments->foo = 1;
      break;

    case 's':
      arguments->string = arg;
      break;

    case 'r':
      arguments->repeat_count = arg ? atoi (arg) : 10;
      break;

    case NSO:
      arguments->no_short_opt = 1;
      break;

    case ARGP_KEY_NO_ARGS: 
      // no non-option arguments were supplied to the program.
         argp_usage (state);

    case ARGP_KEY_ARG:
      /* Here we know that state->arg_num == 0, since we
         force argument parsing to end before any more arguments can
         get here. */
      arguments->arg1 = arg;

      /* Now we consume all the rest of the arguments.
         state->next is the index in state->argv of the
         next argument to be parsed, which is the first string
         we’re interested in, so we can just use
         &state->argv[state->next] as the value for
         arguments->strings.

         In addition, by setting state->next to the end
         of the arguments, we can force argp to stop parsing here and
         return. */
      arguments->strings = &state->argv[state->next];
      state->next = state->argc;

      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp arg_parser = {
  /* argp_option*  */ options,
  /* argp_parser_t */ option_callback,
  /* const char*   */ args_doc,
  /* const char*   */ program_documentation,
  /* argp_child*   */ NULL,
  /* f-ptr         */ NULL,
  /* const char*   */ NULL
};

int main (int argc, char **argv) {

  int i, j;
  struct arguments arguments;

  // Default values:
  arguments.foo          = 0;
  arguments.string       = "-";
  arguments.repeat_count = 1;
  arguments.no_short_opt = 0;

  // Parse the options. The sixth parameter (arguments)
  // is passed to the call back function »option_callback«
  argp_parse (
       &arg_parser,
       argc,
       argv,
       0,
       0,
       &arguments);


  for (i = 0; i < arguments.repeat_count; i++) {

      printf ("ARG1      : %s\n", arguments.arg1);
      printf ("STRINGS   : ");

      for (j = 0; arguments.strings[j]; j++)
        printf (j == 0 ? "%s" : ", %s", arguments.strings[j]);

      printf ("\n");

      printf("Do the foo: %s\n", arguments.foo ? "yes" : "no");
      printf("String    : %s\n", arguments.string);
      printf("No short  : %s\n", arguments.no_short_opt ? "yes" : "no");

    }

  exit (0);
}
