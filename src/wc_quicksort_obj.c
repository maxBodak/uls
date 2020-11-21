#include "uls.h"

static void mx_swapObj(t_obj **a, t_obj **b) {
    t_obj *temp = *a;

    *a = *b;
    *b = temp;
}
static int partition(t_obj **arr, int l, int r, bool cmp(t_obj *, t_obj *)) {
    int p = (r + l) / 2;

    while (l < r) {
        for (;cmp(arr[p], arr[l]) && l < p; l++);
        for (;cmp(arr[r], arr[p]) && r > p; r--);
        if (l < r && cmp(arr[l], arr[r])) {
            p = l * (p == r) + r * (p == l) + p * (p != l && p != r);
            mx_swapObj(&arr[l], &arr[r]);
        }
        l += 1 * (l != p);
        r -= 1 * (r != p);
    }
    return p;
}
void mx_quicksortObj(t_obj **arr, int l, int r, bool cmp(t_obj *, t_obj *)) {
    int p;

    if (arr == NULL)
        return;
    if (l < r) {
        p = partition(arr, l, r, cmp);
        mx_quicksortObj(arr, l, p - 1, cmp);
        mx_quicksortObj(arr, p + 1, r, cmp);
    }
}
