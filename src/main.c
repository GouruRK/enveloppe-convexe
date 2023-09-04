#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <time.h>

#include "../include/graphic.h"
#include "../include/list.h"
#include "../include/struct.h"
#include "../include/tools.h"
#include "../include/convexhull.h"

#define WIDTH 600
#define HEIGHT 600

int main(void) {
    srand(time(NULL));
    Window win = create_window_data(WIDTH, HEIGHT);
    int stop = 0;
    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("ConvexHull", "", WIDTH, HEIGHT);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_update_window();

    create_convexhull(&stop, 500, rising_sphere, &win);

    MLV_free_window();
}