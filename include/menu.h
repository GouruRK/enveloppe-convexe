#ifndef __INIT_MENU__
#define __INIT_MENU__

#include <MLV/MLV_color.h>
#include <stdbool.h>

#define MIN(a, b) ((a < b) ? (a) : (b))
#define BORDER 5
#define WIDTH 600
#define HEIGHT 600

typedef enum {
    SQUARE,
    RECTANGLE,
    CIRCLE,
    ELLIPSE
} Shapes;

typedef struct {
    int x;
    int width;
    int y;
    int height;
    char* text;
    int value;
} Button;

typedef struct {
    int w_width;
    int w_height;
    int radius;
    int factor;
} Args;

Button create_button(int x, int y, char* text, int value);
void draw_button(Button but, MLV_Color text_color,
                 MLV_Color border_color);
bool onclick_button(int user_x, int user_y, Button but);
Args menu(void);

#endif
