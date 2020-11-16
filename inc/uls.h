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

typedef struct s_file {
    char *name;
    struct stat st;
}              t_file;
typedef struct s_dir {
    struct s_dir *dirs;
    t_file *files;

    char *name;
    struct stat st;

    int dir_amt;
    int file_amt;
}              t_dir;


typedef struct s_result {
    t_file *files;
    t_dir *dirs;
    int file_amt;
    int dir_amt;
}              t_result;

t_path *wc_getPaths(int argc, char *argv[]);
t_dir *bigPP(char *p, bool rec);
t_file *bigFF(char *p);
