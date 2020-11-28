#pragma once

#include "uls.h"
#define FLAG_LIST "ACFGHLSRTUacdefhlmnoprtu1@"
enum flags {
    G,
    U,
    F,
    f,
    a,
    A,
    R,
    l,
    one,
    m,
    C,
    S,
    t,
    r,
    p,
    u,
    c,
    dog,
    e,
    h,
    T,
    d,
    L,
    H,
    n,
    o,
    tty,
    err,
    ALL_FLAGS,
};

bool *cf_flags_num (int argc, char *argv[]);
bool *cf_cmp_flags(bool *fls);
void cf_err_illegal_option(char *flags_char);
bool *cf_isatty(bool *fls);
bool *cf_bool_manip(int argc, char **argv);

    













