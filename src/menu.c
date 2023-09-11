#include "../include/menu.h"

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include <string.h>

#include "../include/tools.h"

#define BLACK MLV_COLOR_BLACK

Button create_button(int x, int y, char* text, int value) {
    Button but;
    // + 1 for the \0 at the end of the char*
    // but.text = malloc((strlen(text) + 1) * sizeof(char));
    // if (!but.text) {
    //     exit(EXIT_FAILURE);
    // }
    // strcpy(but.text, text);
    but.x = x, but.y = y, but.value = value, but.text = text;
    MLV_get_size_of_text(but.text, &but.width, &but.height);
    return but;
}

void draw_button_value(Button but, MLV_Color text_color,
                       MLV_Color border_color) {
    int add_x;
    MLV_get_size_of_text(" %d", &add_x, NULL, but.value);

    MLV_draw_rectangle(but.x - BORDER, but.y - BORDER,
                       but.width + 2 * BORDER + add_x, but.height + 2 * BORDER,
                       border_color);

    MLV_draw_text(but.x, but.y,
                  "%s %d",
                  text_color,
                  but.text, but.value);

    MLV_update_window();
}

void erase_button_value(Button but, MLV_Color border_color) {
    int add_x;
    MLV_get_size_of_text(" %d", &add_x, NULL, but.value);

    MLV_draw_filled_rectangle(but.x - BORDER, but.y - BORDER,
                              but.width + 2 * BORDER + add_x, but.height + 2 * BORDER,
                              border_color);

    MLV_update_window();
}

void draw_button(Button but, MLV_Color text_color,
                 MLV_Color border_color) {
    MLV_draw_text(but.x, but.y,
                  but.text,
                  text_color);

    MLV_draw_rectangle(but.x - BORDER, but.y - BORDER,
                       but.width + 2 * BORDER, but.height + BORDER,
                       border_color);

    MLV_update_window();
}

void erase_button(Button but, MLV_Color border_color) {
    MLV_draw_filled_rectangle(but.x - BORDER, but.y - BORDER,
                              but.width + 2 * BORDER, but.height + BORDER,
                              border_color);

    MLV_update_window();
}

void draw_tab_button(Button* tab, int length, MLV_Color text_color,
                     MLV_Color border_color) {
    for (int i = 0; i < length; i++) {
        draw_button(tab[i], text_color, border_color);
    }
}

void draw_tab_button_value(Button* tab, int length, MLV_Color text_color,
                           MLV_Color border_color) {
    for (int i = 0; i < length; i++) {
        draw_button_value(tab[i], text_color, border_color);
    }
}

bool onclick_button(int user_x, int user_y, Button but) {
    return ((user_x >= but.x - BORDER && user_x <= but.x + but.width + BORDER) &&
            (user_y >= but.y - BORDER && user_y <= but.y + but.height + BORDER));
}

Button* onclick_tab_button(int user_x, int user_y, Button* tab_but, int length) {
    for (int i = 0; i < length; i++) {
        if (onclick_button(user_x, user_y, tab_but[i])) {
            return &tab_but[i];
        }
    }
    return NULL;
}

char* max_len(char** tab, int length) {
    char* result = tab[0];
    for (int i = 1; i < length; i++) {
        if (strlen(result) < strlen(tab[i])) {
            result = tab[i];
        }
    }
    return result;
}

