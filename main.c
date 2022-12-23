#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BORDER 8

static const char red[] = "\x1b[31m";
static const char green[] = "\x1b[32m";
static const char cyan[] = "\x1b[36m";
static const char reset[] = "\x1b[0m";

typedef struct button {
    char* text;
    int x;
    int y;
    int height;
    int width;
} Button;

void exit_function(void* data);
void init_window_param();
void window_param_preclose();

Button button_create(int x, int y, char* text);
void button_draw_Wborder(Button but, MLV_Color color_text, MLV_Color color_border);
void button_draw_WOborder(Button but, MLV_Color color_text);
int button_onclick(Button but, int x, int y);

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

Button button_create(int x, int y, char* text) {
    Button but;
    but.text = (char*)malloc(strlen(text) * sizeof(char));
    if (but.text == NULL) {
        printf("%s Problème d'allocation mémoire %s\n", red, reset);
    }
    but.x = x, but.y = y;
    strcpy(but.text, text);
    MLV_get_size_of_text(but.text, &but.width, &but.height);
    return but;
}

void button_draw_Wborder(Button but, MLV_Color color_text, MLV_Color color_border) {
    MLV_draw_rectangle(but.x, but.y, but.width + BORDER, but.height + BORDER, color_border);
    MLV_draw_text(but.x + BORDER / 2, but.y + BORDER / 2, but.text, color_text);
    MLV_update_window();
}

void button_draw_WOborder(Button but, MLV_Color color_text) {
    MLV_draw_text(but.x + BORDER / 2, but.y + BORDER / 2, but.text, color_text);
    MLV_update_window();
}

void window_param_preclose() {
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_text(150, 50, "cc", MLV_COLOR_GREEN);
    printf("%s Fin d'execusion %s\n", green, reset);
    MLV_actualise_window();
    MLV_wait_seconds(2);
}

void init_window_param() {
    int stop = 0, pressed = 0, x = 0, y = 0;

    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("Setting convex hull", "Setting", 300, 300);

    Button but;
    but = button_create(100, 100, "Je m'appelle Michel");

    while (!stop) {
        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_draw_text(150, 50, "%d", MLV_COLOR_GREEN, MLV_get_time());
        button_draw_Wborder(but, MLV_COLOR_GREEN, MLV_COLOR_RED);
        MLV_update_window();

        if ((MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) && pressed == 0) {
            pressed = 1;
            MLV_get_mouse_position(&x, &y);
            printf("%d\n", button_onclick(but, x, y));
        }
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_RELEASED) {
            pressed = 0;
        }
    }
    window_param_preclose();
    MLV_free_window();
}

int main(int argc, char* argv[]) {
    init_window_param();
    return 0;
}
