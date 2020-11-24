#include "uls.h"

int main(int argc, char ** argv) {
//cf
    bool *fl = cf_flags_num (argc, argv);
    fl = cf_cmp_flags(fl);
    fl = cf_isatty(fl);
    // for(int i = 0; i < ALL_FLAGS; i++)
    //     printf("%d - %d\n", i+8, fl->flags[i]);
    // printf("cf end\n");
    // system("leaks uls");
//end of cf
//wc
    t_path *p = wc_getPaths(argc, argv);
    t_data *d = wc_fetchData(p, fl);
    // if (isatty(fileno(stdout))
    //       ? "stdout is tty"
    //       : "stdout is not tty");
    if (d) {
        cf_not_flag_f(d->files_path, d->files_amt, fl);
        cf_not_flag_f(d->dirs_path, d->dirs_amt, fl);
    }
    if (d) {
        cf_flag_r(d->files_path, d->files_amt, fl);
        cf_flag_r(d->dirs_path, d->dirs_amt, fl);
    }
    if (d) {
        cf_flag_S(d->files_path, d->files_amt, fl);
        cf_flag_S(d->dirs_path, d->dirs_amt, fl);
    }
    wc_printResult(d, fl);
    wc_freePath(p);
    wc_freeData(d);
    free(fl);
//    system("leaks -q uls");
//end of wd
    return 0;
}
