#pragma once

#include "libmx.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define INT_MAX 2147483647


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

typedef struct s_path {
    char **path;
    int amt;
}              t_path;

t_path *wc_getPaths(int argc, char *argv[]);
