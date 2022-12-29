#include <MLV/MLV_all.h>

#include "../utils.h"

/*
clang -c graphic.c -Wall -std=c17 -lMLV
clang -c ./utils/list/list.c -Wall -std=c17
clang -c ./utils/math/math.c list.o -Wall -std=c17
clang enveloppe.c graphic.o -Wall -std=c17 -lMLV
*/

int main(void) {
    init_window_param();
    return 0;
}