Args menu(void) {
    int mid_x = WIDTH / 2;
    int n1 = 70, n2 = 100, n3 = 130, n_4 = HEIGHT - 190, n_3 = HEIGHT - 160, n_2 = HEIGHT - 130, n_1 = HEIGHT - 100;
    MLV_Color tab_color[2] = {MLV_COLOR_RED, MLV_COLOR_DARK_GREEN};

    char *s1 = "Window width",
         *s2 = "Window height",
         *s3 = "Radius",
         *s4 = "Factor",
         *s5 = "Inception";

    char* tab_gen[SIZE_GEN] = {
        "Shape",
        "Click",
    };
    char* tab_shape[SIZE_SHAPE] = {
        "Circle",
        "Ellipse",
        "Square",
        "Rectangle",
    };

    int w_s1, w_s2, w_s3, w_s4, w_s5, w_shape, w_gen;
    MLV_get_size_of_text(s1, &w_s1, NULL);
    MLV_get_size_of_text(s2, &w_s2, NULL);
    MLV_get_size_of_text(s3, &w_s3, NULL);
    MLV_get_size_of_text(s4, &w_s4, NULL);
    MLV_get_size_of_text(s5, &w_s5, NULL);
    MLV_get_size_of_text(max_len(tab_shape, SIZE_SHAPE), &w_shape, NULL);
    MLV_get_size_of_text(max_len(tab_gen, SIZE_GEN), &w_gen, NULL);

    Button tab_but[SIZE_VALUE] = {
        create_button(mid_x - w_s1 / 2, n_4, s1, WIDTH),
        create_button(mid_x - w_s2 / 2, n_3, s2, HEIGHT),
        create_button(mid_x - w_s3 / 2, n_2, s3, MIN(WIDTH, WIDTH) / 2),
        create_button(mid_x - w_s4 / 2, n_1, s4, 1),
    };

    Button gen = create_button(mid_x - w_gen / 2, n1, tab_gen[0], 0);
    Button shape = create_button(mid_x - w_shape / 2, n2, tab_shape[3], 3);
    Button incep = create_button(mid_x - w_s5 / 2, n3, s5, 0);

    Button tab_but_arrow[SIZE_ARROW] = {
        create_button(tab_but[0].x - 1.2 * MARGIN, n_4, "<", 10),
        create_button(tab_but[0].x - 2.5 * MARGIN, n_4, "<<", 100),
        create_button(tab_but[0].x + tab_but[0].width + 2 * MARGIN, n_4, ">", 10),
        create_button(tab_but[0].x + tab_but[0].width + 3 * MARGIN, n_4, ">>", 100),
        create_button(tab_but[1].x - 1.2 * MARGIN, n_3, "<", 10),
        create_button(tab_but[1].x - 2.5 * MARGIN, n_3, "<<", 100),
        create_button(tab_but[1].x + tab_but[1].width + 2 * MARGIN, n_3, ">", 10),
        create_button(tab_but[1].x + tab_but[1].width + 3 * MARGIN, n_3, ">>", 100),
        create_button(tab_but[2].x - 1.2 * MARGIN, n_2, "<", 10),
        create_button(tab_but[2].x - 2.5 * MARGIN, n_2, "<<", 100),
        create_button(tab_but[2].x + tab_but[2].width + 2 * MARGIN, n_2, ">", 10),
        create_button(tab_but[2].x + tab_but[2].width + 3 * MARGIN, n_2, ">>", 100),
        create_button(tab_but[3].x - 1.2 * MARGIN, n_1, "<", 1),
        create_button(tab_but[3].x + tab_but[3].width + 2 * MARGIN, n_1, ">", 1),

        create_button(gen.x - MARGIN, n1, "<", 10),
        create_button(gen.x + w_gen + MARGIN / 2, n1, ">", 10),
        create_button(shape.x - MARGIN, n2, "<", 10),
        create_button(shape.x + w_shape + MARGIN / 2, n2, ">", 10),
    };

    Button next_phase = create_button(WIDTH - 150, HEIGHT - 30, "Launch ConvexHull", 0);

    draw_button(shape, BLACK, BLACK);
    draw_button(gen, BLACK, BLACK);
    draw_button(incep, tab_color[incep.value], tab_color[incep.value]);
    draw_tab_button_value(tab_but, SIZE_VALUE, MLV_COLOR_DARK_BLUE, BLACK);
    draw_tab_button(tab_but_arrow, SIZE_ARROW, BLACK, BLACK);
    draw_button(next_phase, MLV_COLOR_DARK_GREEN, MLV_COLOR_DARK_GREEN);

    MLV_Event ev = MLV_NONE;
    MLV_Keyboard_button touche;
    MLV_Mouse_button mouse;
    MLV_Button_state state;
    int x, y;

    while (true) {
        ev = MLV_wait_event_or_milliseconds(&touche, NULL, NULL, NULL, NULL, &x, &y, &mouse, &state, TIME_INTERVAL);
        if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED && onclick_button(x, y, next_phase)) {
            break;
        }
        if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED) {
            if (onclick_button(x, y, incep)) {
                erase_button(incep, MLV_COLOR_LIGHT_GRAY);
                incep.value = 1 - incep.value;
                draw_button(incep, tab_color[incep.value], tab_color[incep.value]);
            }

            Button* result = onclick_tab_button(x, y, tab_but_arrow, SIZE_ARROW);
            if (result) {
                if (result->y == n2) {
                    erase_button(shape, MLV_COLOR_LIGHT_GRAY);
                    if (result->text[0] == '<') {
                        shape.value = true_modulo(shape.value - 1, SIZE_SHAPE);
                        shape.text = tab_shape[shape.value];
                    } else {
                        shape.value = true_modulo(shape.value + 1, SIZE_SHAPE);
                        shape.text = tab_shape[shape.value];
                    }
                    draw_button(shape, BLACK, BLACK);

                } else if (result->y == n1) {
                    erase_button(gen, MLV_COLOR_LIGHT_GRAY);
                    gen.value = 1 - gen.value;
                    gen.text = tab_gen[gen.value];
                    draw_button(gen, BLACK, BLACK);

                } else {
                    for (int i = 0; i < SIZE_ARROW; i++) {
                        if ((tab_but_arrow[i].y == result->y)) {
                            erase_button_value(tab_but[i / 4], MLV_COLOR_LIGHT_GRAY);
                            if (result->text[0] == '<' && tab_but[i / 4].value > result->value) {
                                tab_but[i / 4].value -= result->value;
                            } else if (result->text[0] == '>') {
                                tab_but[i / 4].value += result->value;
                            }
                            draw_button_value(tab_but[i / 4], MLV_COLOR_DARK_BLUE, BLACK);
                            break;
                        }
                    }
                }
            }
        }
    }

    Args args = {
        .w_width = tab_but[0].value,
        .w_height = tab_but[1].value,
        .radius = tab_but[2].value,
        .factor = tab_but[3].value,
    };
    return args;
}
