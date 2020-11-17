#include "uls.h"

int main(int argc, char ** argv) {
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
