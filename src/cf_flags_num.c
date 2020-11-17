#include "uls.h"

static inline t_flags *mem_manip(int count_flags) {
    t_flags *fl = (t_flags *)malloc(sizeof(t_flags));
    fl->flags_char = mx_strnew(count_flags - 1);
    fl->flags = (bool *)malloc(sizeof(bool) * ALL_FLAGS);
    return fl;
}

static inline int cpy_args(int j, const char *argv, char *flags_char){
    for (int i = 1; argv[i] != '\0'; i++, j++) {
        flags_char[j] = argv[i];
    }
    return j;
}

static inline void fill_bool(t_flags *fl, int count_flags) {
    char flag[ALL_FLAGS] = {'R', 'l', '1', 'm', 'C', 'S', 't', 'r', 'p', 'u', 'c', '@', 'e', 'h', 'T'};
    for (int i = 0; i < count_flags; i++) {
        for (int j = 0; j < ALL_FLAGS; j++) {
            if (fl->flags_char[i] == flag[j])
                fl->flags[j] = true;
        }
    }
}

void cf_flags_num (int argc, char *argv[]) {
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
        j = cpy_args(j, argv[i], fl->flags_char);
    }
    fill_bool(fl, count_flags);
//    for(int i = 0; i < ALL_FLAGS; i++)
//        printf("%d\n", fl->flags[i]);
//    printf("\n%d\n", count);
//    printf("%d\n", count_flags);
//    printf("%s\n", fl->flags_char);
}
