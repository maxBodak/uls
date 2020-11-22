#include "uls.h"

bool *cf_isatty(bool *fls) {
    bool *flags = fls;

    if (!isatty(fileno(stdin))) {
        flags[G] = false;
        if (flags[l] == false &&
            flags[m] == false &&
            flags[C] == false &&
            flags[one] == false) {
            flags[one] = true;
        }
        flags[tty] = true;
    }
    return flags;
}


//{
//puts(isatty(fileno(stdin))
//? "stdin is tty"
//: "stdin is not tty");
//return 0;
//}
