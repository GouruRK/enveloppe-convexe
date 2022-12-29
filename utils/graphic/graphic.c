#include "../utils.h"

#define BORDER 8
#define LENGTH_DISTRIB 3
#define LENGTH_SHAPES 5
#define LENGTH_DISPLAY 2

static const char red[] = "\x1b[31m";
static const char green[] = "\x1b[32m";
static const char cyan[] = "\x1b[36m";
static const char reset[] = "\x1b[0m";

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

int button_onclick(Button but, int x, int y) {
    // 1 si clické sinon 0
    int but_max_x = but.x + but.width + BORDER;
    int but_max_y = but.y + but.height + BORDER;
    if (x < but.x || x > but_max_x || y < but.y || y > but_max_y) {
        return 0;
    }
    return 1;
}

int button_onclick_tab(Button tab[], int size, int x, int y) {
    for (int i = 0; i < size; i++) {
        int but_max_x = tab[i].x + tab[i].width + BORDER;
        int but_max_y = tab[i].y + tab[i].height + BORDER;
        // est dans le bouton
        if (!(x < tab[i].x || x > but_max_x || y < tab[i].y || y > but_max_y)) {
            return i;
        }
    }
    return -1;
}

void button_draw_Wborder(Button but, MLV_Color color_text, MLV_Color color_border) {
    MLV_draw_rectangle(but.x, but.y, but.width + BORDER, but.height + BORDER, color_border);
    MLV_draw_text(but.x + BORDER / 2, but.y + BORDER / 2, but.text, color_text);
}

void button_draw_WOborder(Button but, MLV_Color color_text) {
    MLV_draw_text(but.x + BORDER / 2, but.y + BORDER / 2, but.text, color_text);
}

void button_draw_tab(Button tab[], int val[], int size, MLV_Color color[]) {
    for (int i = 0; i < size; i++) {
        // fprintf(stderr, "x:%d y:%d w:%d h:%d val%d\n", tab[i].x, tab[i].y, tab[i].width, tab[i].height, val[i]);
        button_draw_Wborder(tab[i], color[val[i]], color[val[i]]);
    }
}

void switch_(int val[], int size, int index) {
    for (int i = 0; i < size; i++) {
        if (i == index) {
            val[i] = 1;
        } else {
            val[i] = 0;
        }
    }
}

void window_param_preclose(void) {
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_text(150, 50, "cc", MLV_COLOR_GREEN);
    printf("%s Fin d'execusion %s\n", green, reset);
    MLV_actualise_window();
    MLV_wait_seconds(2);
}

void init_window_param(void) {
    int stop = 0, pressed = 0, x = 0, y = 0;
    Button tab_button_distrib[LENGTH_DISTRIB], tab_button_shapes[LENGTH_SHAPES], tab_button_display[LENGTH_DISPLAY];
    int tab_value_distrib[LENGTH_DISTRIB] = {}, tab_value_shapes[LENGTH_SHAPES] = {}, tab_value_display[LENGTH_DISPLAY] = {};
    MLV_Color tab_color[2] = {MLV_COLOR_RED,
                              MLV_COLOR_GREEN};

    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("Setting convex hull", "Setting", 600, 300);

    MLV_draw_text(40, 75, "Mode de distribution :", MLV_COLOR_GREEN);
    tab_button_distrib[0] = button_create(50, 100, "Placer à la souris");
    tab_button_distrib[1] = button_create(50, 150, "Aléatoire controlé");
    tab_button_distrib[2] = button_create(50, 200, "Forme prédéfini");

    MLV_draw_text(240, 75, " Formes prédéfinies :", MLV_COLOR_GREEN);
    tab_button_shapes[0] = button_create(450, 100, "Cercle");
    tab_button_shapes[1] = button_create(450, 150, "Carré");
    tab_button_shapes[2] = button_create(450, 200, "Rectangle");
    tab_button_shapes[3] = button_create(450, 250, "Ellipse");
    tab_button_shapes[4] = button_create(250, 250, "Rayon croissant");

    MLV_draw_text(240, 75, " Mode d'afficahge :", MLV_COLOR_GREEN);
    tab_button_display[0] = button_create(250, 100, "Point par Point");
    tab_button_display[1] = button_create(250, 150, "Automatique");

    while (!stop) {
        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_draw_text(150, 20, "%d", MLV_COLOR_GREEN, MLV_get_time());
        button_draw_tab(tab_button_distrib, tab_value_distrib, LENGTH_DISTRIB, tab_color);
        button_draw_tab(tab_button_display, tab_value_display, LENGTH_DISPLAY, tab_color);
        if (tab_value_distrib[2] == 1) {
            button_draw_tab(tab_button_shapes, tab_value_shapes, LENGTH_SHAPES, tab_color);
        }
        MLV_actualise_window();
        MLV_update_window();

        if ((MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) && pressed == 0) {
            pressed = 1;
            MLV_get_mouse_position(&x, &y);
            int val = button_onclick_tab(tab_button_distrib, LENGTH_DISTRIB, x, y);
            int val2 = button_onclick_tab(tab_button_display, LENGTH_DISPLAY, x, y);
            int val3 = button_onclick_tab(tab_button_shapes, LENGTH_SHAPES, x, y);
            if (val != -1) {
                switch_(tab_value_distrib, LENGTH_DISTRIB, val);
            } else if (val2 != -1) {
                switch_(tab_value_display, LENGTH_DISPLAY, val2);
            } else if (val3 != -1 && tab_value_distrib[2] == 1) {
                switch_(tab_value_shapes, LENGTH_SHAPES, val3);
            }
        }
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_RELEASED) {
            pressed = 0;
        }
    }
    window_param_preclose();
    MLV_free_window();
}
