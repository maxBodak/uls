#include "uls.h"

static inline int findMaxLenName(t_obj **fp, int fp_amt) {
    int l = mx_strlen(fp[0]->s_name);

    for(int i = 1; i < fp_amt; i++)
        l = l < mx_strlen(fp[i]->s_name) ? mx_strlen(fp[i]->s_name) : l;
    return l - l % 8 + 8;
}/*--------------------------------------------------------------------------*/
static inline void printMultiCuls(t_obj **fp, int fp_amt, 
                                    int max_len, int cols) {
    int rows = !(fp_amt % cols) ? fp_amt / cols : fp_amt / cols + 1;
    int tmp;

    for (int i = 0; i < rows; mx_printchar(10)) {
        for (int j = i++; j < fp_amt; j += rows) {
            mx_printstr(fp[j]->s_name);
            tmp = (max_len - mx_strlen(fp[j]->s_name)) / 8;
            (max_len - mx_strlen(fp[j]->s_name)) % 8 != 0 ? tmp++ : tmp;
            for (int k = 0; k++ < tmp; mx_printchar('\t'));
        }
    }
}/*--------------------------------------------------------------------------*/
static inline void printInOneRow(t_obj **fp, int fp_amt, int max_len) {
    for (int i = 0; i < fp_amt; i++) {
            mx_printstr(fp[i]->s_name);
        for (int j = mx_strlen(fp[i]->s_name); j < max_len; j++)
            mx_printchar(' ');
    }
    fp_amt > 0 ? mx_printchar(10) : mx_printstr("");
}/*==========================================================================*/
void wc_printWithC(t_obj **fp, int fp_amt) {
    struct winsize w;
    int max_len = findMaxLenName(fp, fp_amt);

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (w.ws_col < max_len)
        wc_printWithOne(fp, fp_amt);
    else if (w.ws_col >= max_len * fp_amt)
        printInOneRow(fp, fp_amt, max_len);
    else
        printMultiCuls(fp, fp_amt, max_len, w.ws_col / max_len);
}
