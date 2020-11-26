#include "uls.h"

void wc_printStats(struct stat st, t_lout l) {
    struct passwd* tmp = getpwuid(st.st_uid);
    struct group *tmp_g = getgrgid(st.st_gid);
    //Column 2 (links)
    for (int i = l.a_link - wc_getBitDepth(st.st_nlink); i >= 0; i--)
        mx_printchar(' ');
    mx_printint(st.st_nlink);
    //Column 3 (owner)
    if (tmp) {
        for (int i = l.b_owner - mx_strlen(tmp->pw_name); i >= 0; i--)
            mx_printchar(' ');
     mx_printstr(tmp->pw_name );
    } else {
        for (int i = l.c_group - wc_getBitDepth(st.st_uid); i >= 0; i--)
            mx_printchar(' ');
        mx_printint(st.st_uid);
    }
    // Column 4 (group)
    if (tmp_g) {
        for (int i = l.c_group - mx_strlen(tmp_g->gr_name); i >= -1; i--)
            mx_printchar(' ');
        mx_printstr(tmp_g->gr_name);
    } else {
        for (int i = l.c_group - wc_getBitDepth(st.st_gid); i >= 0; i--)
            mx_printchar(' ');
        mx_printint(st.st_gid);
    }
    // Column 5 (size)
    for (int i = l.d_size - wc_getBitDepth(st.st_size); i >= -1; i--)
        mx_printchar(' ');
    mx_printint(st.st_size);
    mx_printchar(' ');
}
