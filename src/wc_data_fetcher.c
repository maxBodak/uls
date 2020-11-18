#include "uls.h"

t_data *wc_fetchData(t_path *p, bool rec) {
    int i = 0;
    t_data *res = NULL;

    if(p) {
        res = (t_data *)malloc(sizeof(res));
        res->amt = p->amt;
        res->path = (t_obj **)malloc(sizeof(t_obj *) * p->amt);
        for (int j = 0; j < p->amt; j++)
            if (!p->isdir[j])
                res->path[i++] = wc_getFileInfo(p->path[j]);
        for (int j = 0; j < p->amt; j++)
            if (p->isdir[j])
                res->path[i++] = wc_getDirInfo(p->path[j], rec);
    }
    return res;
}
