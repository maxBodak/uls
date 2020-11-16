#include "uls.h"

int main(int argc, char *argv[]) {
    t_path *p = wc_getPaths(argc, argv);
    // if (p)
    //     for (int i = 0; i < p->amt; i++)
    //         printf("path[%d]: %s\n", i, p->path[i]);
    // else
    //     printf("no paths exist\n");
    return 0;
}
