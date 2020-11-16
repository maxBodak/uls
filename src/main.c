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

    t_file *d = bigFF(p->path[0]);
    printf("%s\n", d->name);
    // for (int i = 0; i < d->dir_amt; i++)
    //     printf("%s\n", d->dirs[i].name);
    // for (int i = 0; i < d->file_amt; i++)
    //     printf("%s\n", d->files[i].name);
    return 0;
}
