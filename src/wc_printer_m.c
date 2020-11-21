#include "uls.h"

static void printDelimiter(int *len, char *name, int win_col) {
    int ln = mx_strlen(name);

    mx_printstr(", ");
    if (((*len) + ln + 4 <= win_col))
        (*len) += 2;
    else if (((*len) + ln + 4 > win_col)) {
        (*len) = 0;
        mx_printchar('\n');
    }
}/*==========================================================================*/
void wc_printWithM(t_obj **fp, int fp_amt) {
    struct winsize w;
    int len = 0;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (mx_strlen(fp[0]->s_name) >= w.ws_col)
        mx_printchar('\n');
    for (int i = 0; i < fp_amt; i++) {
        if (i != 0)
            printDelimiter(&len, fp[i]->s_name, w.ws_col);
        mx_printstr(fp[i]->s_name);
        len += mx_strlen(fp[i]->s_name);
    }
    mx_printstr("\n");
}
