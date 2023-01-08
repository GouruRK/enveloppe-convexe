/**
 * @file enveloppe.c
 * @author Quentin Laborde - Rémy Kies
 * @brief Génération d'enveloppe convexe, par click, ou génération 
 *        aléatoire en suivant une forme (carré, cercle)
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <math.h>
#include <time.h>

#include "../utils.h"

/*
Lignes de compilation :

clang -c ../args/errs.c -Wall -std=c17
clang -c ../list/list.c errs.o -Wall -std=c17
clang -c ../math/math.c list.o errs.o -Wall -std=c17
clang -c draw.c -Wall -std=c17
clang -c graphic.c -Wall -std=c17
clang enveloppe.c graphic.o math.o list.o draw.o errs.o -g3 -Wall -std=c17 -o env -lMLV -lm
*/

/**
 * @brief Permet de free tous les polygomes
 *
 * @param convex L'enveloppe convexe
 * @param insidePoints Les points dans l'enveloppe convexe
 * @param p Point
 */
void freeAll(ConvexHull* convex, ListPoint* insidePoints, Point* p) {
    freePolygon(&(convex->poly));
    freePolygon(&(insidePoints->poly));
    free(p);
}

/**
 * @brief Permet d'ajouter un point dans une enveloppe convexe
 *
 * @param convex L'enveloppe convexe
 * @param insidePoints Les points dans l'enveloppe convexe
 * @param p Nouveau point
 */
void newPoint(ConvexHull* convex, ListPoint* insidePoints, Point* p) {
    // On regarde si le point est a l'intérieur de l'enveloppe
    Vertex* head = NULL;
    Vertex* point;
    int direct;
    while (head != convex->poly) {
        if (!head) {
            head = convex->poly;
        }
        direct = isDirect(p, convex->poly->p, convex->poly->next->p);
        convex->poly = convex->poly->next;
        if (direct) {
            continue;
        } else {
            // on insère p entre [Si, Si+1]
            // on insère a (*poly)->next pcq sinon on insère avant Si
            // *poly = (*poly)->next;
            if (!addPoint(&(convex->poly), p, addVertexHead)) {
                freeAll(convex, insidePoints, p);
                exit(1);
            }
            // point devient l'endroit où on a insérer le point
            point = convex->poly;
            convex->curlen++;
            break;
        }
    }
    if (direct) {
        if (!addPoint(&(insidePoints->poly), p, addVertexHead)) {
            freeAll(convex, insidePoints, p);
            exit(1);
        }
        insidePoints->curlen++;
        return;
    }
    // On fixe le début de poly au nouveau point
    convex->poly = point;

    // nettoyage avant
    while (1) {
        direct = isDirect(convex->poly->p, convex->poly->next->p,
                          convex->poly->next->next->p);
        if (!direct) {
            Vertex* v = extractVertexHead(&(convex->poly->next));
            addVertexHead(&(insidePoints->poly), v);
            convex->curlen--;
            insidePoints->curlen++;
        } else {
            break;
        }
    }
    // nettoyage arriere
    while (1) {
        direct = isDirect(convex->poly->p, convex->poly->prev->prev->p,
                          convex->poly->prev->p);
        if (!direct) {
            Vertex* keep = convex->poly;
            convex->poly = convex->poly->prev;
            Vertex* v = extractVertexHead(&(convex->poly));
            addVertexHead(&(insidePoints->poly), v);
            convex->poly = keep;
            convex->curlen--;
            insidePoints->curlen++;
        } else {
            break;
        }
    }
}

/**
 * @brief Renvoie `-1` ou `1` aléatoirement
 *
 * @return int
 */
int r_sign(void) {
    return !(rand() % 2) ? -1 : 1;
}

