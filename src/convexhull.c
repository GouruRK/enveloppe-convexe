#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "../include/convexhull.h"
#include "../include/struct.h"
#include "../include/list.h"
#include "../include/math.h"
#include "../include/graphic.h"

void create_convexhull(int* stop) {
    Convex convexhull = create_convex();
    int err = init_convexhull(&convexhull, stop);
    if (!err) {
        return;
    }
    Array points = create_array();
    Point point;
    int x, y, mouse_pressed = 1;
    while (!(*stop)) {
        if (check_mouse_position(MLV_BUTTON_LEFT, MLV_PRESSED) && !mouse_pressed) {
            MLV_get_mouse_position(&x, &y);
            point = create_point(x, y);
            
            int res = new_point(&convexhull, &points, point);
            if (!res) {
                break;
            }
            MLV_clear_window(MLV_COLOR_WHITE);
            draw_outline(convexhull);
            draw_array(points);
            MLV_update_window();

            mouse_pressed = 1;
        } else if (check_mouse_position(MLV_BUTTON_LEFT, MLV_RELEASED) && mouse_pressed) {
            mouse_pressed = 0;
        }
    }
    free_array(&points);
    free_convex(&convexhull);
}

void create_inception_convexhull(int* stop) {
    InceptionConvex incepconv = create_inception_convex();
    if (!(incepconv.tab_convex)) {
        return;
    }

    int x, y, mouse_pressed = 1;
    while (!(*stop)) {
        if (check_mouse_position(MLV_BUTTON_LEFT, MLV_PRESSED) && !mouse_pressed) {
            MLV_get_mouse_position(&x, &y);
            Point point = create_point(x, y);

            int res = new_point_rec(&incepconv, 0, point);
            if (!res) {
                break;
            }

            MLV_clear_window(MLV_COLOR_WHITE);
            draw_inception_convex(incepconv);
            MLV_update_window();

            mouse_pressed = 1;
        } else if (check_mouse_position(MLV_BUTTON_LEFT, MLV_RELEASED) && mouse_pressed) {
            mouse_pressed = 0;
        }
    }
    free_inception_convex(&incepconv);
}

int init_convexhull(Convex* convex, int* stop) {
    int n_points = 0, x, y, mouse_pressed = 0;
    Point p0, p1;
    while (!(*stop) && n_points < 2) {
        if (check_mouse_position(MLV_BUTTON_LEFT, MLV_PRESSED) && !mouse_pressed) {
            MLV_get_mouse_position(&x, &y);
            
            if (!n_points) {
                fill_point(&p0, x, y);
                draw_online_point(p0);
            } else {
                fill_point(&p1, x, y);
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
        return 0;
    }
    if (p0.x == p1.x && p0.y == p1.y) {
        p1.x++;
    }
    add_point(&(convex->poly), p0, add_vertex_tail);
    add_point(&(convex->poly), p1, add_vertex_tail);
    convex->curlen = 2;
    return 1;
}



int new_point(Convex* convex, Array* inside_points, Point point) {
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
            if (!add_point(&(convex->poly), point, add_vertex_head)) {
                return 0;
            }
            point_container = convex->poly;
            convex->curlen++;
            break;
        }
    }
    if (direct) {
        if (!add_point(&(inside_points->poly), point, add_vertex_head)) {
            return 0;
        }
        inside_points->curlen++;
        return 1;
    }
    convex->poly = point_container;

    // front cleaning
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
    // back cleaning
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
    return 1;
}

int new_point_rec(InceptionConvex* incepconv, int depth, Point point) {
    // if not enough space, resize incepconv to add more
    if (incepconv->maxlen == depth) {
        resize_inception_convex(incepconv);
        if (!(incepconv->tab_convex)) {
            return 0;
        }
    }

    Convex* convexhull = &(incepconv->tab_convex[depth]);

    // initiate a polygon
    if (convexhull->curlen < 2) {
        if (!add_point(&(convexhull->poly), point, add_vertex_tail)) {
            return 0;
        }
        convexhull->curlen++;
        return 1;
    }

    Vertex* head = NULL;
    Vertex* vrtx;
    int direct;
    while (head != convexhull->poly) {
        if (!head) {
            head = convexhull->poly;
        }
        direct = is_direct(point, convexhull->poly->point, convexhull->poly->next->point);
        convexhull->poly = convexhull->poly->next;
        if (direct) {
            continue;
        } else {
            if (!add_point(&(convexhull->poly), point, add_vertex_head)) {
                return 0;
            }
            vrtx = convexhull->poly;
            convexhull->curlen++;
            break;
        }
    }
    if (direct) {
        new_point_rec(incepconv, depth + 1, point);
        return 1;
    }
    convexhull->poly = vrtx;

    // front cleaning
    while (1) {
        direct = is_direct(convexhull->poly->point, convexhull->poly->next->point,
                           convexhull->poly->next->next->point);
        if (!direct) {
            Vertex* v = extract_vertex_head(&(convexhull->poly->next));
            new_point_rec(incepconv, depth + 1, v->point);
            convexhull->curlen--;
        } else {
            break;
        }
    }
    // back cleaning
    while (1) {
        direct = is_direct(convexhull->poly->point, convexhull->poly->prev->prev->point,
                          convexhull->poly->prev->point);
        if (!direct) {
            Vertex* keep = convexhull->poly;
            convexhull->poly = convexhull->poly->prev;
            Vertex* v = extract_vertex_head(&(convexhull->poly));
            new_point_rec(incepconv, depth + 1, v->point);
            convexhull->poly = keep;
            convexhull->curlen--;
        } else {
            break;
        }
    }
    return 1;
}
