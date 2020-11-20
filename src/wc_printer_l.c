#include "uls.h"

static char *flag_T (time_t time) {
    char *str;
    str = mx_substr(ctime(&(time)), 4, 16);
    return str;
}/*--------------------------------------------------------------------------*/
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

}/*--------------------------------------------------------------------------*/
static inline void printPerms_firstChar(struct stat st) {
    if ((st.st_mode & S_IFDIR) == S_IFDIR)
        mx_printchar('d');
    else if ((st.st_mode & S_IFIFO) == S_IFIFO)
        mx_printchar('p');
    else if ((st.st_mode & S_IFCHR) == S_IFCHR)
        mx_printchar('c');
    else if ((st.st_mode & S_IFBLK) == S_IFBLK)
        mx_printchar('b');
    else if ((st.st_mode & S_IFLNK) == S_IFLNK)
        mx_printchar('l');
    else if ((st.st_mode & S_IFSOCK) == S_IFSOCK)
        mx_printchar('s');
    else
        mx_printchar('-');
}/*--------------------------------------------------------------------------*/
static inline void printPerms_lastChar(char *p) {
    if (listxattr(p, NULL, 0, XATTR_NOFOLLOW) > 0)
        mx_printstr("@");
    else if (acl_get_file(p, ACL_TYPE_EXTENDED) != NULL)
        mx_printstr("+");
    else
        mx_printstr(" ");
}/*--------------------------------------------------------------------------*/
static inline void printPerms(struct stat st, char *p) {
    printPerms_firstChar(st);

    mx_printstr((st.st_mode & S_IRUSR) ? "r" : "-");
    mx_printstr((st.st_mode & S_IWUSR) ? "w" : "-");
    char t = '-';
    if ((st.st_mode & S_IXUSR) == S_IXUSR)
        t = 'x';
    if ((st.st_mode & S_ISUID) == S_ISUID)
        t = (t = 'x') ? 's' : 'S';
    mx_printchar(t);
    mx_printstr((st.st_mode& S_IRGRP) ? "r" : "-");
    mx_printstr((st.st_mode & S_IWGRP) ? "w" : "-");
    t = '-';
    if ((st.st_mode & S_IXGRP) == S_IXGRP)
        t = 'x';
    if ((st.st_mode & S_ISGID) == S_ISGID)
        t = (t = 'x') ? 's' : 'S';
    mx_printchar(t);
    mx_printstr((st.st_mode& S_IROTH) ? "r" : "-");
    mx_printstr((st.st_mode & S_IWOTH) ? "w" : "-");
    t = '-';
    if ((st.st_mode & S_IXOTH) == S_IXOTH)
        t = 'x';
    if ((st.st_mode & S_ISVTX) == S_ISVTX)
        t = (t = 'x') ? 't' : 'T';
    mx_printchar(t);

    printPerms_lastChar(p);
}/*--------------------------------------------------------------------------*/
static inline void printPermsUtil(struct stat st, char *p, t_lout l) {
    char * str;
    struct passwd* tmp = getpwuid(st.st_uid);
    struct group *tmp_g = getgrgid(st.st_gid);
    //Column 1
    printPerms(st, p);
    //Column 2
    for (int i = l.a_link - wc_getBitDepth(st.st_nlink); i >= 0; i--)
        mx_printchar(' ');
    mx_printint(st.st_nlink);
    //Column 3
    for (int i = l.b_owner - mx_strlen(tmp->pw_name); i >= 0; i--)
        mx_printchar(' ');
    mx_printstr(tmp->pw_name);
    // Column 4
    for (int i = l.c_group - mx_strlen(tmp_g->gr_name); i >= 0; i--)
        mx_printchar(' ');
    mx_printstr(tmp_g->gr_name);
    // Column 5
    for (int i = l.d_size - wc_getBitDepth(st.st_size); i >= 0; i--)
        mx_printchar(' ');
    mx_printint(st.st_size);
    mx_printstr(" ");
    str = mx_flag_time(st);
    mx_printstr(str);
    free(str);
}/*==========================================================================*/
void wc_printWithL(t_obj **fp, int fp_amt) {
    t_lout l = getSizesForL(fp, fp_amt);

        for(int i = 0; i < fp_amt; i++) {
            printPermsUtil(fp[i]->st, fp[i]->name, l);
            mx_printstr(" ");
            wc_printShortName(fp[i]->name);
            mx_printstr("\n");
        }
         mx_printstr("\n");
}