/**
 * @brief Crée et affiche une enveloppe convexe en forme de cercle
 *        ou d'ellipse (param coef) qui s'agrandit
 * 
 * @param window Les paramètres de la fenêtre
 * @param convex L'enveloppe convexe
 * @param radius_max Rayon maximum du cercle
 * @param nb_points Nombre de points à générer 
 * @param wait Temps d'attente entre chaque itération (graphique uniquement)
 * @param coef Coefficient d'aplatissement
 */
void drawCircleRandomRising(Window* window, ConvexHull* convex, 
                            int radius_max, int nb_points, int wait, 
                            float coef) {
    ListPoint insidePoints = createListPoint(nb_points);
    double nb_random, radius = radius_max / (float)nb_points;

    for (int i = 0; i < nb_points; i++) {
        Point* p = createPoint();
        if (!p) {
            freeAll(convex, &insidePoints, NULL);
            exit(1);
        }
        nb_random = rand();
        fillPoint(p, 
                  window->width/2 + radius * coef * i * cos(nb_random),
                  window->clickableHeight/2 + radius * i * sin(nb_random));

        if (i == 2) {
            if (isPointEqual(convex->poly->p, convex->poly->next->p)) {
                convex->poly->next->p->x++;
            }
            convex->curlen = 2;
        }
        if (i < 2) {
            drawPoint(p, RADIUS, COLOR_OUTSIDE);
            if (i == 1) {
                MLV_draw_line(p->x, p->y, convex->poly->p->x,
                              convex->poly->p->y, COLOR_LINE);
            }
            if (!addPoint(&(convex->poly), p, addVertexTail)) {
                freeAll(convex, &insidePoints, p);
                exit(1);
            }
            MLV_update_window();
        } else {
            newPoint(convex, &insidePoints, p);
            drawAll(window, convex, &insidePoints, RADIUS, MLV_draw_polygon);
        }
        MLV_update_window();

        if (wait) {
            MLV_wait_keyboard_or_mouse_or_milliseconds(NULL, NULL, NULL,
                                                       NULL, NULL, wait);
        }
    }
    freeAll(convex, &insidePoints, NULL);
}

/**
 * @brief Crée et affiche une enveloppe convexe
 *        en forme de cercle ou d'ellipse (param coef)
 *
 * @param window Les paramètres de la fenêtre
 * @param convex L'enveloppe convexe
 * @param radius_max Rayon maximum du cercle
 * @param nb_points Nombre de points à générer 
 * @param wait Temps d'attente entre chaque itération (graphique uniquement)
 * @param coef Coefficient d'aplatissement
 */
void drawCircleRandom(Window* window, ConvexHull* convex, int radius_max, 
                      int nb_points, int wait, float coef) {
    ListPoint insidePoints = createListPoint(nb_points);
    double nb_random;
    int radius;

    for (int i = 0; i < nb_points; i++) {
        Point* p = createPoint();
        if (!p) {
            freeAll(convex, &insidePoints, NULL);
            exit(1);
        }
        nb_random = rand();
        radius = rand() % radius_max;
        fillPoint(p, 
                  window->width/2 + radius * coef * cos(nb_random),
                  window->clickableHeight/2 + radius * sin(nb_random));

        if (i == 2) {
            if (isPointEqual(convex->poly->p, convex->poly->next->p)) {
                convex->poly->next->p->x++;
            }
            convex->curlen = 2;
        }
        if (i < 2) {
            drawPoint(p, RADIUS, COLOR_OUTSIDE);
            if (i == 1) {
                MLV_draw_line(p->x, p->y, convex->poly->p->x,
                              convex->poly->p->y, COLOR_LINE);
            }
            if (!addPoint(&(convex->poly), p, addVertexTail)) {
                freeAll(convex, &insidePoints, p);
                exit(1);
            }
            MLV_update_window();
        } else {
            newPoint(convex, &insidePoints, p);
            drawAll(window, convex, &insidePoints, RADIUS, MLV_draw_polygon);
        }
        MLV_update_window();

        if (wait) {
            MLV_wait_keyboard_or_mouse_or_milliseconds(NULL, NULL, NULL,
                                                       NULL, NULL, wait);
        }
    }
    freeAll(convex, &insidePoints, NULL);
}

