#include "uls.h"

void printShortName(char *p) {
    int l = mx_strlen(p) - 1;

    for (;l > 0 && p[l] != '/'; l--);
    l += (l != 0);
    p += l;
    mx_printstr(p);
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
