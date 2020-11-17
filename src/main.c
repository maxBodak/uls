#include "uls.h"

int main(int argc, char ** argv) {
    //cf
//    bool flags[ALL_FLAGS];
    t_flags *fl = cf_flags_num (argc, argv);
    for(int i = 0; i < ALL_FLAGS; i++)
        printf("%d - %d\n", i+8, fl->flags[i]);
    printf("cf end\n");
    system("leaks uls");
    //eng cf
    t_path *p = wc_getPaths(argc, argv);
    for (int f = 0; f < p->amt; f++)
        if (p->isdir) {
            mx_printstr(p->path[f]);
            mx_printstr("\n");
        }
    //wc_fetchData(p, 1);
    //system("leaks -q uls");
    return 0;
}