/**
 * @brief Crée et affiche une enveloppe convexe
 *        en forme de carré ou de rectangle (param coef)
 *
 * @param window Les paramètres de la fenêtre
 * @param convex L'enveloppe convexe
 * @param radius_max Rayon maximum du cercle
 * @param nb_points Nombre de points à générer 
 * @param wait Temps d'attente entre chaque itération (graphique uniquement)
 * @param coef Coefficient d'aplatissement
 */
void drawSquareRandom(Window* window, ConvexHull* convex, int radius_max,
                      int nb_points, int wait, float coef) {
    ListPoint insidePoints = createListPoint(nb_points);

    for (int i = 0; i < nb_points; i++) {
        Point* p = createPoint();
        if (!p) {
            freeAll(convex, &insidePoints, NULL);
            exit(1);
        }
        fillPoint(p,
                  window->width/2 + r_sign() * coef * (rand() % radius_max),
                  window->clickableHeight/2 + r_sign()*(rand()%radius_max));

        if (i == 2) {
            if (isPointEqual(convex->poly->p, convex->poly->next->p)) {
                convex->poly->next->p->x++;
            }
            convex->curlen = 2;
        }
        if (i < 2) {
            drawPoint(p, RADIUS, COLOR_OUTSIDE);
            if (i == 1) {
                MLV_draw_line(p->x, p->y, convex->poly->p->x,
                              convex->poly->p->y, COLOR_LINE);
            }
            if (!addPoint(&(convex->poly), p, addVertexTail)) {
                freeAll(convex, &insidePoints, p);
                exit(1);
            }
            MLV_update_window();
        } else {
            newPoint(convex, &insidePoints, p);
            drawAll(window, convex, &insidePoints, RADIUS, MLV_draw_polygon);
        }
        MLV_update_window();

        if (wait) {
            MLV_wait_keyboard_or_mouse_or_milliseconds(NULL, NULL, NULL,
                                                       NULL, NULL, wait);
        }
    }
    freeAll(convex, &insidePoints, NULL);
}

/**
 * @brief Crée et affiche une enveloppe convexe en forme de carré
 *        ou de rectangle (param coef) et qui s'agrandit
 *
 * @param window Les paramètres de la fenêtre
 * @param convex L'enveloppe convexe
 * @param radius_max Rayon maximum du cercle
 * @param nb_points Nombre de points à générer 
 * @param wait Temps d'attente entre chaque itération (graphique uniquement)
 * @param coef Coefficient d'aplatissement
 */
void drawSquareRandomRising(Window* window, ConvexHull* convex, 
                            int radius_max, int nb_points, int wait, 
                            float coef) {
    ListPoint insidePoints = createListPoint(nb_points);
    float radius = radius_max / (float)nb_points;

    for (int i = 0; i < nb_points; i++) {
        Point* p = createPoint();
        if (!p) {
            freeAll(convex, &insidePoints, NULL);
            exit(1);
        }
        int nb = (radius * i) + 1;
        fillPoint(p,
                  window->width/2 + r_sign() * coef * (rand() % nb),
                  window->clickableHeight/2 + r_sign()*(rand() % nb));

        if (i == 2) {
            if (isPointEqual(convex->poly->p, convex->poly->next->p)) {
                convex->poly->next->p->x++;
            }
            convex->curlen = 2;
        }
        if (i < 2) {
            drawPoint(p, RADIUS, COLOR_OUTSIDE);
            if (i == 1) {
                MLV_draw_line(p->x, p->y, convex->poly->p->x,
                              convex->poly->p->y, COLOR_LINE);
            }
            if (!addPoint(&(convex->poly), p, addVertexTail)) {
                freeAll(convex, &insidePoints, p);
                exit(1);
            }
            printInfo(window, convex, &insidePoints);
            MLV_update_window();
        } else {
            newPoint(convex, &insidePoints, p);
            drawAll(window, convex, &insidePoints, RADIUS, MLV_draw_polygon);
        }
        MLV_actualise_window();

        if (wait) {
            MLV_wait_keyboard_or_mouse_or_milliseconds(NULL, NULL, NULL,
                                                       NULL, NULL, wait);
        }
    }
    freeAll(convex, &insidePoints, NULL);
}

