#include "uls.h"

t_lout wc_getSizesForL(t_obj **fp, int fp_amt) {
    t_lout r;
    struct passwd* tmp = getpwuid(fp[0]->st.st_uid);
    struct group *tmp_g = getgrgid(fp[0]->st.st_gid);
    int link = fp[0]->st.st_nlink;
    int size = fp[0]->st.st_size;
    r.total = fp[0]->st.st_blocks;
    r.b_owner = mx_strlen_safe(tmp->pw_name);
    r.c_group = mx_strlen_safe(tmp_g->gr_name);
    for (int i = 1; i < fp_amt; i++) {
        //Column 2 (links)
        if (link < fp[i]->st.st_nlink)
            link = fp[i]->st.st_nlink;
        //Column 3 (owner)
        tmp = getpwuid(fp[i]->st.st_uid);
        if (tmp && r.b_owner < mx_strlen_safe(tmp->pw_name))
            r.b_owner = mx_strlen_safe(tmp->pw_name);
        else if (!tmp && r.b_owner < wc_getBitDepth(fp[i]->st.st_uid))
            r.b_owner = wc_getBitDepth(fp[i]->st.st_uid);
        //Column 4 (group)
        tmp_g = getgrgid(fp[i]->st.st_gid);
        if (tmp_g && r.c_group < mx_strlen_safe(tmp_g->gr_name))
            r.c_group = mx_strlen_safe(tmp_g->gr_name);
        else if (!tmp_g && r.c_group < wc_getBitDepth(fp[i]->st.st_gid))
            r.c_group = wc_getBitDepth(fp[i]->st.st_gid);
        // Column 5 (size)
        if (fp[i]->type == chr || fp[i]->type == blk || fp[i]->type == sock) {
            if ( size < 2 + wc_getBitDepth(major(fp[i]->st.st_rdev)) + 
                            wc_getBitDepth(minor(fp[i]->st.st_rdev)))
                size += major(fp[i]->st.st_rdev) + 2 + minor(fp[i]->st.st_rdev);
        } else {
            if (size < fp[i]->st.st_size)
                size = fp[i]->st.st_size;
        }
            r.total += fp[i]->st.st_blocks;
    }
    r.a_link = wc_getBitDepth(link);
    r.d_size = wc_getBitDepth(size);
    return r;
}
