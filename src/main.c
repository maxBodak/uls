#include "uls.h"

int main(int argc, char ** argv) {
//cf
    bool *fl = cf_bool_manip(argc, argv);
//    if(fl[tty] == true)
//        printf("is not tty\n");
//    if(!fl[tty] == true)
//        printf("is tty\n");
    // for(int i = 0; i < ALL_FLAGS; i++)
    //     printf("%d - %d\n", i+8, fl->flags[i]);
    // printf("cf end\n");
    // system("leaks uls");
//end of cf
//wc
    t_path *p = wc_getPaths(argc, argv);
    t_data *d = wc_fetchData(p, fl);
    cf_flags_check (d, fl);
//    printf("%d\n",d->dirs_path[0]->kids[8]->st.st_mode);
//    printf("%s\n",d->dirs_path[0]->kids[8]->path_name);
//    if (d) {
//        cf_flag_u(d->files_path, d->files_amt, fl);
//        cf_flag_u(d->dirs_path, d->dirs_amt, fl);
//    }
    wc_printResult(d, fl);
    wc_freePath(p);
    wc_freeData(d);
    free(fl);
//    system("leaks -q uls");
//end of wd
    return 0;
}
