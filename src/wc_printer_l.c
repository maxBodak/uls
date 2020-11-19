#include "uls.h"
char *mx_substr(const char *str, int a, int b) {
    char *tmp;
    int j = 0;

    tmp = mx_strnew(b - a + 1);
    for (int i = a; i < b && str[i] != '\0'; i++) {
        tmp[j] = str[i];
        j++;
    }
    return tmp;
}
static char *flag_T (time_t time) {
    char *str;

        str = mx_substr(ctime(&(time)), 4, 16);
    return str;
}
char *mx_flag_time(struct stat buff) {
    time_t sec = time(NULL);
    time_t time = 0;
    char *sub;
    char *tmp;
    char *tmp_2;

    time = buff.st_mtime;
    if (((sec - (time)) > 15778368)) {
        sub = mx_substr(ctime(&(time)), 4, 10);
        tmp = mx_strjoin(sub, "  ");
        free(sub);
        tmp_2 = mx_substr(ctime(&(time)), 20, 24);
        sub = mx_strjoin(tmp, tmp_2);
        free(tmp_2);
        free(tmp);
        return sub;
    }

    return flag_T(time);
}
static inline void printPermsUtil(struct stat st, char *p) {
    char * str;
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
    mx_printstr(" ");
    str = mx_flag_time(st);
    mx_printstr(str);
    // str = mx_itoa(st.st_uid);
    // mx_printstr(str);
    // free(str);
    // str = mx_itoa(st.st_gid);
    // mx_printstr(str);
    free(str);
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
