#include"uls.h"

static void mx_swapObj(t_obj **a, t_obj **b) {
    t_obj *temp = *a;

    *a = *b;
    *b = temp;
}

static int partition(t_obj **arr, int l, int r) {
    int p = (r + l) / 2;

    while (l < r) {
        for (;mx_strcmp(arr[l]->s_name,arr[p]->s_name) < 0 && l < p; l++);
        for (;mx_strcmp(arr[l]->s_name,arr[p]->s_name) > 0 && r > p; r--);
        if (l < r && mx_strcmp(arr[l]->s_name,arr[r]->s_name) > 0) {
            p = l * (p == r) + r * (p == l) + p * (p != l && p != r);
            mx_swapObj(&arr[l], &arr[r]);
        }
        l += 1 * (l != p);
        r -= 1 * (r != p);
    }
    return p;
}
void mx_quicksortObj(t_obj **arr, int left, int right) {
    int p;

    if (arr == NULL)
        return;
    if (left < right) {
        p = partition(arr, left, right);
        mx_quicksortObj(arr, left, p - 1);
        mx_quicksortObj(arr, p + 1, right);
    }
}
void cf_not_flag_f(t_obj **d, int d_amt, const bool *fl) {
    //t_obj *buf = NULL;

    if (!fl[f]) {
        mx_quicksortObj(d, 0, d_amt - 1);
        for (int i = 0; i < d_amt; i++)
            if (d[i]->kids_amt)
                cf_not_flag_f(d[i]->kids, d[i]->kids_amt, fl);
    }
        // for (int j = 0; j < d_amt; j++) {
        //     for (int i = 0; i < d_amt - 1; i++) {
        //         if (mx_strcmp(d[i]->name, d[i + 1]->name) > 0) {
        //             buf = d[i];
        //             d[i] = d[i + 1];
        //             d[i + 1]= buf;
        //             i = 0;
        //         }
        //         if (d[i]->kids)
        //             cf_not_flag_f(d[i]->kids, d[i]->kids_amt, fl);
        //     }
        // }
}
