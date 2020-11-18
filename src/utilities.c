#include "uls.h"

void printShortName(char *p) {
    int l = mx_strlen(p) - 1;

    for (;l > 0 && p[l] != '/'; l--);
    l += (l != 0);
    p += l;
    mx_printstr(p);
}/*--------------------------------------------------------------------------*/
bool isNotDots(char *name) {
    if (mx_strcmp(name, ".") && mx_strcmp(name, ".."))
        return true;
    return false;
}/*--------------------------------------------------------------------------*/
void wc_printInfo(t_obj *obj, bool rec) {
    if (obj->type != 0) {
        for (int i = 0; i < obj->kids_amt; i++) {
            printShortName(obj->kids[i]->name);
            mx_printstr("\n");
        }
        if (rec) {
            for (int i = 0; i < obj->kids_amt; i++) 
                if (obj->kids[i]->type == 1) {
                    mx_printstr("\n");
                    mx_printstr(obj->kids[i]->name);
                    mx_printstr(":\n");
                    wc_printInfo(obj->kids[i], 1);
                }
        }
    } else {
        mx_printstr(obj->name);
        mx_printstr("\n");
    }
}/*--------------------------------------------------------------------------*/
t_data *wc_fetchData(t_path *p, bool rec) {
    int i = 0;
    t_data *res = NULL;

    if(p) {
        res = (t_data *)malloc(sizeof(res));
        res->amt = p->amt;
        res->path = (t_obj **)malloc(sizeof(t_obj *) * p->amt);
        for (int j = 0; j < p->amt; j++)
            if (!p->isdir[j])
                res->path[i++] = wc_getFileInfo(p->path[j]);
        for (int j = 0; j < p->amt; j++)
            if (p->isdir[j])
                res->path[i++] = wc_getDirInfo(p->path[j], rec);
    }
    return res;
}
