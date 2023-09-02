#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <math.h>

#include "../include/graphic.h"
#include "../include/struct.h"
#include "../include/tools.h"

void exit_function(void* data) {
    int* stop = (int*)data;
    *stop = 1;
}

int check_mouse_position(MLV_Mouse_button button, MLV_Button_state expected) {
    return MLV_get_mouse_button_state(button) == expected;
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

void draw_outline_points(Array points) {
   Polygon polygon = points.poly;
    if (polygon) {
        Vertex* head = polygon;
        Vertex* prev = polygon;
        polygon = polygon->next;
        while (head != polygon) {
            draw_outline_point(polygon->point);
            draw_line(prev->point, polygon->point);
            prev = polygon;
            polygon = polygon->next;
        }
        draw_outline_point(polygon->point);
        draw_line(prev->point, polygon->point);
    }
}

void draw_filled_convex(Convex convex, MLV_Color color) {
    Polygon polygon = convex.poly;
    if (polygon) {
        Vertex* head = polygon;
        Vertex* prev = polygon;
        polygon = polygon->next;
        while (head != polygon) {
            draw_surface(head->point, prev->point, polygon->point, color);
            draw_outline_point(polygon->point);
            draw_line(prev->point, polygon->point);
            prev = polygon;
            polygon = polygon->next;
        }
        draw_surface(head->point, prev->point, polygon->point, color);
        draw_outline_point(polygon->point);
        draw_line(prev->point, polygon->point);
    }
}

void draw_inception_convex(InceptionConvex incepconv) {
    for (int i = 0; i < incepconv.maxlen; i++) {
        if (incepconv.tab_convex[i].curlen) {
            draw_filled_convex(incepconv.tab_convex[i], TAB_COLOR[i % TAB_COLOR_SIZE]);
        } else {
            break;
        }
    }
}

Point point_on_click(int* stop, int nb_points, Window* win) {
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

Point rising_sphere(int* stop, int nb_points, Window* win) {
    static int x, y, init = 0, generated_points = 0;
    static double radius;

    if (!init) {
        if (nb_points < 0) {
            return create_point(-1, -1);
        }

        // radius = radius_max / nb_points
        radius = (win->clickable.width / 2 - 30) / ((float)nb_points);

        x = win->clickable.width / 2;
        y = win->clickable.height / 2;

        init = 1;
    }
    if (generated_points == nb_points) {
        return create_point(-1, -1);
    }
    MLV_wait_milliseconds(10);
    generated_points++;
    int random = rand();
    return create_point(x + radius * generated_points * cos(random),
                        y + radius * generated_points * sin(random));
}

Point rising_square(int* stop, int nb_points, Window* win) {
    static int x, y, init = 0, generated_points = 0;
    static double radius;

    if (!init) {
        if (nb_points < 0) {
            return create_point(-1, -1);
        }

        // radius = radius_max / nb_points
        radius = (win->clickable.width / 2 - 30) / ((float)nb_points);

        x = win->clickable.width / 2;
        y = win->clickable.height / 2;

        init = 1;
    }
    if (generated_points == nb_points) {
        return create_point(-1, -1);
    }
    MLV_wait_milliseconds(10);
    generated_points++;
    return create_point(x + radius * generated_points * cos(rand()),
                        y + radius * generated_points * sin(rand()));
}

void draw_outline_points_information(int value, Window* win) {
    static int width, height, x, y, init = 0;

    if (!init) {
        MLV_get_size_of_text("Outline points : %3d", &width, &height, 0);
        x = win->information.width * 1/4 - width/2;
        y = win->information.min.y + win->information.height/2 - height/2;
        init = 1;
    }
    MLV_draw_text(x, y, "Outline points : %3d", TEXT_COLOR, value);
}

void draw_inside_points_information(int value, Window* win) {
    static int width, height, x, y, init = 0;

    if (!init) {
        MLV_get_size_of_text("Inside points : %3d", &width, &height, 0);
        x = win->information.width * 1/2 - width/2;
        y = win->information.min.y + win->information.height/2 - height/2;
        init = 1;
    }
    MLV_draw_text(x, y, "Inside points : %3d", TEXT_COLOR, value);
}

void draw_total_points_information(int value, Window* win) {
    static int width, height, x, y, init = 0;

    if (!init) {
        MLV_get_size_of_text("Total points : %3d", &width, &height, 0);
        x = win->information.width * 3/4 - width/2;
        y = win->information.min.y + win->information.height/2 - height/2;
        init = 1;
    }
    MLV_draw_text(x, y, "Total points : %3d", TEXT_COLOR, value);
}

void draw_hulls_information(int value, Window* win) {
    static int width, height, x, y, init = 0;

    if (!init) {
        MLV_get_size_of_text("Number of hulls : %3d", &width, &height, 0);
        x = win->information.width * 1/4 - width/2;
        y = win->information.min.y + win->information.height/2 - height/2;
        init = 1;
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
