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
#define LENGTH_DISTRIB 3
#define LENGTH_SHAPES 5
#define LENGTH_DISPLAY 2

/**
 * @brief Permet de savoir si l'utilisateur ferme la fenêtre
 * 
 * @param data 
 */
void exit_function(void* data) {
    int* arret = (int*)data;
    *arret = 1;
}

/**
 * @brief Permet de savoir si les coordonnées (`x`, `y`) sont comprises dans
 *        la "boîte" composée des points (`minX`, `minY`), (`maxX`, `maxY`)
 * 
 * @return int Renvoie `1` si (`x`, `y`) est dans la boite, `0` sinon
 */
int isClick(x, y, minX, maxX, minY, maxY) {
    return (x > minX && x < maxX) && (y > minY && y < maxY);
}

/**
 * @brief Permet de créer un bouton
 * 
 * @param x 
 * @param y 
 * @param text 
 * @return Button 
 */
Button createButton(int x, int y, char* text) {
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

/**
 * @brief Permet de savoir si un boutton est cliqué
 * 
 * @param but 
 * @param x 
 * @param y 
 * @return int Renvoie `1` si clické, `0` sinon
 */
int button_onclick(Button but, int x, int y) {
    int but_max_x = but.x + but.width + BORDER;
    int but_max_y = but.y + but.height + BORDER;
    return isClick(x, y, but.x, but_max_x, but.y, but_max_y);
}

/**
 * @brief Renvoie l'indice du boutton qui a été cliqué
 * 
 * @param tab 
 * @param size 
 * @param x 
 * @param y 
 * @return int -1 si aucun bouton cliqué, l'indice dans le tableau `tab` 
 *         sinon
 */
int button_onclick_tab(Button tab[], int size, int x, int y) {
    for (int i = 0; i < size; i++) {
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

void button_draw_tab(Button tab[], int val[], int size, 
                     MLV_Color color[]) {
    for (int i = 0; i < size; i++) {
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
    printf("%s Fin d'execusion %s\n", GREEN, RESET);
    MLV_actualise_window();
    MLV_wait_seconds(2);
}

void init_window_param(void) {
    int stop = 0, pressed = 0, x = 0, y = 0;
    
    Button tab_button_distrib[LENGTH_DISTRIB];
    Button tab_button_shapes[LENGTH_SHAPES];
    Button tab_button_display[LENGTH_DISPLAY];
    int tab_value_distrib[LENGTH_DISTRIB] = {};
    int tab_value_shapes[LENGTH_SHAPES] = {};
    int tab_value_display[LENGTH_DISPLAY] = {};
    MLV_Color tab_color[2] = {MLV_COLOR_RED,
                              MLV_COLOR_GREEN};

    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("Setting convex hull", "Setting", 600, 300);

    MLV_draw_text(40, 75, "Mode de distribution :", MLV_COLOR_GREEN);
    tab_button_distrib[0] = createButton(50, 100, "Placer à la souris");
    tab_button_distrib[1] = createButton(50, 150, "Aléatoire controlé");
    tab_button_distrib[2] = createButton(50, 200, "Forme prédéfini");

    MLV_draw_text(240, 75, " Formes prédéfinies :", MLV_COLOR_GREEN);
    tab_button_shapes[0] = createButton(450, 100, "Cercle");
    tab_button_shapes[1] = createButton(450, 150, "Carré");
    tab_button_shapes[2] = createButton(450, 200, "Rectangle");
    tab_button_shapes[3] = createButton(450, 250, "Ellipse");
    tab_button_shapes[4] = createButton(250, 250, "Rayon croissant");

    MLV_draw_text(240, 75, " Mode d'afficahge :", MLV_COLOR_GREEN);
    tab_button_display[0] = createButton(250, 100, "Point par Point");
    tab_button_display[1] = createButton(250, 150, "Automatique");

    while (!stop) {
        MLV_clear_window(MLV_COLOR_BLACK);
        MLV_draw_text(150, 20, "%d", MLV_COLOR_GREEN, MLV_get_time());
        button_draw_tab(tab_button_distrib, tab_value_distrib,
                        LENGTH_DISTRIB, tab_color);
        button_draw_tab(tab_button_display, tab_value_display,
                        LENGTH_DISPLAY, tab_color);
        if (tab_value_distrib[2] == 1) {
            button_draw_tab(tab_button_shapes, tab_value_shapes, 
                            LENGTH_SHAPES, tab_color);
        }

        //////////////////////
        // char *choice, *endPtr;
        // MLV_wait_input_box(
        //     200, 100,
        //     100, 100,
        //     MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_WHITE,
        //     "Hauteur : ",
        //     &choice);
        // choix = strtol(choice, &endPtr, 10);
        //////////////////////
        MLV_actualise_window();
        MLV_update_window();

        if ((MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) && pressed == 0) {
            pressed = 1;
            MLV_get_mouse_position(&x, &y);
            int val = button_onclick_tab(tab_button_distrib, LENGTH_DISTRIB,
                                         x, y);
            int val2 = button_onclick_tab(tab_button_display, LENGTH_DISPLAY,
                                          x, y);
            int val3 = button_onclick_tab(tab_button_shapes, LENGTH_SHAPES,
                                          x, y);
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

/*int main(void) {
    init_window_param();
    return 0;
}*/