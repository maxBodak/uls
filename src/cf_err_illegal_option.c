#include"uls.h"

void cf_arr_illegal_option(char *flags_char) {
    char all_flags[38] = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1";

    for (int i = 0; flags_char[i]; i++) {
        for (int j = 0; j <= 38; j++) {
            if (j == 38) {
                mx_printstr("ls: illegal option -- ");
                mx_printchar(flags_char[i]);
                mx_printchar('\n');
                mx_printstr("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
                exit(1);
            }
            if (flags_char[i] == all_flags[j])
                break;
        }
    }
}
