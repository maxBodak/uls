#pragma once

#include "uls.h"

#define ALL_FLAGS 15

enum flags {
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
    T
};
typedef struct s_flags {
    bool *flags;
    char *flags_char;
}              t_flags;

t_flags *cf_flags_num (int argc, char *argv[]);
