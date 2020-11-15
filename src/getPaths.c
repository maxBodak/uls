#include "uls.h"

static inline bool checkPath(char *path) {
    struct stat stats;

    stat(path, &stats);
    if (S_ISDIR(stats.st_mode))
            return 1;
    return 0;
}
static inline t_path *initPaths(int amt) {
    t_path *p = (t_path *)malloc(sizeof(t_path));
    p->amt = amt;
    p->path = (char **)malloc(sizeof(char *) * amt);
    return p;
}

t_path *wc_getPaths(int argc, char *argv[]) {
    t_path *p;
    bool *status;
    int count = 1;
    int none_c = 0;

    while (count < argc && argv[count][0] == '-')
        count++;

    status = (bool *)malloc(sizeof(bool) * argc - count);
    for(int i = count; i < argc; i++) {
        if(checkPath(argv[i]))
            status[i] = true;
        else {
            printf("uls: %s: No such file or directory exists\n",argv[i]);
            none_c++;
        }
    }

    p = initPaths(argc - count - none_c);
    return p;
}
