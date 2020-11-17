#include "uls.h"
void printShortName(char *p) {
    int l = mx_strlen(p) - 1;

    for (;l > 0 && p[l] != '/'; l--);
    l += (l != 0);
    p += l;
    mx_printstr(p);
}/*--------------------------------------------------------------------------*/
bool isTrueDir(char *name) {
    if (mx_strcmp(name, ".") && mx_strcmp(name, ".."))
        return true;
    return false;
}/*--------------------------------------------------------------------------*/
void printInfo(t_obj *obj, bool rec) {
    if (obj->type != 0) {
        for (int i = 0; i < obj->file_amt; i++) {
            mx_printstr(obj->files[i].name);
            mx_printstr("\n");
        }
        for (int i = 0; i < obj->dir_amt; i++) {
            printShortName(obj->subdirs[i]->name);
            mx_printstr("\n");
        }
        if (rec) {
            for (int i = 0; i < obj->dir_amt; i++) 
                if (isTrueDir(obj->subdirs[i]->name)) {
                    mx_printstr("\n");
                    mx_printstr(obj->subdirs[i]->name);
                    mx_printstr(":\n");
                    printInfo(obj->subdirs[i], 1);
                }
        }
    } else {
        mx_printstr(obj->name);
        mx_printstr("\n");
    }
}/*--------------------------------------------------------------------------*/
void wc_fetchData(t_path *p, bool rec) {
    t_obj *d = NULL;
    int f;
    for (f = 0; f < p->amt; f++)
        if (!p->isdir) {
            d = wc_getFileInfo(p->path[f]);
            printInfo(d, 0);
            free(d);
        }
    for (int i = 0; i < p->amt; i++) {
        if (p->isdir) {
            d = wc_getDirInfo(p->path[i], rec);
            if (p->amt > 1 && d->type == 1) {
                if (i > 0 && f > 0)
                    mx_printstr("\n");
                mx_printstr(d->name);
                mx_printstr(":\n");
            }
            printInfo(d, rec);
            free(d);
        }
    }
}
