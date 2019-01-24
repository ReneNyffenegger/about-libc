#include <search.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *tree_root = 0;

typedef struct {
    int         key;
    const char* value;
} item;

int compare_item_keys(const void *item_left, const void *item_right) {
    return ((item*)item_left)->key - ((item*)item_right)->key;
}

void insert_item(int k, const char* v) {

    item *i = malloc(sizeof(item));
    i->key   = k;
    i->value = v;

 // insert
    tsearch(i, &tree_root, compare_item_keys);
}

void find_item(int k) {

 // search
    item *r = tfind(&k, &tree_root, compare_item_keys);

    printf("%d -> %s\n", k, (*(item**)r)->value);
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
    find_item(5);

    return 0;
}
