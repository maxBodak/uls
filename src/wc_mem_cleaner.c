#include "uls.h"

void wc_freePath(t_path *p) {
    free(p->isdir);
    for (int i = 0; i < p->amt; i++)
        free(p->path[i]);
    free(p->path);
    free(p);
}/*--------------------------------------------------------------------------*/
void wc_freeObj(t_obj *o) {
    if(o == NULL)
        return;
    free(o->name);
    for (int i = 0; i < o->kids_amt; i++)
        wc_freeObj(o->kids[i]);
    if(o->kids_amt)
        free(o->kids);
    free(o);
}/*--------------------------------------------------------------------------*/
void wc_freeData(t_data *d) {
    if(d == NULL)
        return;

    for (int i = 0; i < d->amt; i++)
        wc_freeObj(d->path[i]);
    free(d->path);
    free(d);
}
