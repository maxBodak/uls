#include "uls.h"

// int main(int argc, char *argv[]) {
//     t_path *p = wc_getPaths(argc, argv);

//     for (int i = 0; i < p->amt; i++) {
//         mx_printstr(p->path[i]);
//         mx_printstr("\n");
//     }

//     char buf[PATH_MAX];
//     ssize_t len = readlink("src/", buf, PATH_MAX);
//     mx_printint((int)len);
//     if (len != -1) {
//         buf[len] = '\0';
//         printf("%s\n", buf);
//     }


//     // if (p)
//     //     for (int i = 0; i < p->amt; i++)
//     //         printf("path[%d]: %s\n", i, p->path[i]);
//     // else
//     //     printf("no paths exist\n");
//     return 0;
// }

int main(int argc, char ** argv) {
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
