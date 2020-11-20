#include"uls.h"

void cf_not_flag_f(t_obj **d, int d_amt, const bool *fl) {
    char *buf = NULL;
    int j = 0;

    if (!fl[f]) {
            for (int i = 0; i < d_amt; i++) {
                if (mx_strcmp(d[j]->kids[i]->name, d[j]->kids[i + 1]->name) > 0) {
                    buf = d[j]->kids[i]->name;
                    d[j]->kids[i]->name = d[j]->kids[i + 1]->name;
                    d[j]->kids[i + 1]->name = buf;
                    i = 0;
                }
            }
        }
}
