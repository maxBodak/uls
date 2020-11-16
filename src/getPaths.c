#include "uls.h"

static inline void errorNoPath(char *path) {
    mx_printstr("uls: ");
    mx_printstr(path);
    mx_printstr(": No such file or directory exists\n");
}
static char checkPath(char *path) {
    struct stat stats;
    int e = stat(path, &stats);
    
    if (!e) {
        if (S_ISDIR(stats.st_mode))
            return 1;
        return 2;
    }
    return 0;
}
static inline t_path *CurDirPath() {
    t_path *p = (t_path *)malloc(sizeof(t_path));

    p->amt = 1;
    p->path = (char **)malloc(sizeof(char *) * p->amt);
    p->isdir = (bool *)malloc(sizeof(bool) * p->amt);
    p->path[0] = mx_strdup(".");
    p->isdir[0] = true;
    return p;
}
static inline t_path *initPaths(int argc, char *argv[], char *status,
                                                int flags, int fakes) {
    t_path *p = (t_path *)malloc(sizeof(t_path));

    p->amt = argc - flags - fakes;
    p->path = (char **)malloc(sizeof(char *) * p->amt);
    p->isdir = (bool *)malloc(sizeof(bool) * p->amt);

    for (int i = 0, j = 0; j < argc - flags; j++) {
        if (status[j] == 1) {
            p->isdir[i] = true;
            p->path[i++] = argv[j + flags];
        }
        else if(status[j] == 2)
            p->path[i++] = argv[j + flags];
        else
            errorNoPath(argv[j + flags]);
    }
    return p;
}
t_path *wc_getPaths(int argc, char *argv[]) {
    int flags = 1;
    int fakes = 0;
    char *status;

    while (argv[flags][0] == '-')
        if (argv[flags++][1] == '-')
            break;

    status = (char *)malloc(sizeof(char) * argc - flags);
    for(int i = flags; i < argc; i++) {
        status[i - flags] = checkPath(argv[i]);
        fakes += !status[i - flags];
    }
    if (argc - flags - fakes == 0) {
        if (fakes == 0)
            return CurDirPath();
        else
            return NULL;
    }
    return initPaths(argc, argv, status, flags, fakes);
}
