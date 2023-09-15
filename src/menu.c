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

void erase_button(Button but, MLV_Color border_color) {
    MLV_draw_filled_rectangle(but.x - BORDER, but.y - BORDER,
                              but.width + 2 * BORDER, but.height + BORDER,
                              border_color);

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

void draw_array_button(Button* arr, int length, MLV_Color text_color,
                       MLV_Color border_color) {
    for (int i = 0; i < length; i++) {
        draw_button(arr[i], text_color, border_color);
    }
}

void draw_array_button_value(Button* arr, int length, MLV_Color text_color,
                             MLV_Color border_color) {
    for (int i = 0; i < length; i++) {
        draw_button_value(arr[i], text_color, border_color);
    }
}

bool onclick_button(int user_x, int user_y, Button but) {
    return ((user_x >= but.x - BORDER && user_x <= but.x + but.width + BORDER) &&
            (user_y >= but.y - BORDER && user_y <= but.y + but.height + BORDER));
}

Button* onclick_array_button(int user_x, int user_y, Button* arr_but, int length) {
    for (int i = 0; i < length; i++) {
        if (onclick_button(user_x, user_y, arr_but[i])) {
            return &arr_but[i];
        }
    }
    return NULL;
}

char* max_len(char** arr, int length) {
    char* result = arr[0];
    for (int i = 1; i < length; i++) {
        if (strlen(result) < strlen(arr[i])) {
            result = arr[i];
        }
    }
    return result;
}

Args menu(int* stop) {
    int mid_x = WIDTH / 2;
    int n1 = 50,
        n2 = 50 + BUT_MARGIN,
        n_1 = HEIGHT - 50,
        n_2 = n_1 - BUT_MARGIN,
        n_3 = n_2 - BUT_MARGIN,
        n_4 = n_3 - BUT_MARGIN,
        n_5 = n_4 - 2 * BUT_MARGIN,
        n_6 = n_5 - BUT_MARGIN;

    MLV_Color tab_color[2] = {MLV_COLOR_RED, MLV_COLOR_DARK_GREEN};

    char *ww = "Window width",
         *wh = "Window height",

         *inc = "Inception",
         *gc = "Clicks",
         *gs = "Shapes",

         *sp = "Points",
         *sr = "Radius",
         *sf = "Factor";

    char* tab_shape[SIZE_SHAPE] = {
        "Circle",
        "Ellipse",
        "Square",
        "Rectangle",
    };

    int w_ww, w_wh, w_inc, w_gc, w_grah, w_shape;
    MLV_get_size_of_text(ww, &w_ww, NULL);
    MLV_get_size_of_text(wh, &w_wh, NULL);

    MLV_get_size_of_text(inc, &w_inc, NULL);
    MLV_get_size_of_text(gc, &w_gc, NULL);
    MLV_get_size_of_text(sr, &w_grah, NULL);
    MLV_get_size_of_text(max_len(tab_shape, SIZE_SHAPE), &w_shape, NULL);

    Button tab_but[SIZE_VALUE] = {
        create_button(mid_x - w_ww / 2, n_6, ww, WIDTH),
        create_button(mid_x - w_wh / 2, n_5, wh, HEIGHT),
        create_button(mid_x - w_grah / 2, n_3, sp, 100),
        create_button(mid_x - w_grah / 2, n_2, sr, MIN(WIDTH, WIDTH) / 2),
        create_button(mid_x - w_grah / 2, n_1, sf, 1),
    };

    Button gen_c = create_button(mid_x - w_gc - MARGIN / 2, n1, gc, 0);
    Button gen_s = create_button(mid_x + MARGIN / 2, n1, gs, 1);
    Button shape = create_button(mid_x - w_grah / 2, n_4, tab_shape[3], 3);
    Button incep = create_button(mid_x - w_inc / 2, n2, inc, 0);

    Button tab_but_arrow[SIZE_ARROW] = {
        create_button(tab_but[0].x - 1.2 * MARGIN, n_6, "<", 10),
        create_button(tab_but[0].x - 2.5 * MARGIN, n_6, "<<", 100),
        create_button(tab_but[0].x + tab_but[0].width + 2 * MARGIN, n_6, ">", 10),
        create_button(tab_but[0].x + tab_but[0].width + 3 * MARGIN, n_6, ">>", 100),
        create_button(tab_but[1].x - 1.2 * MARGIN, n_5, "<", 10),
        create_button(tab_but[1].x - 2.5 * MARGIN, n_5, "<<", 100),
        create_button(tab_but[1].x + tab_but[1].width + 2 * MARGIN, n_5, ">", 10),
        create_button(tab_but[1].x + tab_but[1].width + 3 * MARGIN, n_5, ">>", 100),

        create_button(tab_but[3].x - 1.2 * MARGIN, n_3, "<", 10),
        create_button(tab_but[3].x - 2.5 * MARGIN, n_3, "<<", 100),
        create_button(tab_but[3].x + tab_but[2].width + 2 * MARGIN, n_3, ">", 10),
        create_button(tab_but[3].x + tab_but[2].width + 3 * MARGIN, n_3, ">>", 100),

        create_button(tab_but[2].x - 1.2 * MARGIN, n_2, "<", 10),
        create_button(tab_but[2].x - 2.5 * MARGIN, n_2, "<<", 100),
        create_button(tab_but[2].x + tab_but[2].width + 2 * MARGIN, n_2, ">", 10),
        create_button(tab_but[2].x + tab_but[2].width + 3 * MARGIN, n_2, ">>", 100),

        create_button(tab_but[4].x - 1.2 * MARGIN, n_1, "<", 1),
        create_button(tab_but[4].x + tab_but[3].width + 2 * MARGIN, n_1, ">", 1),

        create_button(shape.x - 1.2 * MARGIN, n_4, "<", 10),
        create_button(shape.x + w_shape + MARGIN, n_4, ">", 10),
    };

    Button next_phase = create_button(WIDTH - 150, HEIGHT - 30, "Launch ConvexHull", 0);

    MLV_draw_text(MARGIN, n1, "Generation Parameters : ", BLACK);
    MLV_draw_text(MARGIN, n_6, "Window Parameters : ", BLACK);
    MLV_draw_text(MARGIN, n_4, "Shape Parameters : ", BLACK);
    draw_button(shape, BLACK, BLACK);
    draw_button(gen_c, tab_color[gen_c.value], tab_color[gen_c.value]);
    draw_button(gen_s, tab_color[gen_s.value], tab_color[gen_s.value]);
    draw_button(incep, tab_color[incep.value], tab_color[incep.value]);
    draw_array_button_value(tab_but, SIZE_VALUE, MLV_COLOR_DARK_BLUE, BLACK);
    draw_array_button(tab_but_arrow, SIZE_ARROW, BLACK, BLACK);
    draw_button(next_phase, MLV_COLOR_DARK_GREEN, MLV_COLOR_DARK_GREEN);

    MLV_Event ev = MLV_NONE;
    MLV_Keyboard_button touche;
    MLV_Mouse_button mouse;
    MLV_Button_state state;
    int x, y;

    while (!(*stop)) {
        ev = MLV_wait_event_or_milliseconds(&touche, NULL, NULL, NULL, NULL, &x, &y, &mouse, &state, TIME_INTERVAL);
        if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED && onclick_button(x, y, next_phase)) {
            break;
        }
        if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED) {
            if (onclick_button(x, y, incep)) {
                erase_button(incep, MLV_COLOR_LIGHT_GRAY);
                incep.value = 1 - incep.value;
                draw_button(incep, tab_color[incep.value], tab_color[incep.value]);
            } else if ((onclick_button(x, y, gen_c) && !gen_c.value) ||
                       (onclick_button(x, y, gen_s) && !gen_s.value)) {
                erase_button(gen_c, MLV_COLOR_LIGHT_GRAY);
                erase_button(gen_s, MLV_COLOR_LIGHT_GRAY);
                gen_c.value = 1 - gen_c.value;
                gen_s.value = 1 - gen_s.value;
                draw_button(gen_c, tab_color[gen_c.value], tab_color[gen_c.value]);
                draw_button(gen_s, tab_color[gen_s.value], tab_color[gen_s.value]);
            }
            Button* result = onclick_array_button(x, y, tab_but_arrow, SIZE_ARROW);
            if (result) {
                if (result->y == n_4) {
                    erase_button(shape, MLV_COLOR_LIGHT_GRAY);
                    if (result->text[0] == '<') {
                        shape.value = true_modulo(shape.value - 1, SIZE_SHAPE);
                        shape.text = tab_shape[shape.value];
                    } else {
                        shape.value = true_modulo(shape.value + 1, SIZE_SHAPE);
                        shape.text = tab_shape[shape.value];
                    }
                    draw_button(shape, BLACK, BLACK);
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
        .nb_point = tab_but[3].value,
        .factor = tab_but[4].value,
    };
    return args;
}
