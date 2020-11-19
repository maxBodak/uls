#include "uls.h"
static inline void printPermsUtil(struct stat st, char *p) {
    mx_printstr((S_ISDIR(st.st_mode)) ? "d" : "-");
    mx_printstr((st.st_mode & S_IRUSR) ? "r" : "-");
    mx_printstr((st.st_mode & S_IWUSR) ? "w" : "-");
    mx_printstr((st.st_mode & S_IXUSR) ? "x" : "-");
    mx_printstr((st.st_mode& S_IRGRP) ? "r" : "-");
    mx_printstr((st.st_mode & S_IWGRP) ? "w" : "-");
    mx_printstr((st.st_mode & S_IXGRP) ? "x" : "-");
    mx_printstr((st.st_mode& S_IROTH) ? "r" : "-");
    mx_printstr((st.st_mode & S_IWOTH) ? "w" : "-");
    mx_printstr((st.st_mode & S_IXOTH) ? "x" : "-");
    mx_printstr(listxattr(p, NULL, 0, XATTR_NOFOLLOW) > 0 ? "@" : " ");
    mx_printstr(" ");
    mx_printint(st.st_nlink);
}/*--------------------------------------------------------------------------*/
void wc_printWithL(t_obj **fp, int fp_amt) {
        for(int i = 0; i < fp_amt; i++) {
            printPermsUtil(fp[i]->st, fp[i]->name);
            mx_printstr("\t");
            printShortName(fp[i]->name);
            mx_printstr("\n");
        }
         mx_printstr("\n");
}
