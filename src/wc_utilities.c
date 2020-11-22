#include "uls.h"

short wc_getBitDepth(int a) {
    short r = 0;

    a = (a == 0) ? 1 : a;
    while ((a = a / 10))
        r++;
    return r;
}/*--------------------------------------------------------------------------*/
char *wc_getShortName(char *p) {
    int l = mx_strlen_safe(p) - 1;

    for (;l > 0 && p[l] != '/'; l--);
    l += (p[l] == '/');
    p += l;
    return p;
}/*--------------------------------------------------------------------------*/
// void wc_printShortName(char *p) {
//     int l = mx_strlen_safe(p) - 1;

//     for (;l > 0 && p[l] != '/'; l--);
//     l += (l != 0);
//     p += l;
//     mx_printstr(p);
// }/*--------------------------------------------------------------------------*/
// char *getStatName(char *name) {
//     int l = mx_strlen_safe(name) - 1;

//     for (;l > 0 && name[l] != '.'; l--);
//     return l ? mx_strndup(name, l) : mx_strdup(name);
// }
