#include "uls.h"

static void colorDir(struct stat sb) {
    if ((sb.st_mode & S_IWOTH) == S_IWOTH
        && (sb.st_mode & S_ISVTX) == S_ISVTX)
        mx_printstr(DIR_T);
    else if ((sb.st_mode & S_IWOTH) == S_IWOTH
             && (sb.st_mode & S_IXOTH) == S_IXOTH)
        mx_printstr(DIR_X);
    else
        mx_printstr(BLU);
}

static void colorFile(struct stat sb) {
    if ((sb.st_mode & S_ISUID) == S_ISUID)
        mx_printstr(BLK_F_RED_B );
    else if ((sb.st_mode & S_ISGID) == S_ISGID)
        mx_printstr(BLK_F_CYAN_B);
    else if ((sb.st_mode & S_IXUSR) == S_IXUSR)
        mx_printstr(RED);
    else
        mx_printstr(RESET);
}

void wc_printName(t_obj *obj, bool *fl) {
    if (fl[G]) {
        if (S_ISFIFO(obj->st.st_mode))
            mx_printstr(YEL);
        else if (S_ISCHR(obj->st.st_mode))
            mx_printstr(CHR);
        else if (S_ISBLK(obj->st.st_mode))
            mx_printstr(BLOCK);
        else if (S_ISLNK(obj->st.st_mode))
            mx_printstr(MAG);
        else if (S_ISSOCK(obj->st.st_mode))
            mx_printstr(GRN);
        else if (S_ISDIR(obj->st.st_mode))
            colorDir(obj->st);
        else if (S_ISREG(obj->st.st_mode))
            colorFile(obj->st);
    }
    mx_printstr(obj->s_name);
    mx_printstr(RESET);
}
