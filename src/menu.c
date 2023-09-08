#include "../include/menu.h"

#include <MLV/MLV_all.h>
#include <stdbool.h>
#include <string.h>

#define BLACK MLV_COLOR_BLACK

Button create_button(int x, int y, char* text, int value) {
    Button but;
    // + 1 for the \0 at the end of the char*
    but.text = malloc((strlen(text) + 1) * sizeof(char));
    if (!but.text) {
        exit(EXIT_FAILURE);
    }
    strcpy(but.text, text);
    but.x = x, but.y = y, but.value = value;
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
    return ((user_x >= but.x && user_x <= but.x + but.width) &&
            (user_y >= but.y && user_y <= but.y + but.height));
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
    int n1 = 100, n_1 = HEIGHT - 160, n_2 = HEIGHT - 130, n_3 = HEIGHT - 100;
    Args args;
    args.w_width = WIDTH, args.w_height = WIDTH, args.factor = 1;
    args.radius = MIN(WIDTH, WIDTH) / 2;

    char *s1 = "Window width",
         *s2 = "Window height", *s3 = "Radius";

    char* tab_shape[4] = {
        "Circle",
        "Ellipse",
        "Square",
        "Rectangle",
    };
    int w_s1, w_s2, w_s3, w_shape;
    MLV_get_size_of_text(s1, &w_s1, NULL);
    MLV_get_size_of_text(s2, &w_s2, NULL);
    MLV_get_size_of_text(s3, &w_s3, NULL);
    MLV_get_size_of_text(max_len(tab_shape, 4), &w_shape, NULL);

    Button tab_but[3] = {
        create_button(mid_x - w_s1 / 2, n_1, s1, args.w_width),
        create_button(mid_x - w_s2 / 2, n_2, s2, args.w_height),
        create_button(mid_x - w_s3 / 2, n_3, s3, args.radius),
    };
    Button shape = create_button(mid_x - w_shape / 2, n1, tab_shape[3], 0);

    Button tab_but_arrow[14] = {
        create_button(tab_but[0].x - MARGIN, n_1, "<", 10),
        create_button(tab_but[1].x - MARGIN, n_2, "<", 10),
        create_button(tab_but[2].x - MARGIN, n_3, "<", 10),
        create_button(tab_but[0].x - 2.5 * MARGIN, n_1, "<<", 100),
        create_button(tab_but[1].x - 2.5 * MARGIN, n_2, "<<", 100),
        create_button(tab_but[2].x - 2.5 * MARGIN, n_3, "<<", 100),
        create_button(tab_but[0].x + tab_but[0].width + 1.7 * MARGIN, n_1, ">", 10),
        create_button(tab_but[1].x + tab_but[1].width + 1.7 * MARGIN, n_2, ">", 10),
        create_button(tab_but[2].x + tab_but[2].width + 1.7 * MARGIN, n_3, ">", 10),
        create_button(tab_but[0].x + tab_but[0].width + 2.7 * MARGIN, n_1, ">>", 100),
        create_button(tab_but[1].x + tab_but[1].width + 2.7 * MARGIN, n_2, ">>", 100),
        create_button(tab_but[2].x + tab_but[2].width + 2.7 * MARGIN, n_3, ">>", 100),

        create_button(shape.x - MARGIN, n1, "<", 10),
        create_button(shape.x + w_shape + MARGIN / 2, n1, ">", 10),
    };

    Button next_phase = create_button(WIDTH - 150, HEIGHT - 30, "Launch ConvexHull", 0);

    draw_button(shape, BLACK, BLACK);
    draw_tab_button_value(tab_but, 3, MLV_COLOR_DARK_BLUE, BLACK);
    draw_tab_button(tab_but_arrow, 14, BLACK, BLACK);
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
            Button* result = onclick_tab_button(x, y, tab_but_arrow, 14);
            if (result) {
                fprintf(stderr, "cc");
            }
        }
    }

    // cercle / rectangle tab[0] / tab[1] / tab[2]

    // croissant / non tab[_][0] / tab[_][1]

    // inception / non tab[_][_][0] / tab[_][_][1]
    return args;
}