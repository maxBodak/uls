#pragma once

#include "uls.h"

#define ALL_FLAGS 21

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
};

bool *cf_flags_num (int argc, char *argv[]);
bool * cf_cmp_flags(bool *fls);
void cf_arr_illegal_option(char *flags_char);
