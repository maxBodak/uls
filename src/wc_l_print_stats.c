#include "uls.h"

static inline void printSize(struct stat st, t_lout l) {
    // Column 5 (size)
    if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode) || S_ISLNK(st.st_mode)) {
        int mjr = major(st.st_rdev);
        int mnr = minor(st.st_rdev);

        if (major(st.st_rdev)) {
            for (int i = l.d_size - wc_getBitDepth(mjr); i >= 0; i--)
                mx_printchar(' ');
            mx_printint(mjr);
            mx_printstr(", ");
        } else {
            for (int i = l.d_size - wc_getBitDepth(mjr); i >= 0; i--)
                mx_printchar(' ');
        }
        for (int i = l.d_size - wc_getBitDepth(mnr); i >= 0; i--)
            mx_printchar(' ');
        mx_printint(mnr);
    } else {
        mx_printint(st.st_size);
        for (int i = l.d_size - wc_getBitDepth(st.st_size); i >= -1; i--)
            mx_printchar(' ');
    }
    mx_printchar(' ');
}
void wc_printStats(struct stat st, t_lout l) {
    struct passwd* tmp = getpwuid(st.st_uid);
    struct group *tmp_g = getgrgid(st.st_gid);
    //Column 2 (links)
    for (int i = l.a_link - wc_getBitDepth(st.st_nlink); i >= 0; i--)
        mx_printchar(' ');
    mx_printint(st.st_nlink);
    //Column 3 (owner)
    mx_printchar(' ');
    if (tmp) {
        mx_printstr(tmp->pw_name);
        for (int i = l.b_owner - mx_strlen(tmp->pw_name); i >= 0; i--)
            mx_printchar(' ');
    } else {
        mx_printint(st.st_uid);
        for (int i = l.c_group - wc_getBitDepth(st.st_uid); i >= 0; i--)
            mx_printchar(' ');
    }
    // Column 4 (group)
    mx_printchar(' ');
    if (tmp_g) {
        mx_printstr(tmp_g->gr_name);
        for (int i = l.c_group - mx_strlen(tmp_g->gr_name); i >= -1; i--)
            mx_printchar(' ');
    } else {
        mx_printint(st.st_gid);
        for (int i = l.c_group - wc_getBitDepth(st.st_gid); i >= 0; i--)
            mx_printchar(' ');
    }
    printSize(st, l);
}
