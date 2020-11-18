#include "uls.h"

int main(int argc, char ** argv) {
//cf
    // t_flags *fl = cf_flags_num (argc, argv);
    // for(int i = 0; i < ALL_FLAGS; i++)
    //     printf("%d - %d\n", i+8, fl->flags[i]);
    // printf("cf end\n");
    // system("leaks uls");
//end of cf
//wc
    t_path *p = wc_getPaths(argc, argv);
    // for (int f = 0; f < p->amt; f++) {
    //         mx_printstr(p->path[f]);
    //         mx_printstr("\n");
    // }
    t_data *d = wc_fetchData(p, 0);
    wc_printInfo(d->path[0], 1);
    wc_freePath(p);
    wc_freeData(d);
    //system("leaks -q uls");
//end of wd
    return 0;
}
