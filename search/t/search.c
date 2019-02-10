// http://gist.githubusercontent.com/kulp/3971591/raw/0320f9052ce4dcbcb9e703eaee969ba48c93c744/tsearch.c
// From Algorithms T and D, Knuth, TAoCP Vol. 3 (6.2.2)

typedef enum {preorder, postorder, endorder, leaf} VISIT;

struct tree {
    // datum must be the first field in struct tree
    const void *datum;
    struct tree *left, *right;
};

static struct tree *null_tree_p = NULL;

typedef int  cmp(const void *key1, const void *key2);
typedef void act(const void *node, VISIT order, int level);
typedef void freer(void *node);

static struct tree **traverse(const void *key, struct tree **rootp, cmp *compar, int create, struct tree **parent) {

 // traverse is guaranteed to return a non-NULL pointer (might be a pointer to NULL)

    struct tree *p;
    int    result;

    if (*rootp == NULL) {

        if (create) {

            struct tree *q = *rootp = malloc(sizeof *q);
            q->left  = q->right = NULL;
            q->datum = key;
            return rootp;

        } else {
            return &null_tree_p;
        }
    }

    p = *rootp;
    result = compar(key, p->datum);

    if (parent) *parent = p;

 // we could easily implement this iteratively as well but let's do it
 // recursively and depend on a smart compiler to use tail recursion
    if (result == 0) {
        return rootp;
    } else if (result < 0) {
        return traverse(key, &p->left , compar, create, parent);
    } else {
        return traverse(key, &p->right, compar, create, parent);
    }
}

void *tfind(const void *key, void *const *rootp, cmp *compar) {
    return *traverse(key, (void*)rootp, compar, 0, NULL);
}

void *tsearch(const void *key, void **rootp, cmp *compar) {
    return *traverse(key, (void*)rootp, compar, 1, NULL);
}

void *tdelete(const void *key, void **rootp, cmp *compar) {
    struct tree  *parent;
    struct tree **q;
    struct tree  *t;
    struct tree **r;
    struct tree **s;

    parent = NULL;
    q = traverse(key, (void*)rootp, compar, 0, &parent);


    if (!(*q)->datum) return NULL;

    t = *q;
    do {
        if (!t->right) {
            *q = t->left;
            break;
        }

        r = &t->right;

        if (!(*r)->left) {
            (*r)->left = t->left;
            *q = *r;
            break;
        }

        s = &(*r)->left;

        while ((*s)->left) {
            r = s;
            s = &(*r)->left;
        }

       (*s)->left = t->left;
       (*r)->left = (*s)->right;
       (*s)->right = t->right;

        *q = *s;
    } while (0);

    free(t);

    return parent;
}

static void walk(const void *root, act *action, int level) {

 // walk(), unlike traverse(), cannot tail-recurse, and so we might want an
 // iterative implementation for large trees
 //
    const struct tree *p = root;

    if (!p) return;

    if (!p->left && !p->right) {
        action(p, leaf, level);
    } else {
        action(p, preorder , level);
        walk(p->left , action, level + 1);
        action(p, postorder, level);
        walk(p->right, action, level + 1);
        action(p, endorder , level);
    }
}

void twalk(const void *root, act *action) {
    walk(root, action, 0);
}

void tdestroy(void *root, freer *free_node) {

    struct tree *p = root;

    if (!p) return;

    tdestroy(p->left , free_node);
    tdestroy(p->right, free_node);

    free_node((void*)p->datum);

    free(p);
}