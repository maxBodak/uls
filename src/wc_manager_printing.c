#include "uls.h"

void wc_printObjArr(t_obj **fp, int fp_amt, bool *fl, bool use_total) {
    if (!fp_amt)
        return;
    if (fl[one])
        wc_printWithOne(fp, fp_amt, fl);
    else if (fl[m])
        wc_printWithM(fp, fp_amt, fl);
    else if (fl[l]) {
        wc_printWithL(fp, fp_amt, fl, use_total);
    } else {
        wc_printWithC(fp, fp_amt, fl);
    }
}/*--------------------------------------------------------------------------*/
void wc_printDir(t_obj *obj, bool *fl) {
    wc_printObjArr(obj->kids, obj->kids_amt, fl, 1); 
    if (fl[R])
        for (int i = 0; i < obj->kids_amt; i++) {
            if (obj->kids[i]->type == dir) {
                mx_printstr("\n");
                mx_printstr(obj->kids[i]->path_name);
                mx_printstr(":\n");
                wc_printDir(obj->kids[i], fl);
            } else if (obj->kids[i]->type == perm_denied) {
                mx_printstr("\n");
                mx_printstr(obj->kids[i]->path_name);
                mx_printstr(":\n");
                wc_errorPermDenied(obj->kids[i]->path_name);
            }
        }
}/*--------------------------------------------------------------------------*/
void wc_printResult(t_data *d, bool *fl) {
    if (d == NULL)
        return;

    wc_printObjArr(d->files_path, d->files_amt, fl, 0);

    if (d->dirs_amt > 1 || d->files_amt) {

        mx_printstr(d->files_amt && d->dirs_amt ? "\n" : "");
    
        for (int i = 0; i < d->dirs_amt; i++) {
            mx_printstr(d->dirs_path[i]->path_name);
            mx_printstr(": \n");

            if (d->dirs_path[i]->type != perm_denied)
                wc_printDir(d->dirs_path[i], fl);
            else
                wc_errorPermDenied(d->dirs_path[i]->path_name);

            mx_printstr(i + 1 < d->dirs_amt ? "\n" : "");
        }
    }
    else {
        if (d->dirs_path[0]->type == perm_denied)
            wc_errorPermDenied(d->dirs_path[0]->path_name);
        else
            wc_printDir(d->dirs_path[0], fl);
    }
}
