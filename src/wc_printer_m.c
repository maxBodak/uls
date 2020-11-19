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
}
static char *getShortName(char *p) {
    int l = mx_strlen_safe(p) - 1;

    for (;l > 0 && p[l] != '/'; l--);
    l += (l != 0);
    p += l;
    return p;
}
void wc_printWithM(t_obj **fp, int fp_amt) {
    struct winsize w;
    int len = 0;
    char *name;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (mx_strlen(fp[0]->name) >= w.ws_col)
        mx_printchar('\n');
    for (int i = 0; i < fp_amt; i++) {
        name = getShortName(fp[i]->name);
        if (i != 0)
            printDelimiter(&len, name, w.ws_col);
        mx_printstr(name);
        len += mx_strlen(name);
    }
    mx_printstr("\n");
}
