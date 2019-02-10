#include <stdlib.h>
#include <mcheck.h>

int main() {

    mtrace();

    void *mem_1 = malloc( 500);
    void *mem_2 = malloc(1000);

    free(mem_1); // Note mem_1 is freed twice,
    free(mem_1); // mem_2 is not freed at all

}
