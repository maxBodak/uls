#include "uls.h"

int main(int argc, char ** argv) {
//Parsing
    bool *fl = cf_bool_manip(argc, argv);
    t_path *p = wc_getPaths(argc, argv);
//Fetching
    t_data *d = wc_fetchData(p, fl);
//Sorting
    cf_flags_check (d, fl);
//Printing
    wc_printResult(d, fl);
//Cleanup
    wc_freePath(p);
    wc_freeData(d);
    free(fl);
//    system("leaks -q uls");
    return 0;
}
