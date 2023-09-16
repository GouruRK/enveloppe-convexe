#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "../include/convexhull.h"
#include "../include/graphic.h"
#include "../include/list.h"
#include "../include/menu.h"
#include "../include/struct.h"
#include "../include/tools.h"

int main(void) {
    srand(time(NULL));
    int stop = 0;
    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("ConvexHull", "", WIDTH, HEIGHT);
    MLV_clear_window(MLV_COLOR_LIGHT_GRAY);
    
    Args args = menu(&stop);
    if (stop) {
        MLV_free_window();
        return 0;
    }

    MLV_change_window_size(args.w_width, args.w_height);
    Window win = create_window_data(args.w_width, args.w_height);

    Parameters param = {
        .factor = args.factor,
        .nb_point = args.nb_point,
        .radius = args.radius
    };

    args.convex(&stop, param, args.get_point, &win);

    MLV_free_window();
    return 0;
}