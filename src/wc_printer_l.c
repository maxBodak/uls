#include "uls.h"

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
            mx_printstr("\n");
        }
}
