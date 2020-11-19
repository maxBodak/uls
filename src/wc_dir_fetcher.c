#include "uls.h"

static inline t_obj *initDir(char *p) {
    DIR *dp;
    struct dirent *ep;
    int count = 0;
    t_obj *d = NULL;

    dp = opendir (p);
    if (dp != NULL) {
        while ((ep = readdir(dp)))
            count++;
        closedir(dp);
    }
    d = (t_obj *)malloc(sizeof(t_obj));
    d->name = mx_strdup(p);
    d->kids_amt = count;
    d->kids = (t_obj **)malloc(sizeof(t_obj *) * count);
    d->type = 1;
    return d;
}/*--------------------------------------------------------------------------*/
static inline bool isNotDots(char *name) {
    if (mx_strcmp(name, ".") && mx_strcmp(name, ".."))
        return true;
    return false;
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
        for (int i = 0; (ep = readdir(dp)); i++) {
            if (rec && ep->d_type == DT_DIR && isNotDots(ep->d_name)) {
                buf = addPrefix(p, ep->d_name);
                res->kids[i] = wc_getDirInfo(buf, 1);
                free(buf);
                mx_printstr("test\n");
            } else {
                res->kids[i] = (t_obj *)malloc(sizeof(t_obj));
                res->kids[i]->name = mx_strdup(ep->d_name);
                res->kids[i]->kids_amt = 0;
                res->kids[i]->kids = NULL;
                res->kids[i]->type = 2 * (isNotDots(ep->d_name));
            }
            stat(ep->d_name, &(res->kids[i]->st));
        }
        closedir(dp);
    }
    return res;
}
