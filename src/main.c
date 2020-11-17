#include "uls.h"

int main(int argc, char ** argv) {
    //cf
    t_flags *fl = cf_flags_num (argc, argv);
    for(int i = 0; i < ALL_FLAGS; i++)
        printf("%d - %d\n", i+8, fl->flags[i]);
    printf("cf end\n");
    system("leaks uls");
    //eng cf
    t_path *p = wc_getPaths(argc, argv);

    t_dir *d = bigPP(p->path[0], 1);
    for (int i = 0; i < d->file_amt; i++)
        printf("%s\n", d->files[i].name);

    for (int i = 0; i < d->dir_amt; i++) {
        printf("%s\n", d->dirs[i]->name);
        for (int j = 0; j < d->dirs[i]->file_amt; j++)
            printf("\t%s\n", d->dirs[i]->files[j].name);
        for (int j = 0; j < d->dirs[i]->dir_amt; j++)
            printf("\t%s\n", d->dirs[i]->dirs[j]->name);
    }
    return 0;
}
