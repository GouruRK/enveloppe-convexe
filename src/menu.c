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

    MLV_draw_text(but.x, but.y,
                  "%s %d",
                  text_color,
                  but.text, but.value);

    MLV_draw_rectangle(but.x - BORDER, but.y - BORDER,
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
                       but.width + BORDER, but.height + BORDER,
                       border_color);

    MLV_update_window();
}

bool onclick_button(int user_x, int user_y, Button but) {
    return ((user_x >= but.x && user_x <= but.x + but.width) &&
            (user_y >= but.y && user_y <= but.y + but.height));
}

Args menu(void) {
    int mid_x = WIDTH / 2;
    Args args;
    args.w_width = WIDTH, args.w_height = WIDTH, args.factor = 1;
    args.radius = MIN(WIDTH, WIDTH) / 2;

    char *s1 = "Window width",
         *s2 = "Window height", *s3 = "Radius";

    Button tab_but[3] = {
        create_button(mid_x, 100, s1, args.w_width),
        create_button(mid_x, 130, s2, args.w_height),
        create_button(mid_x, 160, s3, args.radius),
    };

    draw_button_value(tab_but[0], BLACK, BLACK);
    draw_button_value(tab_but[1], BLACK, BLACK);
    draw_button_value(tab_but[2], BLACK, BLACK);

    // cercle / rectangle tab[0] / tab[1] / tab[2]

    // croissant / non tab[_][0] / tab[_][1]

    // inception / non tab[_][_][0] / tab[_][_][1]
    return args;
}