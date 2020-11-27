#include "uls.h"
static inline void printDog(t_obj *fp) {
    char * s = mx_strnew(fp->st.st_size);
    listxattr(fp->path_name, s, fp->st.st_size, XATTR_NOFOLLOW);
    mx_printstr("\n");
}
void wc_printWithL(t_obj **fp, int fp_amt, bool *fl) {
    t_lout spaces = wc_getSizesForL(fp, fp_amt);

    mx_printstr("total ");
    mx_printint(spaces.total);
    mx_printchar('\n');
        for(int i = 0; i < fp_amt; i++) {
            wc_printPerms(fp[i]->st, fp[i]->path_name);
            wc_printStats(fp[i]->st, spaces);
            wc_printTime(fp[i]->st, fl);
            mx_printstr(" ");
            wc_printName(fp[i], fl);
            if (fp[i]->type == lnk) {
                mx_printstr(" -> ");
                char b[1024];
                readlink(fp[i]->path_name, b, 1024);
                mx_printstr(b);
            }
            if (fl[dog])
                printDog(fp[i]);
            mx_printstr("\n");
        }
}
