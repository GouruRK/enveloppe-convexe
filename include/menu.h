#ifndef __INIT_MENU__
#define __INIT_MENU__

#include <MLV/MLV_color.h>
#include <stdbool.h>

#include "../include/struct.h"
#include "../include/graphic.h"
#include "../include/convexhull.h"

#define MIN(a, b) ((a < b) ? (a) : (b))
#define BORDER 5
#define MARGIN 25
#define WIDTH 600
#define HEIGHT 350
#define BUT_MARGIN 30
#define TIME_INTERVAL 100
#define SIZE_VALUE 5
#define SIZE_SHAPE 4
#define SIZE_ARROW 20

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
    int nb_point;
    int radius;
    int factor;
    void (*convex)(int*, Parameters, Point (*)(int*, Parameters, Window*), Window*);
    Point (*get_point)(int*, Parameters, Window*);
} Args;

/**
 * @brief Creates a button object.
 *
 * @param x Button abcissa
 * @param y Button ordinate
 * @param text Button text
 * @param value Button value
 * @return Button initialised
 */
Button create_button(int x, int y, char* text, int value);

/**
 * @brief Draws a button object.
 *
 * @param but Button to draw
 * @param text_color Text color
 * @param border_color Border color
 */
void draw_button(Button but, MLV_Color text_color,
                 MLV_Color border_color);

/**
 * @brief Draws a button object with its value.
 *
 * @param but Button to draw
 * @param text_color Text color
 * @param border_color Border color
 */
void draw_button_value(Button but, MLV_Color text_color,
                       MLV_Color border_color);

/**
 * @brief Erases a button object.
 *
 * @param but Button to erase
 * @param border_color Color draws
 */
void erase_button(Button but, MLV_Color border_color);

/**
 * @brief Erases a button object with its value.
 *
 * @param but Button to erase
 * @param border_color Color draws
 */
void erase_button_value(Button but, MLV_Color border_color);

/**
 * @brief Tells if the button is clicked.
 *
 * @param user_x User input x
 * @param user_y User input y
 * @param but Button to compare.
 * @return true : the button is clicked
 * @return false : the button is not clicked
 */
bool onclick_button(int user_x, int user_y, Button but);

/**
 * @brief Tells witch button is clicked in the array.
 *
 * @param user_x User input x
 * @param user_y User input y
 * @param arr_but Array of buttons
 * @param length Array length
 * @return Button* NULL if no button was clicked else button.
 */
Button* onclick_array_button(int user_x, int user_y, Button* arr_but, int length);

/**
 * @brief Draws a array of button object.
 *
 * @param arr Button array
 * @param length Array length
 * @param text_color Text color
 * @param border_color Border color
 */
void draw_array_button(Button* arr, int length, MLV_Color text_color,
                       MLV_Color border_color);

/**
 * @brief Draws a array of button object with its value.
 *
 * @param arr Button array
 * @param length Array length
 * @param text_color Text color
 * @param border_color Border color
 */
void draw_array_button_value(Button* arr, int length, MLV_Color text_color,
                             MLV_Color border_color);

/**
 * @brief Return the char* with the max length
 *
 * @param arr Array
 * @param length Array length
 * @return Longest char*
 */
char* max_len(char** arr, int length);

/**
 * @brief Overall function to interact with the menu.
 *
 * @param stop set to '1' whenever the user close the window
 * @return Args Button value to initialise the game.
 */
Args menu(int* stop);

#endif
