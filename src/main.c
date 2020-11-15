#include "uls.h"


bool checkPath(char *path) {
    struct stat stats;

    stat(path, &stats);
    if (S_ISDIR(stats.st_mode))
            return 1;
    return 0;
}
t_path *initPaths(int amt) {
    t_path *p = (t_path *)malloc(sizeof(t_path));
    p->amt = amt;
    p->path = (char **)malloc(sizeof(char *) * amt);
    // for (int i = 0; i < amt; i++)
    //     p->path[i] = NULL;
    return p;
}

t_path *getPaths(int argc, char *argv[]) {
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
            printf("uls: %s: No such file or directory exist",argv[i]);
            none_c++;
        }
    }

    p = initPaths(argc - count - none_c);
    for(int i = 0; count < argc; count++)
        if(status[count])
            p->path[i++] = mx_strdup(argv[count]);

    for(int i = 0;i < p->amt; i++)
        printf("\nuls: %s", p->path[i]);
    return p;
}

int main(int argc, char *argv[]) {
    getPaths(argc, argv);
    return 0;
}
