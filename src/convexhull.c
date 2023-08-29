#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "../include/convexhull.h"
#include "../include/struct.h"
#include "../include/list.h"
#include "../include/math.h"
#include "../include/graphic.h"

void create_convexhull(int* stop) {
    Convex convexhull = create_convex(-1);
    int err = init_convexhull(&convexhull, stop);
    if (!err) {
        return;
    }

    Array points = create_array(-1);
    Point* point;
    int x, y, mouse_pressed = 1;
    while (!(*stop)) {
        if (check_mouse_position(MLV_BUTTON_LEFT, MLV_PRESSED) && !mouse_pressed) {
            MLV_get_mouse_position(&x, &y);
            point = create_filled_point(x, y);
            if (!point) {
                deep_free_convex(&convexhull);
                deep_free_array(&points);
                return;
            }
            
            new_point(&convexhull, &points, point);
            MLV_clear_window(MLV_COLOR_WHITE);
            draw_outline(convexhull);
            draw_array(points);
            MLV_update_window();

            mouse_pressed = 1;
        } else if (check_mouse_position(MLV_BUTTON_LEFT, MLV_RELEASED) && mouse_pressed) {
            mouse_pressed = 0;
        }
    }
    deep_free_array(&points);
    deep_free_convex(&convexhull);
}

int init_convexhull(Convex* convex, int* stop) {
    int n_points = 0, x, y, mouse_pressed = 0;
    Point* p0 = create_point();
    if (!p0) {
        return 0;
    }
    Point* p1 = create_point();
    if (!p1) {
        free_point(p0);
        return 0;
    }
    while (!(*stop) && n_points < 2) {
        if (check_mouse_position(MLV_BUTTON_LEFT, MLV_PRESSED) && !mouse_pressed) {
            MLV_get_mouse_position(&x, &y);
            
            if (!n_points) {
                fill_point(p0, x, y);
                draw_online_point(p0);
            } else {
                fill_point(p1, x, y);
                draw_online_point(p1);
                draw_line(p0, p1);
            }

            MLV_update_window();
            n_points++;
            mouse_pressed = 1;
        } else if (check_mouse_position(MLV_BUTTON_LEFT, MLV_RELEASED) && mouse_pressed) {
            mouse_pressed = 0;
        }
    }
    if (n_points != 2) {
        free_point(p0);
        free_point(p1);
        return 0;
    }
    if (p0->x == p1->x && p0->y == p1->y) {
        p1->x++;
    }
    add_point(&(convex->poly), p0, add_vertex_tail);
    add_point(&(convex->poly), p1, add_vertex_tail);
    convex->curlen = 2;
    return 1;
}



void new_point(Convex* convex, Array* inside_points, Point* point) {
    // On regarde si le point est a l'intérieur de l'enveloppe
    Vertex* head = NULL;
    Vertex* point_container;
    int direct;
    while (head != convex->poly) {
        if (!head) {
            head = convex->poly;
        }
        direct = is_direct(point, convex->poly->point, convex->poly->next->point);
        convex->poly = convex->poly->next;
        if (direct) {
            continue;
        } else {
            // on insère p entre [Si, Si+1]
            // on insère a (*poly)->next pcq sinon on insère avant Si
            // *poly = (*poly)->next;
            if (!add_point(&(convex->poly), point, add_vertex_head)) {
                // free
                exit(1);
            }
            // point devient l'endroit où on a insérer le point
            point_container = convex->poly;
            convex->curlen++;
            break;
        }
    }
    if (direct) {
        if (!add_point(&(inside_points->poly), point, add_vertex_head)) {
            // free
            exit(1);
        }
        inside_points->curlen++;
        return;
    }
    // On fixe le début de poly au nouveau point
    convex->poly = point_container;

    // nettoyage avant
    while (1) {
        direct = is_direct(convex->poly->point, convex->poly->next->point,
                          convex->poly->next->next->point);
        if (!direct) {
            Vertex* vrtx = extract_vertex_head(&(convex->poly->next));
            add_vertex_head(&(inside_points->poly), vrtx);
            convex->curlen--;
            inside_points->curlen++;
        } else {
            break;
        }
    }
    // nettoyage arriere
    while (1) {
        direct = is_direct(convex->poly->point, convex->poly->prev->prev->point,
                          convex->poly->prev->point);
        if (!direct) {
            Vertex* keep = convex->poly;
            convex->poly = convex->poly->prev;
            Vertex* vrtx = extract_vertex_head(&(convex->poly));
            add_vertex_head(&(inside_points->poly), vrtx);
            convex->poly = keep;
            convex->curlen--;
            inside_points->curlen++;
        } else {
            break;
        }
    }
}