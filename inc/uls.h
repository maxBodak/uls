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
    char hidden;
}              t_obj;
typedef struct s_data {
    t_obj **dirs_path;
    t_obj **files_path;
    int dirs_amt;
    int files_amt;
}               t_data;
t_path *wc_getPaths(int argc, char *argv[]);
/*-----------Fetchers-------------*/
t_data *wc_fetchData(t_path *p, bool *fl);
t_obj *wc_getDirInfo(char *p, bool *fl);
t_obj *wc_getFileInfo(char *p);
/*-----------Utilities------------*/
void wc_printDir(t_obj *obj, bool *fl);
void wc_printResult(t_data *d, bool *flocktimeout);
void printShortName(char *p);

void wc_printObjArr(t_obj **fp, int fp_amt, bool *fl);
/*-----------Cleaners------------*/
void wc_freePath(t_path *p);
void wc_freeObj(t_obj *o);
void wc_freeData(t_data *d);
