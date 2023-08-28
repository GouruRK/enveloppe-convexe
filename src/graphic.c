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

void draw_inside_point(Point* point) {
    draw_point(point, INSIDE_POINT_COLOR);
}

void draw_online_point(Point* point) {
    draw_point(point, ONLINE_POINT_COLOR);
}

void draw_point(Point* point, MLV_Color color) {
    MLV_draw_filled_circle(point->x, point->y, RADIUS, color);
}

void draw_line(Point* a, Point* b) {
    MLV_draw_line(a->x, a->y, b->x, b->y, LINE_COLOR);
}

void draw_array(Array points) {
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

void draw_outline(Convex convex) {
   Polygon polygon = convex.poly;
    if (polygon) {
        Vertex* head = polygon;
        Vertex* prev = polygon;
        polygon = polygon->next;
        while (head != polygon) {
            draw_online_point(polygon->point);
            draw_line(prev->point, polygon->point);
            prev = polygon;
            polygon = polygon->next;
        }
        draw_online_point(polygon->point);
        draw_line(prev->point, polygon->point);
    }
}
