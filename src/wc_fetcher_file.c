#include "uls.h"

t_obj *wc_fetchFileInfo(char *p) {
    t_obj *f = (t_obj *)malloc(sizeof(t_obj));
    lstat(p, &(f->st));
    f->path_name = mx_strdup(p);
    f->s_name = wc_getShortName(p);
    f->kids_amt = 0;
    f->kids = NULL;
    f->type = 0;
    return f;
}
