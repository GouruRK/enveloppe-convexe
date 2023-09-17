/**
 * @file graphic.h
 * @author Laborde Quentin & Kies Remy
 * @brief Contains functions to draw anything on the current window
 * @date 05-09-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "../include/graphic.h"
#include "../include/struct.h"
#include "../include/tools.h"

void exit_function(void* data) {
    bool* stop = (bool*)data;
    *stop = true;
}

bool check_mouse_position(MLV_Mouse_button button, MLV_Button_state expected) {
    return MLV_get_mouse_button_state(button) == expected;
}

bool check_key_position(MLV_Keyboard_button key, MLV_Button_state expected) {
    return MLV_get_keyboard_state(key) == expected;
}

void draw_inside_point(Point point) {
    draw_point(point, INSIDE_POINT_COLOR);
}

void draw_outline_point(Point point) {
    draw_point(point, ONLINE_POINT_COLOR);
}

void draw_point(Point point, MLV_Color color) {
    MLV_draw_filled_circle(point.x, point.y, RADIUS, color);
}

void draw_line(Point a, Point b) {
    MLV_draw_line(a.x, a.y, b.x, b.y, LINE_COLOR);
}

void draw_surface(Point a, Point b, Point c, MLV_Color color) {
    MLV_draw_filled_triangle(a.x, a.y, b.x, b.y, c.x, c.y, color);
}

void draw_inside_points(Array points) {
    Polygon polygon = points.poly;
    if (polygon) {
        Vertex* head = polygon->prev;
        while (head != polygon) {
            draw_inside_point(polygon->point);
            polygon = polygon->next;
        }
        draw_inside_point(polygon->point);
    }
}

void draw_outline_points(Array points, bool show_points) {
   Polygon polygon = points.poly;
    if (polygon) {
        Vertex* head = polygon;
        Vertex* prev = polygon;
        polygon = polygon->next;
        while (head != polygon) {
            if (show_points) {
                draw_outline_point(polygon->point);
            }
            draw_line(prev->point, polygon->point);
            prev = polygon;
            polygon = polygon->next;
        }
        if (show_points) {
            draw_outline_point(polygon->point);
        }
        draw_line(prev->point, polygon->point);
    }
}

void draw_filled_convex(Convex convex, MLV_Color color, bool show_points) {
    Polygon polygon = convex.poly;
    if (polygon) {
        Vertex* head = polygon;
        Vertex* prev = polygon;
        polygon = polygon->next;
        while (head != polygon) {
            draw_surface(head->point, prev->point, polygon->point, color);
            if (show_points) {
                draw_outline_point(polygon->point);
            }
            draw_line(prev->point, polygon->point);
            prev = polygon;
            polygon = polygon->next;
        }
        draw_surface(head->point, prev->point, polygon->point, color);
        if (show_points) {
            draw_outline_point(polygon->point);
        }
        draw_line(prev->point, polygon->point);
    }
}

void draw_inception_convex(InceptionConvex incepconv, bool show_points) {
    for (int i = 0; i < incepconv.maxlen; i++) {
        if (i == incepconv.maxlen - 1 && show_points) {
            draw_inside_points(incepconv.tab_convex[i]);
        } else {
            draw_filled_convex(incepconv.tab_convex[i], TAB_COLOR[i % TAB_COLOR_SIZE], show_points);
        }
    }
}

Point point_on_click(bool* stop, Settings set, Window* win) {
    int x, y, mouse_pressed = 1;
    Point point;

    while (!(*stop)) {
        if (check_mouse_position(MLV_BUTTON_LEFT, MLV_PRESSED) && !mouse_pressed) {
            MLV_get_mouse_position(&x, &y);
            fill_point(&point, x, y);
            if (point_in_section(point, win->clickable)) {
                return point;
            }
        } else if (check_mouse_position(MLV_BUTTON_LEFT, MLV_RELEASED) && mouse_pressed) {
            mouse_pressed = 0;
        }
    }
    fill_point(&point, -1, -1);
    return point;
}

Point rising_circle(bool* stop, Settings set, Window* win) {
    static int x, y, init = 0, generated_points = 0;

    if (!init) {
        if (set.nb_points < 0) {
            return create_point(-1, -1);
        }

        x = win->clickable.width / 2;
        y = win->clickable.height / 2;

        init = true;
    }
    if (generated_points == set.nb_points) {
        return create_point(-1, -1);
    }
    MLV_wait_milliseconds(10);
    generated_points++;
    double theta = uniform() * 2 * PI;
    double radius = (set.radius / 2) * sqrt(uniform()); 
    return create_point(x + radius * (generated_points / (double)set.nb_points) * cos(theta) * (1 / set.factor),
                        y + radius * (generated_points / (double)set.nb_points) * sin(theta));
}

Point rising_square(bool* stop, Settings set, Window* win) {
    static int x, y, init = 0, generated_points = 0;

    if (!init) {
        if (set.nb_points < 0) {
            return create_point(-1, -1);
        }

        x = win->clickable.width / 2;
        y = win->clickable.height / 2;

        init = true;
    }
    if (generated_points == set.nb_points) {
        return create_point(-1, -1);
    }
    // MLV_wait_milliseconds(10);
    double distance = (((double)(set.radius) / (double)set.nb_points) * ++generated_points) / 2;
    return create_point(x + (float)random_int(-distance, distance) * (1 / set.factor),
                        y + random_int(-distance, distance));
}

void draw_outline_points_information(int value, Window* win) {
    static bool init = false;
    static int width, height, x, y;

    if (!init) {
        MLV_get_size_of_text("Outline points : %3d", &width, &height, 0);
        x = win->information.width * 1/4 - width/2;
        y = win->information.min.y + win->information.height/2 - height/2;
        init = true;
    }
    MLV_draw_text(x, y, "Outline points : %3d", TEXT_COLOR, value);
}

void draw_inside_points_information(int value, Window* win) {
    static bool init = false;
    static int width, height, x, y;

    if (!init) {
        MLV_get_size_of_text("Inside points : %3d", &width, &height, 0);
        x = win->information.width * 1/2 - width/2;
        y = win->information.min.y + win->information.height/2 - height/2;
        init = true;
    }
    MLV_draw_text(x, y, "Inside points : %3d", TEXT_COLOR, value);
}

void draw_total_points_information(int value, Window* win) {
    static bool init = false;
    static int width, height, x, y;

    if (!init) {
        MLV_get_size_of_text("Total points : %3d", &width, &height, 0);
        x = win->information.width * 3/4 - width/2;
        y = win->information.min.y + win->information.height/2 - height/2;
        init = true;
    }
    MLV_draw_text(x, y, "Total points : %3d", TEXT_COLOR, value);
}

void draw_hulls_information(int value, Window* win) {
    static bool init = false;
    static int width, height, x, y;

    if (!init) {
        MLV_get_size_of_text("Number of hulls : %3d", &width, &height, 0);
        x = win->information.width * 1/4 - width/2;
        y = win->information.min.y + win->information.height/2 - height/2;
        init = true;
    }
    MLV_draw_text(x, y, "Number of hulls : %3d", TEXT_COLOR, value);
}

void draw_raw_convex_information(int outline, int inside, Window* win) {
    MLV_draw_line(win->information.min.x, win->information.min.y,
                  win->information.max.x, win->information.min.y, LINE_COLOR);
    
    draw_outline_points_information(outline, win);
    draw_inside_points_information(inside, win);
    draw_total_points_information(outline + inside, win);
}

void draw_convex_information(Convex convex, Array points, Window* win) {
    draw_raw_convex_information(convex.curlen, points.curlen, win);
}

void draw_raw_inception_convex_information(int hulls, int points, Window* win) {
    MLV_draw_line(win->information.min.x, win->information.min.y,
                  win->information.max.x, win->information.min.y, LINE_COLOR);
    
    draw_hulls_information(hulls, win);
    draw_total_points_information(points, win);
}

void draw_inception_convex_information(InceptionConvex incepconv, Window* win) {
    int hulls = incepconv.curlen;
    if (incepconv.tab_convex[incepconv.curlen - 1].curlen < 3) {
        hulls--;
    }

    draw_raw_inception_convex_information(hulls, incepconv.total_points, win);
}
