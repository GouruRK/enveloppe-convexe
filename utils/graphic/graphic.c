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
clang -c ../list/list.c -Wall -std=c17
clang -c ../args/errs.c -Wall -std=c17
clang -c ../math/math.c -Wall -std=c17
clang -c ../graphic/draw.c -Wall -std=c17
clang graphic.c errs.o list.o math.o draw.o -Wall -std=c17 -o graph -lMLV
*/

#define BORDER 8
#define LENGTH_DISTRIB 2
#define LENGTH_SHAPES 4
#define LENGTH_DISPLAY 2

/**
 * @brief Fonction d'arrêt
 * 
 * @param data 
 */
void exit_function(void* data) {
    int* arret = (int*)data;
    *arret = 1;
}

/**
 * @brief Permet de savoir si l'utilisateur appuie avec le bouton
 *        `button`
 * 
 * @param button 
 * @param expected 
 * @return int 
 */
int isClicking(MLV_Mouse_button button, MLV_Button_state expected) {
    return MLV_get_mouse_button_state(button) == expected;
}

/**
 * @brief Permet de créer un bouton
 * 
 * @param x 
 * @param y 
 * @param text Texte a afficher
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
    but.value = 0;
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
int buttonOnClick(Button but, int x, int y) {
    int but_max_x = but.x + but.width + BORDER;
    int but_max_y = but.y + but.height + BORDER;
    return isInside(x, y, but.x, but_max_x, but.y, but_max_y);
}

/**
 * @brief Renvoie l'indice du boutton qui a été cliqué
 * 
 * @param tab Tableau contenant les différents boutons
 * @param size Taille du tableau
 * @param x 
 * @param y 
 * @return int -1 si aucun bouton cliqué, l'indice dans le tableau `tab` 
 *         sinon
 */
