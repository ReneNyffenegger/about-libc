#include <search.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *tree_root = 0;

typedef struct {
    int         key;
    const char* value;
} item;


static const char* visit_str(VISIT order) {
 //
 // Helper function for visited_node() to
 // show the value of the VISIT enum.
 //
    if (order == preorder ) { return "preorder" ; }
    if (order == postorder) { return "postorder"; }
    if (order == endorder ) { return "endorder" ; }
    if (order == leaf     ) { return "leaf"     ; }
}

static void visited_node(const void* node, VISIT order, int level) {
 //
 // Function to be called when twalk(…) is instructed to
 // walk the tree.
 //
    int i;
    item **val = (item**) node;

    for (i=0; i<level; i++) {
       printf("  ");
    }

    printf("node %s (%x) was visited (%s)\n", (*val) -> value, node, visit_str(order));
}

int compare_item_keys(const void *const item_left, const void *const item_right) {
    return ((item*)item_left)->key - ((item*)item_right)->key;
}

static void insert_item(int k, const char* v) {

    item *i = malloc(sizeof(item));
    i->key   = k;
    i->value = v;

 //
 // Although named tsearch, it insert an item.
 //
    tsearch(i, &tree_root, compare_item_keys);
}

static void find_item(int k) {

 // search
    item **r = tfind(&k, &tree_root, compare_item_keys);

    if (r) {
      printf("%d -> %s\n", k, (*r)->value);
    }
    else {
      printf("%d was not found\n", k);
    }
}

int main(int argc, char **argv) {

    insert_item(4, "four" );
    insert_item(7, "seven");
    insert_item(2, "two"  );
    insert_item(5, "five" );
    insert_item(9, "nine" );
    insert_item(1, "one"  );
    insert_item(8, "eight");
    insert_item(6, "six"  );

    find_item(5);
    find_item(4);
    find_item(3);
    find_item(7);

 //
 // Walk the tree and call visited_node() for nodes being walked.
 //
 // visited_node() is called three times for non-leaf nodes (order = preorder, postorder, endorder),
 // and once for leaf nodes (order=leaf)
 //
    twalk(tree_root, visited_node);

    return 0;
}
