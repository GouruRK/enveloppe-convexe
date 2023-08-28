#include <MLV/MLV_all.h>

#include "../include/graphic.h"
#include "../include/list.h"
#include "../include/struct.h"
#include "../include/tools.h"
#include "../include/convexhull.h"

int main(void) {
    int stop = 0;
    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("ConvexHull", "", 600, 600);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_update_window();

    create_convexhull(&stop);

    MLV_free_window();
}