#include "uls.h"

static inline void printTime(struct stat st, bool *fl) {
   time_t sec = time(NULL);
    time_t time = 0;
    char *sub;
    char *tmp;
    char *tmp_2;

    time = fl[c] ? st.st_ctime : 
            fl[u] ? st.st_atime : 
            fl[U] ? st.st_birthtime : st.st_mtime;
    if (((sec - (time)) > 15778368)) {
        sub = mx_substr(ctime(&(time)), 4, 10);
        tmp = mx_strjoin(sub, "  ");
        free(sub);
        tmp_2 = mx_substr(ctime(&(time)), 20, 24);
        sub = mx_strjoin(tmp, tmp_2);
        free(tmp_2);
        free(tmp);
        mx_printstr(sub);
    }
    else {
        sub = mx_substr(ctime(&(time)), 4, 16); 
        mx_printstr(sub);
        free(sub);
    }
}/*--------------------------------------------------------------------------*/
static inline void printPerms_firstChar(struct stat st) {
    mx_printchar(S_ISBLK(st.st_mode) ? 'b' :
                    S_ISCHR(st.st_mode) ? 'c' :
                    S_ISDIR(st.st_mode) ? 'd' :
                    S_ISSOCK(st.st_mode) ? 's' :
                    S_ISFIFO(st.st_mode) ? 'p' :
                    S_ISLNK(st.st_mode) ? 'l' : '-');
}/*--------------------------------------------------------------------------*/
static inline void printPerms_lastChar(char *p) {
    mx_printchar(listxattr(p, NULL, 0, XATTR_NOFOLLOW) > 0 ? ('@') :
                    acl_get_file(p, ACL_TYPE_EXTENDED) != NULL ? '+' : ' ');
}/*--------------------------------------------------------------------------*/
static inline void printPerms(struct stat st, char *p) {
    printPerms_firstChar(st);
    //Chars 2 & 3
    mx_printchar((st.st_mode & S_IRUSR) ? 'r' : '-');
    mx_printchar((st.st_mode & S_IWUSR) ? 'w' : '-');
    //Char 4
    mx_printchar((st.st_mode & S_IXUSR) ?
             ((st.st_mode & S_ISUID) ? 's' : 'x') :
             ((st.st_mode & S_ISUID) ? 'S' : '-'));
    //Chars 5 & 6
    mx_printchar((st.st_mode& S_IRGRP) ? 'r' : '-');
    mx_printchar((st.st_mode & S_IWGRP) ? 'w' : '-');
    //Char 7
    mx_printchar((st.st_mode & S_IXGRP) ?
             ((st.st_mode & S_ISGID) ? 's' : 'x') :
             ((st.st_mode & S_ISGID) ? 'S' : '-'));
    //char 8 & 9
    mx_printchar((st.st_mode& S_IROTH) ? 'r' : '-');
    mx_printchar((st.st_mode & S_IWOTH) ? 'w' : '-');
    //Char 10
    mx_printchar((st.st_mode & S_IXOTH) ?
             ((st.st_mode & S_ISTXT) ? 't' : 'x') :
             ((st.st_mode & S_ISTXT) ? 'T' : '-'));
    printPerms_lastChar(p);
}/*--------------------------------------------------------------------------*/
static inline void printStats(struct stat st, t_lout l) {
    struct passwd* tmp = getpwuid(st.st_uid);
    struct group *tmp_g = getgrgid(st.st_gid);
    //Column 2 (links)
    for (int i = l.a_link - wc_getBitDepth(st.st_nlink); i >= 0; i--)
        mx_printchar(' ');
    mx_printint(st.st_nlink);
    //Column 3 (owner)
    for (int i = l.b_owner - mx_strlen(tmp->pw_name); i >= 0; i--)
        mx_printchar(' ');
    mx_printstr(tmp->pw_name);
    // Column 4 (group)
    for (int i = l.c_group - mx_strlen(tmp_g->gr_name); i >= -1; i--)
        mx_printchar(' ');
    mx_printstr(tmp_g->gr_name);
    // Column 5 (size)
    for (int i = l.d_size - wc_getBitDepth(st.st_size); i >= -1; i--)
        mx_printchar(' ');
    mx_printint(st.st_size);
    mx_printchar(' ');
}/*==========================================================================*/
 void wc_printWithL(t_obj **fp, int fp_amt, bool *fl) {
    t_lout spaces = getSizesForL(fp, fp_amt);

    mx_printstr("total ");
    mx_printint(spaces.total);
    mx_printchar('\n');
        for(int i = 0; i < fp_amt; i++) {
            printPerms(fp[i]->st, fp[i]->path_name);
            printStats(fp[i]->st, spaces);
            printTime(fp[i]->st, fl);
            mx_printstr(" ");
            wc_printName(fp[i], fl);
            mx_printstr("\n");
        }
}
