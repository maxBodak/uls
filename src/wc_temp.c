#include "uls.h"

void wc_printObjArr(t_obj **fp, int fp_amt, bool *fl) {
    if (!fp_amt)
        return;
    if (fl[one])
        wc_printWithOne(fp, fp_amt, fl);
    else if (fl[m])
        wc_printWithM(fp, fp_amt, fl);
    else if (fl[l]) {
        wc_printWithL(fp, fp_amt, fl);
    } else {
        wc_printWithC(fp, fp_amt, fl);
    }
}/*--------------------------------------------------------------------------*/
void wc_printDir(t_obj *obj, bool *fl) {
    wc_printObjArr(obj->kids, obj->kids_amt, fl);
    if (fl[R]) {
        for (int i = 0; i < obj->kids_amt; i++) 
            if (obj->kids[i]->type == 1) {
                mx_printstr("\n");
                mx_printstr(obj->kids[i]->path_name);
                mx_printstr(":\n");
                wc_printDir(obj->kids[i], fl);
            }
    }
}/*--------------------------------------------------------------------------*/
void wc_printResult(t_data *d, bool *fl) {
    if (d == NULL)
        return;

    wc_printObjArr(d->files_path, d->files_amt, fl);
    if (d->dirs_amt > 1 || d->files_amt)
        for (int i = 0; i < d->dirs_amt; i++) {
            mx_printstr(d->dirs_path[i]->path_name);
            mx_printstr(": \n");
            wc_printDir(d->dirs_path[i], fl);
        }
    else
        wc_printDir(d->dirs_path[0], fl);
}
