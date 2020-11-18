#pragma once

#include "libmx.h"

#include "cf_uls.h"
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

typedef struct s_path {
    char **path;
    bool *isdir;
    int amt;
}              t_path;
typedef struct s_obj {
    struct s_obj **kids;
    char *name;
    struct stat st;
    int kids_amt;
    char type;
}              t_obj;
typedef struct s_data {
    t_obj **path;
    int amt;
}               t_data;
t_path *wc_getPaths(int argc, char *argv[]);
t_obj *wc_getDirInfo(char *p, bool rec);
t_obj *wc_getFileInfo(char *p);

/*-----------Utilities------------*/
t_data *wc_fetchData(t_path *p, bool rec);
void wc_printInfo(t_obj *obj, bool rec);
void printShortName(char *p);
/*-----------Cleaners------------*/
void wc_freePath(t_path *p);
void wc_freeObj(t_obj *o);
void wc_freeData(t_data *d);
