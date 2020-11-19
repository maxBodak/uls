#include "uls.h"

int main(int argc, char ** argv) {
//cf
     bool *fl = cf_flags_num (argc, argv);
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
    t_data *d = wc_fetchData(p, fl);
    // for (int i = 0; i < d->files_amt; i++) {
    //     wc_printInfo(d->files_path[0], fl);
    //     mx_printstr("\n");
    // }
    // for (int i = 0; i < d->dirs_amt; i++) {
    //     wc_printInfo(d->dirs_path[0], fl);
    //     mx_printstr("\n");
    // }
    wc_printResult(d, fl);
    wc_freePath(p);
    wc_freeData(d);
    free(fl);
    //system("leaks -q uls");
//end of wd
    return 0;
}
