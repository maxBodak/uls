#include "uls.h"


static inline void printPermsUtil(struct stat st, char *p) {
    //char * str;
    struct passwd* tmp = getpwuid(st.st_uid);
    struct group *tmp_g = getgrgid(st.st_gid);
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
    
    mx_printstr(st.st_nlink < 10 ? " " : "");
    mx_printstr(st.st_nlink < 100 ? " " : "");
    mx_printint(st.st_nlink);

    mx_printstr(" ");
    mx_printstr(tmp->pw_name);
    mx_printstr("  ");
    mx_printstr(tmp_g->gr_name);

    mx_printstr(st.st_size < 10 ? " " : "");
    mx_printstr(st.st_size < 100 ? " " : "");
    mx_printstr(st.st_size < 1000 ? " " : "");
    mx_printstr(st.st_size < 10000 ? " " : "");
    mx_printstr(st.st_size < 100000 ? " " : "");
    mx_printstr(" ");
    mx_printint(st.st_size);
    //mx_printstr(" ");
    //mx_printint(st.st_mtimespec.tv_sec);
    // str = mx_itoa(st.st_uid);
    // mx_printstr(str);
    // free(str);
    // str = mx_itoa(st.st_gid);
    // mx_printstr(str);
    //free(str);
}/*--------------------------------------------------------------------------*/
void wc_printWithL(t_obj **fp, int fp_amt) {
        for(int i = 0; i < fp_amt; i++) {
            printPermsUtil(fp[i]->st, fp[i]->name);
            mx_printstr(" ");
            printShortName(fp[i]->name);
            mx_printstr("\n");
        }
         mx_printstr("\n");
}
