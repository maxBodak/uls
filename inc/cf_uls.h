#pragma once

#include "uls.h"

#define ALL_FLAGS 15

typedef struct s_flags {
    bool *flags;
    char *flags_char;
}              t_flags;

void cf_flags_num (int argc, char *argv[]);