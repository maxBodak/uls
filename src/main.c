#include "uls.h"
void o_free(t_obj *o) {
    if(o == NULL)
        return;
    free(o->name);
    for (int i = 0; i < o->file_amt; i++)
        free(o->files[i].name);
    if(o->file_amt)
        free(o->files);
    for (int i = 0; i < o->subdir_amt; i++)
        o_free(o->subdirs[i]);
    free(o);
}
void freeer(t_data *d) {
    if(d == NULL)
        return;
    for (int i = 0; i < d->amt; i++) {
        o_free(d->path[i]);
    }
    free(d);
}
int main(int argc, char ** argv) {
//cf
    // t_flags *fl = cf_flags_num (argc, argv);
    // for(int i = 0; i < ALL_FLAGS; i++)
    //     printf("%d - %d\n", i+8, fl->flags[i]);
    // printf("cf end\n");
    // system("leaks uls");
//eng cf
    t_path *p = wc_getPaths(argc, argv);
    for (int f = 0; f < p->amt; f++)
        if (p->isdir) {
            mx_printstr(p->path[f]);
            mx_printstr("\n");
        }
    system("leaks -q uls");
    t_data *d = wc_fetchData(p, 1);
    printf("%d\n", d->amt);
    freeer(d);
    free(p);
    system("leaks -q uls");
    return 0;
}
