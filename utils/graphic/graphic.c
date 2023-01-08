/**
 * @file graphic.c
 * @author Quentin Laborde - Kies Rémy
 * @brief Affiche le menu
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../utils.h"

/* Ligne de compilation :
clang -c ../args/errs.c -Wall -std=c17
clang graphic.c errs.o -Wall -std=c17 -o graph -lMLV
*/

#define BORDER 8
#define LENGTH_DISTRIB 2
#define LENGTH_SHAPES 5
#define LENGTH_DISPLAY 2

void exit_function(void* data) {
    int* arret = (int*)data;
    *arret = 1;
}

int isClick(x, y, minX, maxX, minY, maxY) {
    return (x > minX && x < maxX) && (y > minY && y < maxY);
}

Button button_create(int x, int y, char* text) {
    Button but;
    but.text = (char*)malloc(strlen(text) * sizeof(char));
    if (but.text == NULL) {
        errAlloc();
        exit(1);
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
    // if (x < but.x || x > but_max_x || y < but.y || y > but_max_y) {
    //     return 0;
    // }
    // return 1;
    return isClick(x, y, but.x, but_max_x, but.y, but_max_y);
}

int button_onclick_tab(Button tab[], int size, int x, int y) {
    for (int i = 0; i < size; i++) {
        // int but_max_x = tab[i].x + tab[i].width + BORDER;
        // int but_max_y = tab[i].y + tab[i].height + BORDER;
        // est dans le bouton
        // if (!(x < tab[i].x || x > but_max_x || y < tab[i].y || y > but_max_y)) {
        //     return i;
        // }
        if (button_onclick(tab[i], x, y)) {
            return i;
        }
    }
    return -1;
}

void button_draw_Wborder(Button but, MLV_Color color_text,
                         MLV_Color color_border) {
    MLV_draw_rectangle(but.x, but.y, but.width + BORDER, but.height + BORDER,
                       color_border);
    MLV_draw_text(but.x + BORDER / 2, but.y + BORDER / 2, but.text,
                  color_text);
}

void button_draw_WOborder(Button but, MLV_Color color_text) {
    MLV_draw_text(but.x + BORDER / 2, but.y + BORDER / 2, but.text,
                  color_text);
}

void button_draw_tab(Button tab[], int size,
                     MLV_Color color[]) {
    for (int i = 0; i < size; i++) {
        // fprintf(stderr, "x:%d y:%d w:%d h:%d val%d\n", tab[i].x, tab[i].y, tab[i].width, tab[i].height, val[i]);
        button_draw_Wborder(tab[i], color[tab[i].value], color[tab[i].value]);
    }
}

void switch_(Button tab[], int size, int index) {
    for (int i = 0; i < size; i++) {
        if (i == index) {
            tab[i].value = 1;
        } else {
            tab[i].value = 0;
        }
    }
}

void window_param_preclose(void) {
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_text(150, 50, "cc", MLV_COLOR_GREEN);
    printf("%s Fin d'execusion %s\n", GREEN, RESET);
    MLV_actualise_window();
    MLV_wait_seconds(2);
}

void init_window_param(int* window_width, int* window_height) {
    int stop = 0, pressed = 0;
    Button tab_button_distrib[LENGTH_DISTRIB], tab_button_shapes[LENGTH_SHAPES], tab_button_display[LENGTH_DISPLAY];
    MLV_Color tab_color[2] = {MLV_COLOR_RED,
                              MLV_COLOR_DARKGREEN};

    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("Setting convex hull", "Setting", 600, 400);

    /////////
    MLV_Input_box *input_box = NULL, *input1, *input2, *input3;
    MLV_Event event = MLV_NONE;
    int x = 0,
        y = 0;  // Position de la souris
    char* text = NULL;

    char *choice, *endPtr;
    input1 = MLV_create_input_box(
        95, 300,
        200, 20,
        MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_LIGHT_GRAY,
        "Largeur de la fenetre: ",
        &choice);
    input2 = MLV_create_input_box(
        305, 300,
        200, 20,
        MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_LIGHT_GRAY,
        "Hauteur de la fenetre: ");
    // input3 = MLV_create_input_box(
    //     200, 300,
    //     100, 50,
    //     MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_WHITE,
    //     "Rayon: ");
    // MLV_draw_all_input_boxes();
    /////////
    fprintf(stderr, "cc\n");
    tab_button_distrib[0] = button_create(250, 50, "Placer à la souris");
    tab_button_distrib[1] = button_create(250, 100, "Forme prédéfini");

    tab_button_shapes[0] = button_create(450, 50, "Cercle");
    tab_button_shapes[1] = button_create(450, 100, "Carré");
    tab_button_shapes[2] = button_create(450, 150, "Rectangle");
    tab_button_shapes[3] = button_create(450, 200, "Ellipse");

    tab_button_display[1] = button_create(50, 50, "Automatique");
    tab_button_display[0] = button_create(50, 100, "Avec delai");

    while (!stop) {
        MLV_clear_window(MLV_COLOR_LIGHT_GRAY);
        // MLV_draw_text(150, 20, "%d", MLV_COLOR_DARKGREEN, MLV_get_time());
        MLV_draw_text(240, 25, "Mode de distribution :", MLV_COLOR_DARKGREEN);
        button_draw_tab(tab_button_distrib, LENGTH_DISTRIB, tab_color);
        if (tab_button_distrib[1].value == 1) {
            MLV_draw_text(40, 25, " Formes prédéfinies :", MLV_COLOR_DARKGREEN);
            MLV_draw_text(440, 25, " Mode d'afficahge :", MLV_COLOR_DARKGREEN);
            button_draw_tab(tab_button_display, LENGTH_DISPLAY, tab_color);
            button_draw_tab(tab_button_shapes, LENGTH_SHAPES, tab_color);
        }
        //////////////////////
        event = MLV_get_event(
            NULL, NULL, NULL,
            &text, &input_box,
            NULL, NULL, NULL,
            NULL);

        //////////////////////
        if (event == MLV_INPUT_BOX) {
            if (input_box == input1) {
                fprintf(stderr, "Largeur");
                if (strtol(text, &endPtr, 10)) {
                    *window_width = (int)strtol(text, &endPtr, 10);
                }
            } else if (input_box == input2) {
                fprintf(stderr, "hateur");
                if (strtol(text, &endPtr, 10)) {
                    *window_height = (int)strtol(text, &endPtr, 10);
                }
            }
        }
        MLV_draw_input_box(input1);
        MLV_draw_input_box(input2);

        //////////////////////
        MLV_actualise_window();
        MLV_update_window();

        if ((MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) && pressed == 0) {
            pressed = 1;
            MLV_get_mouse_position(&x, &y);
            int val = button_onclick_tab(tab_button_distrib, LENGTH_DISTRIB, x, y);
            int val2 = button_onclick_tab(tab_button_display, LENGTH_DISPLAY, x, y);
            int val3 = button_onclick_tab(tab_button_shapes, LENGTH_SHAPES, x, y);
            if (val != -1) {
                switch_(tab_button_distrib, LENGTH_DISTRIB, val);
            } else if (val2 != -1 && tab_button_distrib[1].value == 1) {
                switch_(tab_button_display, LENGTH_DISPLAY, val2);
            } else if (val3 != -1 && tab_button_distrib[1].value == 1) {
                switch_(tab_button_shapes, LENGTH_SHAPES, val3);
            }
        }
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_RELEASED) {
            pressed = 0;
        }
    }
    window_param_preclose();
    MLV_free_window();
}

int main(void) {
    int window_width = 1000, window_height = 1000;
    init_window_param(&window_width, &window_height);
    printf("w:%d h:%d", window_width, window_height);
    return 0;
}