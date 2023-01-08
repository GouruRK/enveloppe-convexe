/**
 * @file draw.c
 * @author Quentin Laborde - Kies Rémy
 * @brief Contient toutes les fonctions pour gérer l'affichage des 
 *        enveloppes
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../utils.h"

/**
 * @brief Permet de savoir si les coordonnées (`x`, `y`) sont comprises dans
 *        la "boîte" composée des points (`minX`, `minY`), (`maxX`, `maxY`)
 * 
 * @return int Renvoie `1` si (`x`, `y`) est dans la boite, `0` sinon
 */
int isInside(int x, int y, int minX, int maxX, int minY, int maxY) {
    return (x > minX && x < maxX) && (y > minY && y < maxY);
}

/**
 * @brief Crée une enveloppe convexe vide
 * 
 * @param maxlen La longueur maximale d'une enveloppe convexe
 *               Actuellement, la longueur est juste indicative
 *               Pour un nombre infini de point, mettre -1 par convention
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
 * @param maxlen Longueur maximale d'une enveloppe convexe
 *               Actuellement, la longueur est juste indicative
 *               Pour un nombre infini de point, mettre -1 par convention
 * @return ConvexHull* 
 */
ConvexHull* createConvexPointer(int maxlen) {
    ConvexHull* convex = (ConvexHull*)malloc(sizeof(ConvexHull));
    convex->poly = createPolygon();
    convex->curlen = 0;
    convex->maxlen = maxlen;
    return convex;
}

/**
 * @brief Créer une ListPoint vide
 * 
 * @param maxlen Longueur maximale d'une enveloppe convexe
 *               Actuellement, la longueur est juste indicative
 *               Pour un nombre infini de point, mettre -1 par convention
 * @return ListPoint 
 */
ListPoint createListPoint(int maxlen) {
    return createConvex(maxlen);
}

/**
 * @brief Créer un pointeur de ListPoint
 * 
 * @param maxlen Longueur maximale d'une enveloppe convexe
 *               Actuellement, la longueur est juste indicative
 *               Pour un nombre infini de point, mettre -1 par convention
 * @return ListPoint* 
 */
ListPoint* createListPointPointer(int maxlen) {
    return createConvexPointer(maxlen);
}

/**
 * @brief Dessine un point
 * 
 * @param p Coordonnées du point a afficher (p->x et p->y)
 * @param radius Rayon
 * @param color Couleur
 */
void drawPoint(Point* p, int radius, MLV_Color color) {
    MLV_draw_filled_circle(p->x, p->y, radius, color);
}

/**
 * @brief Dessine les points d'un polygone
 * 
 * @param poly Polygon contenant les points a dessiner
 * @param radius Rayon des points
 * @param color Couleur
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
 * @param convex Informations relatives a une enveloppe convexe (Points et 
 *               longueur)
 * @param color Couleur
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
 * @param convex L'enveloppe convexe
 * @param insidePoints Les points contenus dans l'enveloppe convexe
 * @param radius Rayon
 * @param drawFunction L'intéret d'avoir une fonction `drawFunction` est que
 *                     l'on peut passer en argument MLV_draw_polygon ou
 *                     MLV_draw_filled_polygon
 */
void drawAll(Window* window, ConvexHull* convex, ListPoint* insidePoints, 
             int radius, 
             void (*drawFunction)(const int*, const int*, int, MLV_Color)) {
    MLV_clear_window(MLV_COLOR_WHITE);
    drawPoly(*convex, COLOR_LINE, drawFunction);
    drawPoints((*convex).poly, radius, COLOR_OUTSIDE);
    drawPoints((*insidePoints).poly, radius, COLOR_INSIDE);
    printInfo(window, convex, insidePoints);    
    MLV_update_window();
}

/**
 * @brief Initialise les attributs de `window` 
 * 
 * @param window L'élément qui doit être initialisé
 * @param width La largeur de la fenêtre
 * @param height La hauteur de la fenêtre
 * @param panelHeight La hauteur du panel contenant les informations
 *                    sur l'actuelle enveloppe convexe
 */
void initWindow(Window* window, int width, int height, int panelHeight) {
    window->width = width;
    window->height = height;
    window->infoWidth = width;
    window->infoHeight = panelHeight;
    window->clickableWidth = width;
    window->clickableHeight = height - panelHeight;
}

/**
 * @brief Affiche les informations d'une enveloppe convexe
 * 
 * @param window Contient les paramètes de la fenêtre
 * @param convex L'enveloppe convexe
 * @param insidePoints Les points contenus dans l'enveloppe
 */
void printInfo(Window* window, ConvexHull* convex, ListPoint* insidePoints) {
    int points = 0;
    int inside = 0;
    if (convex && convex->poly) {
        points = convex->curlen;
    }
    if (insidePoints && insidePoints->poly) {
        inside = insidePoints->curlen;
    }
    MLV_draw_line(0, window->clickableHeight, window->infoWidth,
                  window->clickableHeight, MLV_COLOR_GRAY);
    int w, h;
    // distance moyenne entre les points de l'enveloppe
    MLV_get_size_of_text("Total des points : %d", &w, &h, points + inside);
    MLV_draw_text(window->infoWidth * 1/7 - w/2,
                  window->clickableHeight + window->infoHeight/2 - h/2,
                  "Total des points : %d",
                  MLV_COLOR_BLACK,
                  points + inside);

    MLV_get_size_of_text("Points qui composent l'enveloppe : %d", &w, &h,
                         points);
    MLV_draw_text(window->infoWidth * 3/7 - w/2,
                  window->clickableHeight + window->infoHeight/2 - h/2,
                  "Points qui composent l'enveloppe : %d",
                  MLV_COLOR_BLACK,
                  points);
    MLV_get_size_of_text("Points dans l'enveloppe : %d", &w, &h, inside);
    MLV_draw_text(window->infoWidth * 5/7 - w/2,
                  window->clickableHeight + window->infoHeight/2 - h/2,
                  "Points dans l'enveloppe : %d",
                  MLV_COLOR_BLACK,
                  inside);
}
