#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>


#include "../include/convexhull.h"
#include "../include/struct.h"
#include "../include/list.h"
#include "../include/triangle.h"
#include "../include/graphic.h"

void create_convexhull(int* stop, int nb_points, Point (*get_point)(int*, int, Window*), Window* win) {
    draw_raw_convex_information(0, 0, win);
    MLV_update_window();
    Convex convexhull = create_convex();
    int err = init_convexhull(&convexhull, stop, nb_points, get_point, win);
    if (!err) {
        return;
    }
    Array points = create_array();
    Point point;
    int res, h_pressed = 0, show_points = 1, next_point = 1;
    while (!(*stop)) {

        if (next_point) {
            point = get_point(stop, nb_points, win);
        }
        if (*stop) {
            break;
        }
        if (point.x < 0) {
            next_point = 0;
        } else {
            res = new_point(&convexhull, &points, point);
            if (!res) {
                break;
            }
        }

        if (check_key_position(MLV_KEYBOARD_h, MLV_PRESSED) && !h_pressed) {
            h_pressed = 1;
            show_points = !show_points;
        } else if (check_key_position(MLV_KEYBOARD_h, MLV_RELEASED) && h_pressed) {
            h_pressed = 0;
        }

        MLV_clear_window(MLV_COLOR_WHITE);
        draw_outline_points(convexhull, show_points);
        if (show_points) {
            draw_inside_points(points);
        }
        draw_convex_information(convexhull, points, win);
        MLV_update_window();
    }
    free_array(&points);
    free_convex(&convexhull);
}

void create_inception_convexhull(int* stop, int nb_points, Point (*get_point)(int*, int, Window*), Window* win) {
    draw_raw_inception_convex_information(0, 0, win);
    MLV_update_window();

    int nb_hulls;
    if (nb_points < 0) {
        nb_hulls = 30;
    } else {
        if (nb_points < 100) {
            nb_hulls = nb_points / 2;    
        } else {
            nb_hulls = nb_points / 10;
        }
    }
    InceptionConvex incepconv = create_inception_convex(nb_hulls);
    if (!(incepconv.tab_convex)) {
        return;
    }
    Point point;
    int res, h_pressed = 0, show_points = 1, next_point = 1;
    while (!(*stop)) {
        if (next_point) {
            point = get_point(stop, nb_points, win);
        }
        if (*stop) {
            break;
        }
        if (point.x < 0) {
            next_point = 0;
        } else {
            incepconv.total_points++;
            res = new_point_rec(&incepconv, 0, point);
            if (!res) {
                break;
            }
        }

        if (check_key_position(MLV_KEYBOARD_h, MLV_PRESSED) && !h_pressed) {
            h_pressed = 1;
            show_points = !show_points;
        } else if (check_key_position(MLV_KEYBOARD_h, MLV_RELEASED) && h_pressed) {
            h_pressed = 0;
        }

        MLV_clear_window(MLV_COLOR_WHITE);
        
        draw_inception_convex(incepconv, show_points);
        draw_inception_convex_information(incepconv, win);
        MLV_update_window();
    }
    free_inception_convex(&incepconv);
}

int init_convexhull(Convex* convex, int* stop, int nb_points, Point (*get_point)(int*, int, Window*), Window* win) {
    Point p0, p1;
    p0 = get_point(stop, nb_points, win);
    if (*stop || p0.x < 0) {
        return 0;
    }
    draw_outline_point(p0);
    MLV_update_window();
    p1 = get_point(stop, nb_points, win);
    if (*stop || p1.x < 0) {
        return 0;
    }
    if (p0.x == p1.x && p0.y == p1.y) {
        p1.x++;
    }
    draw_outline_point(p1);
    draw_line(p0, p1);
    MLV_update_window();
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
    if (depth == incepconv->maxlen - 1) {
        if (!add_point(&(incepconv->tab_convex[depth].poly), point, add_vertex_tail)) {
            return 0;
        }
        return 1;
    }

    Convex* convexhull = &(incepconv->tab_convex[depth]);

    if (convexhull->curlen == 0) {
        incepconv->curlen++;
    }

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
            free_vertex(v);
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
            free_vertex(v);
        } else {
            break;
        }
    }
    return 1;
}

// old implementation
/*int new_point_rec(InceptionConvex* convexs, int depth, Point p) {
    // si tableau trop petit
    if (convexs->maxlen == depth) {
        resize_inception_convex(convexs);
        if (!(convexs->tab_convex)) {
            return 0;
        }
    }

    Convex* convex = &(convexs->tab_convex[depth]);

    // si cas init
    if (convexs->tab_convex[depth].curlen < 2) {
        if (!add_point(&(convex->poly), p, add_vertex_tail)) {
            return 0;
        }
        convexs->tab_convex[depth].curlen++;
        return 1;
    }

    // On regarde si le point est a l'intérieur de l'enveloppe
    Vertex* head = NULL;
    Vertex* point;
    int direct;
    while (head != convex->poly) {
        if (!head) {
            head = convex->poly;
        }
        direct = is_direct(p, convex->poly->point, convex->poly->next->point);
        convex->poly = convex->poly->next;
        if (direct) {
            continue;
        } else {
            // on insère p entre [Si, Si+1]
            // on insère a (*poly)->next pcq sinon on insère avant Si
            // *poly = (*poly)->next;
            if (!add_point(&(convex->poly), p, add_vertex_head)) {
                return 0;
            }
            // point devient l'endroit où on a insérer le point
            point = convex->poly;
            convexs->tab_convex[depth].curlen++;
            break;
        }
    }
    if (direct) {
        new_point_rec(convexs, depth + 1, p);
        return 1;
    }
    // On fixe le début de poly au nouveau point
    convex->poly = point;

    // nettoyage avant
    while (1) {
        direct = is_direct(convex->poly->point, convex->poly->next->point,
                          convex->poly->next->next->point);
        if (!direct) {
            Vertex* v = extract_vertex_head(&(convex->poly->next));
            new_point_rec(convexs, depth + 1, v->point);
            convexs->tab_convex[depth].curlen--;
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
            Vertex* v = extract_vertex_head(&(convex->poly));
            new_point_rec(convexs, depth + 1, v->point);
            convex->poly = keep;
            convexs->tab_convex[depth].curlen--;
        } else {
            break;
        }
    }
    return 1;
}*/