/**
 * @brief Initialise une enveloppe convexe crée par des clicks
 * 
 * @param window Paramètres de la fenêtre
 * @param convex L'enveloppe convexe
 */
void initConvexClick(Window* window, ConvexHull* convex) {
    int points = 0, x, y;
    Point *p0 = createPoint(), *p1 = createPoint();
    if (!p0 || !p1) {
        freeAll(convex, NULL, p0);
        free(p1);
        exit(1);
    }
    while (points < 2) {
        MLV_wait_mouse(&x, &y);
        int inside = isInside(x, y, 0, window->clickableWidth, 0, 
                              window->clickableHeight);
        if (!inside) {
            continue;
        }
        if (points == 0) {
            fillPoint(p0, x, y);
            drawPoint(p0, RADIUS, COLOR_OUTSIDE);
        } else {
            fillPoint(p1, x, y);
            drawPoint(p1, RADIUS, COLOR_OUTSIDE);
            MLV_draw_line(p0->x, p0->y, p1->x, p1->y, COLOR_LINE);
        }
        MLV_update_window();
        points++;
    }
    if (p0->x == p1->x && p0->y == p1->y) {
        p1->x++;
    }
    addPoint(&(convex->poly), p0, addVertexTail);
    addPoint(&(convex->poly), p1, addVertexTail);
    convex->curlen = 2;
    MLV_update_window();
}

/**
 * @brief Crée et affiche une enveloppe convexe généré par les clicks
 *        de l'utilisateur
 * 
 * @param window Paramètres de la fenêtre
 * @param convex Enveloppe convexe
 */
void drawConvexClick(Window* window, ConvexHull* convex) {
    ListPoint insidePoints = createListPoint(-1);
    MLV_clear_window(MLV_COLOR_WHITE);
    printInfo(window, NULL, NULL);
    MLV_update_window();
    initConvexClick(window, convex);
    int x, y;
    while (1) {
        MLV_wait_mouse(&x, &y);
        int inside = isInside(x, y, 0, window->clickableWidth, 0,
                              window->clickableHeight);
        if (!inside) {
            continue;
        }
        Point* p = createPoint();
        if (!p) {
            freeAll(convex, &insidePoints, NULL);
            exit(1);
        }
        fillPoint(p, x, y);
        newPoint(convex, &insidePoints, p);
        MLV_clear_window(MLV_COLOR_WHITE);
        drawAll(window, convex, &insidePoints, RADIUS, MLV_draw_polygon);
        MLV_update_window();
    }
    freeAll(convex, &insidePoints, NULL);
}

int main(void) {
    srand(time(NULL));
    Window window;
    initWindow(&window, 1000, 1000, 50);
    ConvexHull convex = createConvex(-1);
    MLV_create_window("Setting convex hull", "Setting", window.width, 
                      window.height);
    MLV_clear_window(MLV_COLOR_WHITE);
    printInfo(&window, NULL, NULL);
    drawConvexClick(&window, &convex);
    // drawCircleRandomRising(&window, &convex, 400, 400, 1000, 1000, 2000,
    //                        1);
    // drawCircleRandom(&window, &convex, 400, 400, 1000, 1000, 0, 1);
    // drawSquareRandom(&window, &convex, 400, 400, 1000, 1000, 0, 1);
    // drawSquareRandomRising(&window, &convex, 400, 400, 1000, 1000,
    //                       0, 0.5);

    MLV_wait_seconds(2);
    MLV_free_window();
    return 0;
}
