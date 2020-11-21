#include "uls.h"

void wc_printWithOne(t_obj **fp, int fp_amt) {
        for(int i = 0; i < fp_amt; i++) {
            mx_printstr(fp[i]->s_name);
            mx_printstr("\n");
        }
}
