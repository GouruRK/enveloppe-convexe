/**
 * @file draw.c
 * @author Quentin Laborde - Kies Rémy
 * @brief Contient toutes les fonctions pour gérer l'affichage des enveloppes
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../utils.h"

/**
 * @brief Crée une enveloppe convexe vide
 * 
 * @param maxlen 
 * @return ConvexHull 
 */
ConvexHull createConvex(int maxlen) {
    ConvexHull convex;
    convex.poly = createPolygon();
    convex.curlen = 0;
    convex.maxlen = maxlen;
    return convex;
}

/**
 * @brief Créer un pointeur d'enveloppe convexe
 * 
 * @param maxlen 
 * @return ConvexHull* 
 */
ConvexHull* createConvexPointeur(int maxlen) {
    ConvexHull* convex = (ConvexHull*)malloc(sizeof(ConvexHull));
    convex->poly = createPolygon();
    convex->curlen = 0;
    convex->maxlen = maxlen;
    return convex;
}

/**
 * @brief Dessine un point
 * 
 * @param p 
 * @param radius 
 * @param color 
 */
void drawPoint(Point* p, int radius, MLV_Color color) {
    MLV_draw_filled_circle(p->x, p->y, radius, color);
}

/**
 * @brief Dessine les points d'un polygone
 * 
 * @param poly 
 * @param radius 
 * @param color 
 */
void drawPoints(Polygon poly, int radius, MLV_Color color) {
    if (poly) {
        Vertex* head = poly->prev;
        while (head != poly) {
            drawPoint(poly->p, radius, color);
            poly = poly->next;
        }
        drawPoint(poly->p, radius, color);
    }
}

/**
 * @brief Affiche les contours d'ene enveloppe convexe
 * 
 * @param convex 
 * @param color 
 * @param drawFunction L'intéret d'avoir une fonction `drawFunction` est que
 *                     l'on peut passer en argument MLV_draw_polygon ou
 *                     MLV_draw_filled_polygon
 */
void drawPoly(ConvexHull convex, MLV_Color color,
              void (*drawFunction)(const int*, const int*, int, MLV_Color)) {
    if (!convex.curlen) {
        return;
    }
    int* vx = malloc(sizeof(int) * convex.curlen);
    int* vy = malloc(sizeof(int) * convex.curlen);
    if (!vx || !vy) {
        exit(1);
    }
    for (int i = 0; i < convex.curlen; i++) {
        vx[i] = convex.poly->p->x;
        vy[i] = convex.poly->p->y;
        convex.poly = convex.poly->next;
    }
    drawFunction(vx, vy, convex.curlen, color);
    free(vx);
    free(vy);
}

/**
 * @brief Affiche un triangle de points
 * 
 * @param A 
 * @param B 
 * @param C 
 */
void drawTriangle(Point* A, Point* B, Point* C) {
    MLV_Color color = isDirect(A, B, C) ? MLV_COLOR_GREEN : MLV_COLOR_RED;
    MLV_draw_line(A->x, A->y, B->x, B->y, color);
    MLV_draw_line(A->x, A->y, C->x, C->y, color);
    MLV_draw_line(B->x, B->y, C->x, C->y, color);
    MLV_draw_text(A->x, A->y, "A", MLV_COLOR_PURPLE);
    MLV_draw_text(B->x, B->y, "B", MLV_COLOR_PURPLE);
    MLV_draw_text(C->x, C->y, "C", MLV_COLOR_PURPLE);
    MLV_update_window();
}

/**
 * @brief Permet de dessiner directement une enveloppe convexe ainsi que les
 *        points qu'elle englobe
 * 
 * @param convex 
 * @param insidePoints 
 * @param radius 
 * @param drawFunction 
 */
void drawAll(ConvexHull* convex, ConvexHull* insidePoints, int radius,
              void (*drawFunction)(const int*, const int*, int, MLV_Color)) {
    MLV_clear_window(MLV_COLOR_WHITE);
    drawPoly(*convex, COLOR_LINE, drawFunction);
    drawPoints((*convex).poly, radius, COLOR_OUTSIDE);
    drawPoints((*insidePoints).poly, radius, COLOR_INSIDE);
    MLV_update_window();
}