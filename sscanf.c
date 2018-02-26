#include <stdio.h>
#include <stdlib.h>

int main() {

    int    int_1,  int_2,  int_3;
    char  *str_1, *str_2, *str_3;

    str_1 = malloc(256);
    str_2 = malloc(256);
    str_3 = malloc(256);

    int ret; // Rerturn value: indicates how many percent signs were matched

    ret = sscanf(
        "42",                                       //
        "%d",                                       // Simple case: read an integer
        &int_1                                      //
    );
    printf("ret=%d, a=%d\n", ret, int_1);


    ret = sscanf(
        "  \t  \n 42 \n\t  1111 222, etc. ect.",    // 
        "%d %d %d",                                 // Read three integers, seperated by any amount of whitespace
        &int_1, &int_2, &int_3                      //
    );
    printf("ret=%d, int_1=%d, int_2=%d, int_3=%d\n", ret, int_1, int_2, int_3);


    ret = sscanf(
        "   foo,    bar, \t\n baz.",                // Read three strings, seperated by any amount
        "%s %s %s",                                 // of white space. Note, that the resulting strings
         str_1, str_2, str_3                        // must have been malloc'd
    );
    printf("ret=%d, str_1=%s str_2=%s str_3=%s\n", ret, str_1, str_2, str_3);

    ret = sscanf(
        " 42   Skip-Me  \t  word",                  //
        "%d Skip-Me %s",                            // Skip a fixed word.
         &int_1, str_1                              //
    );
    printf("ret=%d, int_1=%d, str_1=%s\n", ret, int_1, str_1);

    ret = sscanf(
        " 42forty-two ",                            //
        "%d%s",                                     //  Scanning for a number that is adjacent to a string.
        &int_1, str_1                               //
    );
    printf("ret=%d, int_1=%d, str_1=%s\n", ret, int_1, str_1);

    ret = sscanf(
        " abcdefghijklmnopqrustuvwxyz a b",         //
        "%3s%5s%2s",                                // Match exactly 3, 5 and 2 characters, respectively.
        str_1, str_2, str_3                         //
    );
    printf("ret=%d, str_1=%s, str_2=%s, str_3=%s\n", ret, str_1, str_2, str_3);

    ret = sscanf(                                   
        "one two three four five",                  //
        "%s %*s %s %*s %s",                         // Use %* to indicate that the respective scanned element
        str_1, str_2, str_3                         // should be skipped.
    );
    printf("ret=%d, str_1=%s, str_2=%s, str_3=%s\n", ret, str_1, str_2, str_3);



    free(str_1);
    free(str_2);
    free(str_3);

}
