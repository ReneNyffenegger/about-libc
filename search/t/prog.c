#ifdef TQ84_USE_GLIBC
 //
 // Defining _GNU_SOURCE exposes the GNU extension tdestroy(), which is not mentioned
 // or mandated by the Single Unix Specification.
 //
    #define _GNU_SOURCE    // in order to declare tdestroy

    #include <search.h>

 //
 // Because this program uses tq84_tsearch() for tsearch() etc, the
 // following defines route the function call to the glibc version.
 //

    #define tq84_tfind    tfind
    #define tq84_tsearch  tsearch
    #define tq84_tdelete  tdelete
    #define tq84_twalk    twalk
    #define tq84_tdestroy tdestroy
#else
    #include "tq84-tsearch.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

 //
 // This is the struct that defines the data
 // we want to insert into the tree.
 //
 // The key is used to identify a node, IT MUST
 // BE THE FIRST ELEMENT in the struct/data that
 // is inserted into the tree.
 //
typedef struct {
    int         key;
    const char* value;
} item;


 //
 // In order to find elements in the tree, we need to have a
 // function that is able to compare items.
 // The following call-back function is called by the t-search interface
 // whenever it needs to compare to inserted items (or keys).
 //
int compare_item_keys(const void *const item_left, const void *const item_right) {

 //
 // We cast both arguments to an (item*) so that we can access their key element.
 // by returning their difference, we're able to define an ordering among the
 // elements.
 //

    return ((item*)item_left )->key -
           ((item*)item_right)->key;
}


 //
 // Helper function for visited_node() to
 // show the value of the VISIT enum, see below.
 //
static const char* visit_str(VISIT order) {
    if (order == preorder ) { return "preorder" ; }
    if (order == postorder) { return "postorder"; }
    if (order == endorder ) { return "endorder" ; }
    if (order == leaf     ) { return "leaf"     ; }
    return "?";
}


 //
 // We also need a call-back function to be invoked for
 // every node when twalk() is called.
 //
static void visited_node(const void* node, VISIT order, int level) {
 //
 // Function to be called when twalk(…) is instructed to
 // walk the tree.
 //
    int i;

 //
 // The argument node is really a pointer to a pointer
 // to the visited elem.
 // Thus, we cast it in such a pointer to pointer to elem
 // and dereference it once, resulting in a pointer to an
 // element:
 //
    item *item_;
    item_ = * ((item**) node);

 //
 // Print the indentation
 //
    for (i=0; i<level; i++) printf("  ");

 //
 // Print the item's data:
 //
    printf("Item %s (%d) was visited (%s)\n", item_->value, item_->key, visit_str(order));
}

 //
 // We need a variable on which to hinge the tree.
 // A pointer to void is sufficient. It's initialized
 // to NULL so as to indicate that the tree is empty.
 //
void *tree_root = NULL;

 //
 // The function that inserts an item into the tree.
 //
 //
static void insert_item(int k, const char* v) {

 //
 // Create the (new) item
 //
    item *new_item = malloc(sizeof(item));
    new_item->key   = k;
    new_item->value = v;

 //
 // tsearch searches for a node with a specific key.
 // If no such node was found, it inserts it and returns it.
 //
    item **item_in_tree = tq84_tsearch(new_item, &tree_root, compare_item_keys);

    if (*item_in_tree != new_item) {
     //
     // The address of the returned item is different from the
     // item we tried to insert. This means that we have already
     // inserted an item with the same key (which was returned
     // by tsearch)
     //
        printf("Already inserted: %d, overriting\n", k);

     //
     // Because the key was already inserted, we overwrite the
     // already inserted item's value with the new value
     //
      (*item_in_tree)->value = new_item->value;

     //
     // The new item is not needed anymore:
     //
        free(new_item);
    }
}

 //
 // the function that deletes an item from the tree.
 //
static void delete_item(int k) {

    item **item_in_tree;
    item  *item_;

 //
 // first, we try to to find the item that is to be deleted
 //
    if (item_in_tree = tq84_tfind(&k, &tree_root, compare_item_keys)) {

     //
     // The returned item_in_tree (which is acutally a pointer to a pointer to an item)
     // is not NULL. Thus, we have found an item.
     //

     //
     // In order to later free the item (not the node), we save it in
     // item_. It additionally makes it easier to access the data
     // in the struct, if still needed.
     //
     // NOTE WELL, we cannot delete the item here, because it is still
     // needed in the tdelete() call below (or more accuratly in the
     // comparison function that tdelete() calls to compare the items.
     //
        item_ = *item_in_tree;

        printf("Key to delete %d was found, deleting it.\n", k);

     //
     // Delete the node of the item in the tree.
     //
        tq84_tdelete(*item_in_tree, &tree_root, compare_item_keys);

     //
     // And finally free the item.
     //
        free(item_);
    }
    else {
        printf("Key to delete %d was not found\n", k);
    }
}

 //
 // A function that finds an item.
 //
static void find_item(int k) {

 //
 // We call tfind() to search for an item. If the item does
 // not exist, tfind() returns NULL. tsearch() would insert
 // a new item in such a case…
 //
    item **item_in_tree = tq84_tfind(&k, &tree_root, compare_item_keys);

    if (item_in_tree) {
        printf("Found %d, value is %s\n", k, (*item_in_tree)->value);
    }
    else {
        printf("Key %d was not found\n", k);
    }
}

 //
 // Used in conjunction with tdestroy()
 //
void free_item(void *node) {
     free( node );
}

int main(int argc, char **argv) {

    insert_item(4, "four" );
    insert_item(7, "seven");
    insert_item(2, "two"  );
    insert_item(5, "five" );

    insert_item(9, "nyne" ); // note the typo
    insert_item(1, "one"  );
    insert_item(8, "eight");
    insert_item(9, "nine" ); // correct nine
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
    tq84_twalk(tree_root, visited_node);

    delete_item(7);
    delete_item(4);
    delete_item(7);  // Cannot delete, was already deleted
    delete_item(3);  // Cannot delete, was not inserted at all

    delete_item(5);
    delete_item(2);
    delete_item(8);
    delete_item(9);
    delete_item(6);

    tq84_twalk(tree_root, visited_node);

    find_item(5);
    find_item(4);
    find_item(3);
    find_item(7);

 //
 // Delete everything that was left in the tree:
 //
    tq84_tdestroy(tree_root, free_item);

    return 0;
}
