#include <MLV/MLV_all.h>

#include "../include/graphic.h"
#include "../include/struct.h"

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

Point point_on_click(int* stop) {
    int x, y, mouse_pressed = 1;
    Point point;

    while (!(*stop)) {
        if (check_mouse_position(MLV_BUTTON_LEFT, MLV_PRESSED) && !mouse_pressed) {
            MLV_get_mouse_position(&x, &y);
            fill_point(&point, x, y);
            return point;
        } else if (check_mouse_position(MLV_BUTTON_LEFT, MLV_RELEASED) && mouse_pressed) {
            mouse_pressed = 0;
        }
    }
    fill_point(&point, -1, -1);
    return point;
}
