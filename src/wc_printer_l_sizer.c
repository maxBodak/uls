#include "uls.h"

t_lout getSizesForL(t_obj **fp, int fp_amt) {
    t_lout r;
    struct passwd* tmp = getpwuid(fp[0]->st.st_uid);
    struct group *tmp_g = getgrgid(fp[0]->st.st_gid);
    int link = fp[0]->st.st_nlink;
    int size = fp[0]->st.st_size;

    r.b_owner = mx_strlen(tmp->pw_name);
    r.c_group = mx_strlen(tmp_g->gr_name);
    for (int i = 1; i < fp_amt; i++) {
        if (link < fp[i]->st.st_nlink)
            link = fp[i]->st.st_nlink;
        tmp = getpwuid(fp[i]->st.st_uid);
        if (r.b_owner < mx_strlen(tmp->pw_name))
            r.b_owner = mx_strlen(tmp->pw_name);
        tmp_g = getgrgid(fp[i]->st.st_gid);
        if (r.c_group < mx_strlen(tmp_g->gr_name))
            r.c_group = mx_strlen(tmp_g->gr_name);
        if (size < fp[i]->st.st_size)
            size = fp[i]->st.st_size;
    }
    r.a_link = wc_getBitDepth(link);
    r.d_size = wc_getBitDepth(size);
    return r;
}
