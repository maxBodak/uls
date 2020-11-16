#include "uls.h"

t_dir *initDir(char *p) {
    DIR *dp;
    struct dirent *ep;
    int fcount = 0;
    int dcount = 0;
    t_dir *d = NULL;

    dp = opendir (p);
    if (dp != NULL) {
        while ((ep = readdir(dp))) {
            if (ep->d_type == DT_DIR)
                dcount++;
            else if (ep->d_type == DT_REG)
                fcount++;
        }
        closedir (dp);
    }
    d = (t_dir *)malloc(sizeof(t_dir));
    d->file_amt = fcount;
    d->dir_amt = dcount;
    d->dirs = (t_dir **)malloc(sizeof(t_dir *) * dcount);
    d->files = (t_file *)malloc(sizeof(t_file) * fcount);
    return d;
}
t_dir *bigPP(char *p, bool rec) {
    DIR *dp;
    struct dirent *ep;
    t_dir *res = initDir(p);

    if (res) {
        dp = opendir (p);
        for (int i = 0, j = 0; (ep = readdir(dp));) {
            mx_printstr("st\t");
            if (ep->d_type == DT_DIR) {
                if (rec && mx_strcmp(ep->d_name, ".") && mx_strcmp(ep->d_name, "..")) {
                    {mx_printstr(ep->d_name);
                    res->dirs[i] = bigPP(mx_strjoin(p, ep->d_name), 1);}
                stat(ep->d_name, &(res->dirs[i]->st));
                res->dirs[i++]->name = ep->d_name;
                }
            }
            else if (ep->d_type == DT_REG) {
                stat(ep->d_name, &(res->files[i].st));
                res->files[j++].name = ep->d_name;
            }
            mx_printstr("\tend\n");
        }
        closedir (dp);
    }
    return res;
}
char *getFname(char *p) {
    int l = mx_strlen(p) - 1;

    while (l > 0 && p[l] != '/')
        l--;
    p += l;
    return mx_strdup(p);
}
t_file *bigFF(char *p) {
    t_file *f = (t_file *)malloc(sizeof(t_file));

    stat(p, &(f->st));
    f->name = getFname(p);
    return f;
}
