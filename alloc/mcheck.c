#include <stdlib.h>
#include <stdio.h>
#include <mcheck.h>

void mcheck_callback(enum mcheck_status status) {

     printf("memcheck_abort: status = ");

     if      (status == MCHECK_DISABLED) printf("MCHECK_DISABLED");
     else if (status == MCHECK_OK      ) printf("MCHECK_OK"      );
     else if (status == MCHECK_HEAD    ) printf("MCHECK_HEAD"    );
     else if (status == MCHECK_TAIL    ) printf("MCHECK_TAIL"    );
     else if (status == MCHECK_FREE    ) printf("MCHECK_FREE"    );

     printf("\n");

}

int main() {

    mcheck(mcheck_callback);

    char *m1 = malloc( 50);
    char *m2 = malloc(150);

    printf("Free 1st time\n");
    free(m1);

    printf("Free 2nd time\n");
    free(m1);

    printf("The END.\n");
}
