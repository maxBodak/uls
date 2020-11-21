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
    char *path_name;
    char *s_name;
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
typedef struct s_lout {
    int total;
    short a_link;
    short b_owner;
    short c_group;
    short d_size;
}               t_lout;

/*-----------Fetchers-------------*/
t_path *wc_getPaths(int argc, char *argv[]);
t_obj *wc_fetchDirInfo(char *p, bool *fl);
t_obj *wc_fetchFileInfo(char *p);
t_data *wc_fetchData(t_path *p, bool *fl);
/*-----------Utilities------------*/
void wc_printShortName(char *p);
char *wc_getShortName(char *p);
short wc_getBitDepth(int a);
//char *getStatName(char *name);
/*-----------Cleaners------------*/
void wc_freePath(t_path *p);
void wc_freeObj(t_obj *o);
void wc_freeData(t_data *d);
/*-----------Printers------------*/
void wc_printWithC(t_obj **fp, int fp_amt);
void wc_printWithOne(t_obj **fp, int fp_amt);
void wc_printWithM(t_obj **fp, int fp_amt);
void wc_printWithL(t_obj **fp, int fp_amt, bool *fl);
t_lout getSizesForL(t_obj **fp, int fp_amt);
/*-----------Temp-----------------*/
void wc_printResult(t_data *d, bool *flocktimeout);
void wc_printDir(t_obj *obj, bool *fl);
void wc_printObjArr(t_obj **fp, int fp_amt, bool *fl);
/*-----------Sorting--------------*/
void mx_quicksortObj(t_obj **arr, int l, int r, bool cmp(t_obj *, t_obj *));
/*----------CKiff-----------------*/
void cf_not_flag_f(t_obj **d, int d_amt, const bool *fl);
