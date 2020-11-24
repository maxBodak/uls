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

#define RED       "\x1B[31m"
#define GRN       "\x1B[32m"
#define YEL       "\x1B[33m"
#define BLU       "\x1B[34m"
#define MAG       "\x1B[35m"
#define RESET     "\x1B[0m"
#define BLK_F_RED_B "\x1B[0;30;41m"
#define BLK_F_CYAN_B "\x1B[0;30;46m"
#define BLOCK "\x1B[0;34;46m"
#define CHR "\x1B[0;34;43m"
#define DIR_T "\x1B[0;30;42m"
#define DIR_X "\033[0;30;43m"

enum types {
    dir,
    file,
    dots,
    perm_denied
};
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
//void wc_printShortName(char *p);
char *wc_getShortName(char *p);
short wc_getBitDepth(int a);
//char *getStatName(char *name);
/*-----------Cleaners------------*/
void wc_freePath(t_path *p);
void wc_freeObj(t_obj *o);
void wc_freeData(t_data *d);
/*-----------Printers------------*/
void wc_printName(t_obj *obj, bool *fl);
void wc_printWithC(t_obj **fp, int fp_amt, bool *fl);
void wc_printWithOne(t_obj **fp, int fp_amt, bool *fl);
void wc_printWithM(t_obj **fp, int fp_amt, bool *fl);
void wc_printWithL(t_obj **fp, int fp_amt, bool *fl);
t_lout getSizesForL(t_obj **fp, int fp_amt);
/*-----------Temp-----------------*/
void wc_printResult(t_data *d, bool *flocktimeout);
void wc_printDir(t_obj *obj, bool *fl);
void wc_printObjArr(t_obj **fp, int fp_amt, bool *fl);
/*-----------Sorting--------------*/
void mx_quicksortObj(t_obj **arr, int l, int r, bool cmp(t_obj *, t_obj *));
/*-----------Errors---------------*/
void wc_errorNoPath(char *path);
void wc_errorPermDenied(char *name_of_dir);
/*-----------Ckif----------------*/
void cf_not_flag_f(t_obj **d, int d_amt, const bool *fl);
void cf_flag_r(t_obj **d, int d_amt, const bool *fl);
void cf_flag_S(t_obj **d, int d_amt, const bool *fl);

