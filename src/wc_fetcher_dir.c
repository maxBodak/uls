#include "uls.h"

static inline bool isDot(char *name) {
    return !mx_strcmp(name, ".") || !mx_strcmp(name, "..");
}/*--------------------------------------------------------------------------*/
static inline bool isHidden(char *name) {
    return name[0] == '.';
}/*--------------------------------------------------------------------------*/
static inline t_obj *initDir(char *p, bool *fl) {
    DIR *dp;
    struct dirent *ep;
    int count = 0;
    t_obj *d = NULL;

    dp = opendir (p);
    if (dp != NULL) {
        while ((ep = readdir(dp)))
            if (!isHidden(ep->d_name) || fl[a] || (fl[A] && !isDot(ep->d_name)))
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
t_obj *wc_fetchDirInfo(char *p, bool *fl) {
    DIR *dp;
    char *buf = NULL;
    struct dirent *ep;
    t_obj *res = initDir(p, fl);

    if (res) {
        dp = opendir (p);
        for (int i = 0; (ep = readdir(dp));) {
            if (!isHidden(ep->d_name) || fl[a] || (fl[A] && !isDot(ep->d_name))) {
                if (fl[R] && ep->d_type == DT_DIR && !isDot(ep->d_name)) {
                        buf = addPrefix(p, ep->d_name);
                        res->kids[i] = wc_fetchDirInfo(buf, fl);
                        free(buf);
                } else {
                    res->kids[i] = (t_obj *)malloc(sizeof(t_obj));
                    res->kids[i]->name = mx_strdup(ep->d_name);
                    res->kids[i]->kids_amt = 0;
                    res->kids[i]->kids = NULL;
                    res->kids[i]->type = 2 * (isDot(ep->d_name));
                }
                buf = addPrefix(p, ep->d_name);
                stat(buf, &(res->kids[i++]->st));
                free(buf);
            }
        }
        closedir(dp);
    }
    return res;
}
