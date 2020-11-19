#include "uls.h"

void printShortName(char *p) {
    int l = mx_strlen_safe(p) - 1;

    for (;l > 0 && p[l] != '/'; l--);
    l += (l != 0);
    p += l;
    mx_printstr(p);
}/*--------------------------------------------------------------------------*/
void printPermsUtil(struct stat st) {
    mx_printstr((S_ISDIR(st.st_mode)) ? "d" : "-");
    mx_printstr((st.st_mode & S_IRUSR) ? "r" : "-");
    mx_printstr((st.st_mode & S_IWUSR) ? "w" : "-");
    mx_printstr((st.st_mode & S_IXUSR) ? "x" : "-");
    mx_printstr((st.st_mode& S_IRGRP) ? "r" : "-");
    mx_printstr((st.st_mode & S_IWGRP) ? "w" : "-");
    mx_printstr((st.st_mode & S_IXGRP) ? "x" : "-");
    mx_printstr((st.st_mode& S_IROTH) ? "r" : "-");
    mx_printstr((st.st_mode & S_IWOTH) ? "w" : "-");
    mx_printstr((st.st_mode & S_IXOTH) ? "x" : "-");
}/*--------------------------------------------------------------------------*/
void wc_printObjArr(t_obj **fp, int fp_amt, bool *fl) {
    if (!fp_amt)
        return;
    if (fl[one]) {
        for(int i = 0; i < fp_amt; i++) {
            printShortName(fp[i]->name);
            mx_printstr("\n");
        }
    } else if (fl[m]) {
        for(int i = 0; i < fp_amt; i++) {
            if(i)
                mx_printstr(", ");
            printShortName(fp[i]->name);
        }
         mx_printstr("\n");
    } else if (fl[l]) {
        for(int i = 0; i < fp_amt; i++) {
            printPermsUtil(fp[i]->st);
            mx_printstr("\t");
            printShortName(fp[i]->name);
            mx_printstr("\n");
        }
         mx_printstr("\n");
    } else {
        for(int i = 0; i < fp_amt; i++) {
            printShortName(fp[i]->name);
            if (i % 2)
                mx_printstr("\n");
            else
                mx_printstr("\t");
        }
    }
}/*--------------------------------------------------------------------------*/
void wc_printDir(t_obj *obj, bool *fl) {
    wc_printObjArr(obj->kids, obj->kids_amt, fl);
    if (fl[R]) {
        for (int i = 0; i < obj->kids_amt; i++) 
            if (obj->kids[i]->type == 1) {
                mx_printstr("\n");
                mx_printstr(obj->kids[i]->name);
                mx_printstr(":\n");
                wc_printDir(obj->kids[i], fl);
            }
    }
}/*--------------------------------------------------------------------------*/
void wc_printResult(t_data *d, bool *fl) {
    wc_printObjArr(d->files_path, d->files_amt, fl);
    if (d->dirs_amt > 1 || d->files_amt)
        for (int i = 0; i < d->dirs_amt; i++) {
            mx_printstr(d->dirs_path[i]->name);
            mx_printstr(": \n");
            wc_printDir(d->dirs_path[i], fl);
        }
    else
        wc_printDir(d->dirs_path[0], fl);
}
