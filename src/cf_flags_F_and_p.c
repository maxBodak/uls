#include "uls.h"

static inline bool dir_type(struct stat sb) {
    if ((sb.st_mode & S_IWOTH) == S_IWOTH
        && (sb.st_mode & S_ISVTX) == S_ISVTX);
//        mx_printstr(DIR_T);
    else if ((sb.st_mode & S_IWOTH) == S_IWOTH
             && (sb.st_mode & S_IXOTH) == S_IXOTH);
//        mx_printstr(DIR_X);
    else
        return true;
    return false;
}

static inline bool file_type(struct stat sb) {
//    if ((sb.st_mode & S_ISUID) == S_ISUID)
//        mx_printstr(BLK_F_RED_B );
//    else if ((sb.st_mode & S_ISGID) == S_ISGID)
//        mx_printstr(BLK_F_CYAN_B);
    if ((sb.st_mode & S_IXUSR) == S_IXUSR)
        return true;
    return false;
//    else
//        mx_printstr(RESET);
}

static inline void cf_add_symvol(t_obj *d, const bool *fl) {
    if (d->type < perm_denied && d->type >= fifo) {
        if (d->type == fifo)
            d->s_name[mx_strlen(d->s_name)] = '|';
//        else if (d->type == chr)
//            d->s_name = cf_rename (d, "*");
//        else if (d->type == blk)
//            d->s_name = cf_rename (d, "|");
        else if (d->type == lnk)
            d->s_name[mx_strlen(d->s_name)] = '@';
        else if (d->type == sock)
            d->s_name[mx_strlen(d->s_name)] = '=';
        else if (d->type == dir) {
            if (dir_type(d->st))
                d->s_name[mx_strlen(d->s_name)] = '/';
        }
        else if (d->type == file && !fl[p])
            if(file_type(d->st))
                d->s_name[mx_strlen(d->s_name)] = '*';
    }
}

void cf_flag_F_and_p(t_obj **d, int d_amt, const bool *fl) {
    if (fl[F] || fl[p]) {
        for(int i = 0; i < d_amt; i++)
            cf_add_symvol(d[i], fl);
        for (int i = 0; i < d_amt; i++)
            if (d[i]->kids_amt)
                cf_flag_F_and_p(d[i]->kids, d[i]->kids_amt, fl);
    }
}
