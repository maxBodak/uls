#include "uls.h"

static inline char *getName(char *p) {
    int l = mx_strlen(p) - 1;

    for (;l > 0 && p[l] != '/'; l--);
    l += (l != 0);
    p += l;
    return mx_strdup(p);
}/*==========================================================================*/
t_obj *wc_getFileInfo(char *p) {
    t_obj *f = (t_obj *)malloc(sizeof(t_obj));
    stat(p, &(f->st));
    f->name = getName(p);
    f->kids_amt = 0;
    f->kids = NULL;
    f->type = 0;
    return f;
}
