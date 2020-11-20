#include "uls.h"

void wc_printWithOne(t_obj **fp, int fp_amt) {
        for(int i = 0; i < fp_amt; i++) {
            wc_printShortName(fp[i]->name);
            mx_printstr("\n");
        }
}
