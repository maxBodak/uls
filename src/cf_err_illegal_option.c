#include"uls.h"

void cf_err_illegal_option(char *flags_char) {
    char all_flags[38] = "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1@";

    for (int i = 0; flags_char[i]; i++) {
        for (int j = 0; j <= 38; j++) {
            if (j == 38) {
                mx_printerr("uls: illegal option -- ");
                mx_printerr(&flags_char[i]);
                mx_printerr("\n");
                mx_printerr("usage: uls [-");
                mx_printerr(FLAG_LIST);
                mx_printerr("] [file ...]\n");
                exit(1);
            }
            if (flags_char[i] == all_flags[j])
                break;
        }
    }
}
