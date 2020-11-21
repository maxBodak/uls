#include "uls.h"

bool * cf_cmp_flags(bool *fls) {
    bool *flags = fls;
    if (flags[f] == true) {
        flags[a] = true;
        flags[c] = false;
        flags[t] = false;
        flags[u] = false;
        flags[S] = false;
        flags[U] = false;
        flags[r] = false;
    }
    if (flags[S] == true)
        flags[t] = false;
    if (flags[a] == true)
        flags[A] = false;
    return flags;
}
