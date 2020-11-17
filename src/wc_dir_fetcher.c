#include "uls.h"

static inline t_obj *initDir(char *p) {
    DIR *dp;
    struct dirent *ep;
    int dcount = 0;
    int fcount = 0;
    t_obj *d = NULL;

    dp = opendir (p);
    if (dp != NULL) {
        while ((ep = readdir(dp))) {
            if (ep->d_type == DT_DIR)
                dcount++;
            else if (ep->d_type == DT_REG)
                fcount++;
        }
        closedir(dp);
    }
    d = (t_obj *)malloc(sizeof(t_obj));
    d->name = mx_strdup(p);
    d->file_amt = fcount;
    d->subdir_amt = dcount;
    d->subdirs = (t_obj **)malloc(sizeof(t_obj *) * dcount);
    d->files = (t_obj *)malloc(sizeof(t_obj) * fcount);
    d->type = 1;
    return d;
}/*--------------------------------------------------------------------------*/
static inline char *addPrefix(char *prefix, char *str) {
    char *t1 = NULL;
    char *t2 = NULL;

    if (prefix[mx_strlen_safe(prefix) -1] != '/') {
        t1 = mx_strjoin(prefix, "/");
        t2 = mx_strjoin(t1, str);
        free(t1);
    }
    else
        t2 = mx_strjoin(prefix, str);
    return t2;
}/*==========================================================================*/
t_obj *wc_getDirInfo(char *p, bool rec) {
    DIR *dp;
    char *buf = NULL;
    struct dirent *ep;
    t_obj *res = initDir(p);

    if (res) {
        dp = opendir (p);
        for (int i = 0, j = 0; (ep = readdir(dp));) {
            if (ep->d_type == DT_DIR) {
                if (rec && isTrueDir(ep->d_name)) {
                    buf = addPrefix(p, ep->d_name);
                    res->subdirs[i] = wc_getDirInfo(buf, 1);
                    free(buf);
                }
                else {
                    res->subdirs[i] = (t_obj *)malloc(sizeof(t_obj));
                    res->subdirs[i]->name = mx_strdup(ep->d_name);
                }
                stat(ep->d_name, &(res->subdirs[i++]->st));
            }
            else if (ep->d_type == DT_REG) {
                stat(ep->d_name, &(res->files[j].st));
                res->files[j].name = mx_strdup(ep->d_name);
                res->files[j].subdir_amt = 0;
                res->files[j].file_amt = 0;
                res->files[j].subdirs = NULL;
                res->files[j].files = NULL;
                res->files[j++].type = 0;
            }
        }
        closedir(dp);
    }
    return res;
}

