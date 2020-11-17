#include "uls.h"

static inline t_flags *mem_manip(int count_flags) {
    t_flags *fl = (t_flags *)malloc(sizeof(t_flags));
    fl->flags_char = mx_strnew(count_flags - 1);
    fl->flags = (bool *)malloc(sizeof(bool) * ALL_FLAGS);
    return fl;
}

static inline void fill_bool(t_flags *fl, int count_flags) {
    char flag[ALL_FLAGS] = {'R', 'l', '1', 'm', 'C', 'S', 't',
                            'r', 'p', 'u', 'c', '@', 'e', 'h', 'T'};
    for (int i = 0; i < count_flags; i++)
        for (int j = 0; j < ALL_FLAGS; j++)
            if (fl->flags_char[i] == flag[j])
                fl->flags[j] = true;
}

static inline void cmp_flags(t_flags *fl, int i) {
    for (int j = i - 1; j >= 0; j--) {
        if (fl->flags_char[j] == 'l') {
            fl->flags_char[j] = '-';
            fl->flags[l] = false;
        }
        else if (fl->flags_char[j] == 'm') {
            fl->flags_char[j] = '-';
            fl->flags[m] = false;
        }
        else if (fl->flags_char[j] == 'C') {
            fl->flags_char[j] = '-';
            fl->flags[C] = false;
        }
        else if (fl->flags_char[j] == '1') {
            fl->flags_char[j] = '-';
            fl->flags[one] = false;
        }
    }
}

static inline void check_perm(t_flags *fl, int count_flags) {
    for (int i = count_flags - 1; i > 0; i--) {
        if (fl->flags_char[i] == 'S') {
            for (int j = i - 1; j >= 0; j--)
                if (fl->flags_char[j] == 't' || fl->flags_char[j] == 'S') {
                    fl->flags_char[j] = '-';
                    fl->flags[t] = false;
                }
        }
        else if(fl->flags_char[i] == 'l' || fl->flags_char[i] == 'm' ||
                fl->flags_char[i] == 'C' || fl->flags_char[i] == '1' )
            cmp_flags(fl, i);
    }
    if (fl->flags[S] == true)
        fl->flags[t] = false;
}

t_flags *cf_flags_num (int argc, char *argv[]) {
    int count = 0;
    int count_flags = 0;
    t_flags *fl;

    for (int i = 1; i < argc && argv[i][0] == '-' &&
                    (argv[i][1] && argv[i][1] != '-'); i++, count++)
        count_flags += mx_strlen(argv[i]) - 1;
    fl = mem_manip(count_flags);
    for (int i = 0; i < ALL_FLAGS; i++)
        fl->flags[i] = false;
    for (int i = 1, j = 0; i <= count; i++){
        for (int k = 1; argv[i][k] != '\0'; k++, j++)
            fl->flags_char[j] = argv[i][k];
    }
    fill_bool(fl, count_flags);
    check_perm(fl, count_flags);
    free(fl->flags_char);
    return fl;
}
