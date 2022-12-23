// #include "main.h"

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BORDER 8

typedef struct button {
    char* text;
    int x;
    int y;
    int height;
    int width;
} Button;

void exit_function(void* data);

void exit_function(void* data) {
    int* arret = (int*)data;
    *arret = 1;
}

int button_onclick(Button but, int x, int y) {
    // 1 si clické sinon 0
    int but_max_x = but.x + but.width + BORDER;
    int but_max_y = but.y + but.height + BORDER;
    if (x < but.x || x > but_max_x || y < but.y || y > but_max_y) {
        return 0;
    }
    return 1;
}

void init_window_param() {
    int stop = 0, pressed = 0;
    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("Setting convex hull", "Setting", 300, 300);

    Button but;
    char* word = "Je m'appelle Michel";
    but.text = (char*)malloc(strlen(word) * sizeof(char));
    strcpy(but.text, word);
    MLV_get_size_of_text(but.text, &but.width, &but.height);
    but.x = 100, but.y = 100;

    while (!stop) {
        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_draw_text(150, 50, "%d", MLV_COLOR_GREEN, MLV_get_time());
        MLV_draw_rectangle(but.x, but.y, but.width + BORDER, but.height + BORDER, MLV_COLOR_RED);
        MLV_draw_text(but.x + BORDER / 2, but.y + BORDER / 2, but.text, MLV_COLOR_GREEN);
        MLV_update_window();
        if ((MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) && pressed == 0) {
            pressed = 1;
            int x = 0, y = 0;
            MLV_get_mouse_position(&x, &y);
            printf("%d\n", button_onclick(but, x, y));
        }
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_RELEASED) {
            pressed = 0;
        }
    }
    MLV_draw_text(150, 50, "cc", MLV_COLOR_GREEN);
    MLV_actualise_window();
    MLV_wait_seconds(2);
    MLV_free_window();
}

int main(int argc, char* argv[]) {
    init_window_param();
    return 0;
}
