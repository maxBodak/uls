#pragma once

#include "libmx.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <time.h>

#define INT_MAX 2147483647
#define PATH_MAX 1024

enum flags {
    R,
    l,
    one,
    m,
    C,
    S,
    t,
    r,
    p,
    u,
    c,
    dog,
    e,
    h,
    T
};

typedef struct s_path {
    char **path;
    bool *isdir;
    int amt;
}              t_path;
typedef struct s_obj {
    struct s_obj **subdirs;
    struct s_obj *files;
    //t_file *files;

    char *name;
    struct stat st;

    int dir_amt;
    int file_amt;

    char type;
}              t_obj;

t_path *wc_getPaths(int argc, char *argv[]);
t_obj *wc_getDirInfo(char *p, bool rec);
t_obj *wc_getFileInfo(char *p);

/*-----------Utilities------------*/
void wc_fetchData(t_path *p, bool rec);
void printShortName(char *p);
bool isTrueDir(char *name);