int button_onclick_tab(Button tab[], int size, int x, int y) {
    for (int i = 0; i < size; i++) {
        if (buttonOnClick(tab[i], x, y)) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Dessine un bouton
 * 
 * @param but Les paramètres du boutou
 * @param color_text 
 * @param color_border 
 */
void drawButton(Button but, MLV_Color color_text,
                         MLV_Color color_border) {
    MLV_draw_rectangle(but.x, but.y, but.width + BORDER, but.height + BORDER,
                       color_border);
    MLV_draw_text(but.x + BORDER / 2, but.y + BORDER / 2, but.text,
                  color_text);
}

/**
 * @brief Dessine l'ensemble des boutons contenus dans `tab`
 * 
 * @param tab Tableau de boutons
 * @param size Taille du tableau de boutons
 * @param color Couleur du bouton
 */
void button_draw_tab(Button tab[], int size, MLV_Color color[]) {
    for (int i = 0; i < size; i++) {
        drawButton(tab[i], color[tab[i].value], color[tab[i].value]);
    }
}

/**
 * @brief Inverse les bouton sauf un
 * 
 * @param tab Tableau de boutons
 * @param size Taille du tableau
 * @param index Indice du tableau a traiter différemment
 */
void switch_(Button tab[], int size, int index) {
    for (int i = 0; i < size; i++) {
        if (i == index) {
            tab[i].value = 1;
        } else {
            tab[i].value = 0;
        }
    }
}

/**
 * @brief Renvoie l'indice du bouton dans `tab` qui est actif
 * 
 * @param tab Tableau de boutons 
 * @param size Taille du tableau
 * @return int Renvoie -1 si aucun bouton n'est actif
 */
int indexActiveButton(Button tab[], int size) {
    for (int i = 0; i < size; i++) {
        if (tab[i].value == 1) {
            return i;
        }
    }
    return 0;
}

/**
 * @brief Récupère les paramètres donnés par l'utilisateur
 * 
 * @param w_width Nouvelle largeur
 * @param w_height Nouvelle hauteur
 * @param array Tableau de paramètres
 */
void windowParamPreclose(int w_width, int w_height, int array[]) {
    MLV_clear_window(MLV_COLOR_LIGHT_GREY);
    MLV_draw_text(50, 50, "Vous allez dessiner une envellope convexe avec :",
                  MLV_COLOR_BLACK);
    if (array[0] == 0) {
        MLV_draw_text(75, 100, "- Des clics souris", MLV_COLOR_BLACK);
        if (array[1] == 1) {
            MLV_draw_text(75, 125, "- Une envellope imbriquee", 
                          MLV_COLOR_BLACK);
        }
    } else {
        if (array[1] == 0) {
            MLV_draw_text(75, 100, "- Un Cercle", MLV_COLOR_BLACK);
            if (array[2]) {
                MLV_draw_text(155, 100, "croissant", MLV_COLOR_BLACK);
            }
        } else if (array[1] == 1) {
            MLV_draw_text(75, 100, "- Un Carré", MLV_COLOR_BLACK);
            if (array[2]) {
                MLV_draw_text(150, 100, "croissant", MLV_COLOR_BLACK);
            }
        } else if (array[1] == 2) {
            MLV_draw_text(75, 100, "- Un Rectangle", MLV_COLOR_BLACK);
            if (array[2]) {
                MLV_draw_text(180, 100, "croissant", MLV_COLOR_BLACK);
            }
        } else if (array[1] == 3) {
            MLV_draw_text(75, 100, "- Une Ellipse", MLV_COLOR_BLACK);
            if (array[2]) {
                MLV_draw_text(170, 100, "croissante", MLV_COLOR_BLACK);
            }
        }
        MLV_draw_text(75, 125, "- Avec %d points", MLV_COLOR_BLACK,
                      array[3]);
        MLV_draw_text(75, 150, "- Avec un rayon de %d px", MLV_COLOR_BLACK,
                      array[4]);
        if (array[5]) {
            MLV_draw_text(75, 175, "- Avec un delai de %d ms", 
                          MLV_COLOR_BLACK, array[6]);
        } else {
            MLV_draw_text(75, 200, "- Avec une generation automatique",
                          MLV_COLOR_BLACK, array[6]);
        }
    }
    MLV_draw_text(150, 350, "La fenetre sera de dimension %d,%d", 
                  MLV_COLOR_RED, w_width, w_height);
    MLV_actualise_window();
    MLV_wait_seconds(2);
}

/**
 * @brief Initialise la fenêtre du menu
 * 
 * @param window_width Nouvelle largeur
 * @param window_height Nouvelle hauteur
 * @param array Tableau de configuration
 */
void initWindowParam(int* window_width, int* window_height, int array[], int* stop) {
    int pressed = 0;
    int rayon = rayon = (0.9 * min(*window_height, *window_width)) / 2;
    int nb_points = 400, waiting_time = 1000;
    Button tab_button_distrib[LENGTH_DISTRIB]; 
    Button tab_button_shapes[LENGTH_SHAPES];
    Button tab_button_display[LENGTH_DISPLAY];
    MLV_Color tab_color[2] = {MLV_COLOR_RED,
                              MLV_COLOR_DARKGREEN};
    MLV_create_window("Setting convex hull", "Setting", 600, 400);

    /////////
    MLV_Input_box *input_box = NULL;
    MLV_Input_box *input1, *input2, *input3, *input4, *input5;
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
    input3 = MLV_create_input_box(
        255, 250,
        100, 20,
        MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_LIGHT_GRAY,
        "Rayon: ");
    input4 = MLV_create_input_box(
        25, 150,
        150, 20,
        MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_LIGHT_GRAY,
        "Delai en ms : ");
    input5 = MLV_create_input_box(
        205, 275,
        200, 20,
        MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_LIGHT_GRAY,
        "Nombre de points : ");
    // MLV_draw_all_input_boxes();
    /////////
    tab_button_distrib[0] = createButton(250, 50, "Placer à la souris");
    tab_button_distrib[1] = createButton(250, 100, "Forme prédéfini");

    tab_button_shapes[0] = createButton(450, 50, "Cercle");
    tab_button_shapes[1] = createButton(450, 100, "Carré");
    tab_button_shapes[2] = createButton(450, 150, "Rectangle");
    tab_button_shapes[3] = createButton(450, 200, "Ellipse");

    tab_button_display[0] = createButton(50, 50, "Automatique");
    tab_button_display[1] = createButton(50, 100, "Avec delai");

    Button but_incep = createButton(240, 200, "Envellope imbriquee");
    Button but_rising = createButton(250, 200, "Rayon croissant");

    while (!(*stop)) {
        MLV_clear_window(MLV_COLOR_LIGHT_GRAY);
        // MLV_draw_text(150, 20, "%d", MLV_COLOR_DARKGREEN, MLV_get_time());
        MLV_draw_text(240, 25, "Mode de distribution :", 
                      MLV_COLOR_DARKGREEN);
        button_draw_tab(tab_button_distrib, LENGTH_DISTRIB, tab_color);
        if (tab_button_distrib[1].value == 1) {
            MLV_draw_text(40, 25, " Formes prédéfinies :",
                          MLV_COLOR_DARKGREEN);
            MLV_draw_text(440, 25, " Mode d'afficahge :", 
                          MLV_COLOR_DARKGREEN);
            button_draw_tab(tab_button_display, LENGTH_DISPLAY, tab_color);
            button_draw_tab(tab_button_shapes, LENGTH_SHAPES, tab_color);
            drawButton(but_rising, tab_color[but_rising.value],
                       tab_color[but_rising.value]);
            MLV_draw_input_box(input3);
            MLV_draw_input_box(input5);
            if (tab_button_display[1].value == 1) {
                MLV_draw_input_box(input4);
            }
        } else if (tab_button_distrib[0].value == 1) {
            drawButton(but_incep, tab_color[but_incep.value],
                       tab_color[but_incep.value]);
        }

        MLV_draw_input_box(input1);
        MLV_draw_input_box(input2);
        //////////////////////
        event = MLV_get_event(
            NULL, NULL, NULL,
            &text, &input_box,
            NULL, NULL, NULL,
            NULL);

        //////////////////////
        if (event == MLV_INPUT_BOX) {
            int val = 0;
            if (input_box == input1) {
                val = (int)strtol(text, &endPtr, 10);
                if (val && val > 300) {
                    *window_width = val;
                    if (rayon > (0.9 * val) / 2) {
                        rayon = (0.9 * min(*window_height, *window_width)) / 2;
                    }
                }
            } else if (input_box == input2) {
                val = (int)strtol(text, &endPtr, 10);
                if (val && val > 300) {
                    *window_height = val;
                    fprintf(stderr, "%f\n", 0.9 * val);
                    if (rayon > (0.9 * val) / 2) {
                        rayon = (0.9 * min(*window_height, *window_width)) / 2;
                    }
                }
            } else if (input_box == input3 
                       && tab_button_distrib[1].value == 1) 
                {
                val = (int)strtol(text, &endPtr, 10);
                if (val && val < min(*window_height - 50, *window_width)/2) {
                    rayon = val;
                }
            } else if (input_box == input4 
                       && tab_button_distrib[1].value == 1
                       && tab_button_display[1].value == 1)
                {
                val = (int)strtol(text, &endPtr, 10);
                if (val) {
                    waiting_time = val;
                }
            } else if (input_box == input5
                       && tab_button_distrib[1].value == 1) 
                {
                val = (int)strtol(text, &endPtr, 10);
                if (val) {
                    nb_points = val;
                }
            }
        }

        //////////////////////
        MLV_actualise_window();
        MLV_update_window();

        if ((isClicking(MLV_BUTTON_LEFT, MLV_PRESSED)) && pressed == 0) {
            pressed = 1;
            MLV_get_mouse_position(&x, &y);
            int val = button_onclick_tab(tab_button_distrib, LENGTH_DISTRIB,
                                         x, y);
            int val2 = button_onclick_tab(tab_button_display, LENGTH_DISPLAY,
                                          x, y);
            int val3 = button_onclick_tab(tab_button_shapes, LENGTH_SHAPES, 
                                          x, y);
            int val4 = buttonOnClick(but_rising, x, y);
            int val5 = buttonOnClick(but_incep, x, y);
            if (val != -1) {
                switch_(tab_button_distrib, LENGTH_DISTRIB, val);

            } else if (val2 != -1 && tab_button_distrib[1].value == 1) {
                switch_(tab_button_display, LENGTH_DISPLAY, val2);

            } else if (val3 != -1 && tab_button_distrib[1].value == 1) {
                switch_(tab_button_shapes, LENGTH_SHAPES, val3);

            } else if (val4 != 0 && tab_button_distrib[1].value == 1) {
                but_rising.value = 1 - but_rising.value;

            } else if (val5 != 0 && tab_button_distrib[1].value == 0) {
                but_incep.value = 1 - but_incep.value;
            }
        }
        if (isClicking(MLV_BUTTON_LEFT, MLV_RELEASED)) {
            pressed = 0;
        }
    }

    array[0] = indexActiveButton(tab_button_distrib, LENGTH_DISTRIB);
    if (array[0] == 1) {
        array[1] = indexActiveButton(tab_button_shapes, LENGTH_SHAPES);
        array[2] = but_rising.value;
        array[3] = nb_points;
        array[4] = rayon;
        array[5] = indexActiveButton(tab_button_display, LENGTH_DISPLAY);
        if (array[5] == 1) {
            array[6] = waiting_time;
        }
    } else {
        array[1] = but_incep.value;
    }
    windowParamPreclose(*window_width, *window_height, array);
    MLV_free_window();
}

// int main(void) {
//     int window_width = 1000, window_height = 1000;
//     int tab[6] = {};
//     initWindowParam(&window_width, &window_height, tab);
//     for (int i = 0; i < 7; i++) {
//         printf("%d\n", tab[i]);
//     }
//     return 0;
// }
