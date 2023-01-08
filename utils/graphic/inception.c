/**
 * @file inception.c
 * @author Quentin Laborde - Kies Rémy
 * @brief Permet de créer des enveloppes convexes imbriquées
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../utils.h"

#define SIZECOLOR 6

/* Lignes de compilations :
clang -c ../args/errs.c -Wall -std=c17
clang -c ../list/list.c -Wall -std=c17
clang -c ../math/math.c list.o -Wall -std=c17
clang -c draw.c -Wall -std=c17
clang -c graphic.c -Wall -std=c17 -lMLV
clang inception.c graphic.o math.o list.o draw.o errs.o -g3 -Wall -std=c17 -o inc -lMLV -lm
*/

/**
 * @brief Permet de libérer la mémoire de tous les polygons dans `convexs`
 * 
 * @param convexs Liste d'enveloppes convexes
 */
void freeAllList(InceptionConvex* convexs) {
    for (int i = 0; i < convexs->size; i++) {
        freePolygon(&(convexs->tabconvex[i]->poly));
        free(convexs->tabconvex[i]);
    }
    free(convexs->tabconvex);
}

/**
 * @brief Permet d'ajouter un point récursivement a la liste des 
 *        enveloppes convexes
 * 
 * @param convexs Listes des enveloppes
 * @param depth Indice de l'enveloppe courrante
 * @param p Point a ajouter
 */
void newPointRec(InceptionConvex* convexs, int depth, Point* p) {
    // si tableau trop petit
    if (convexs->size == depth) {
        ConvexHull** temp = convexs->tabconvex;
        temp = realloc(temp, (++convexs->size) * sizeof(ConvexHull*));
        if (!(*temp)) {
            errAlloc();
            freeAllList(convexs);
            free(p);
            exit(1);
        }
        convexs->tabconvex = temp;
        convexs->tabconvex[depth] = createConvexPointer(-1);
    }

    ConvexHull* convex = convexs->tabconvex[depth];

    // si cas init
    if (convexs->tabconvex[depth]->curlen < 2) {
        if (!addPoint(&(convex->poly), p, addVertexTail)) {
            freeAllList(convexs);
            free(p);
            exit(1);
        }
        convexs->tabconvex[depth]->curlen++;
        return;
    }

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
                freeAllList(convexs);
                free(p);
                exit(1);
            }
            // point devient l'endroit où on a insérer le point
            point = convex->poly;
            convexs->tabconvex[depth]->curlen++;
            break;
        }
    }
    if (direct) {
        newPointRec(convexs, depth + 1, p);
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
            newPointRec(convexs, depth+1, v->p);
            convexs->tabconvex[depth]->curlen--;
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
            newPointRec(convexs, depth+1, v->p);
            convex->poly = keep;
            convexs->tabconvex[depth]->curlen--;
        } else {
            break;
        }
    }
}

/**
 * @brief Affiche les informations des enveloppes convexes
 * 
 * @param window Informations de la fenêtre d'affichage 
 * @param convexs Listes des enveloppes convexes
 */
void printInfoRec(Window* window, InceptionConvex convexs) {
    int points = 0;
    for (int i = 0; i < convexs.size; i++) {
        points += convexs.tabconvex[i]->curlen;
    }
    
    MLV_draw_line(0, window->clickableHeight, window->infoWidth, 
                  window->clickableHeight, MLV_COLOR_GRAY);
    int w, h;
    MLV_get_size_of_text("Nombre de points : %d", &w, &h, points);
    MLV_draw_text(window->infoWidth * 1/3 - w/2,
                  window->clickableHeight + window->infoHeight/2 - h/2,
                  "Nombre de points : %d",
                  MLV_COLOR_BLACK,
                  points);
    MLV_get_size_of_text("Nombre d'enveloppes : %d", &w, &h, convexs.size);
    MLV_draw_text(window->infoWidth * 2/3 - w/2,
                  window->clickableHeight + window->infoHeight/2 - h/2,
                  "Nombre d'enveloppes : %d",
                  MLV_COLOR_BLACK,
                  convexs.size);
}

/**
 * @brief Permet de dessiner des enveloppes convexes imbriquées
 * 
 */
void drawInceptionClick(void) {
    Window window;
    initWindow(&window, 1000, 1000, 50);
    MLV_Color tabcolora[SIZECOLOR] = {
        MLV_rgba(0, 0, 255, 100),
        MLV_rgba(0, 255, 0, 100),
        MLV_rgba(255, 0, 0, 100),
        MLV_rgba(255, 0, 255, 100),
        MLV_rgba(0, 255, 255, 100),
        MLV_rgba(255, 255, 0, 100)};
    MLV_Color tabcolor[SIZECOLOR] = {
        MLV_rgba(0, 0, 255, 255),
        MLV_rgba(0, 255, 0, 255),
        MLV_rgba(255, 0, 0, 255),
        MLV_rgba(255, 0, 255, 255),
        MLV_rgba(0, 255, 255, 255),
        MLV_rgba(255, 255, 0, 255)};
    MLV_create_window("", "", 1000, 1000);
    MLV_clear_window(MLV_COLOR_WHITE);
    int x, y;
    InceptionConvex convexs;
    convexs.tabconvex = (ConvexHull**)malloc(sizeof(ConvexHull*));
    if (!convexs.tabconvex) {
        exit(1);
    }
    convexs.tabconvex[0] = createConvexPointer(-1);
    if (!convexs.tabconvex[0]) {
        free(convexs.tabconvex);
        exit(1);
    }
    convexs.size = 1;
    printInfoRec(&window, convexs);
    MLV_update_window();
    while (1) {
        Point* p = createPoint();
        if (!p) {
            freeAllList(&convexs);
            exit(1);
        }
        MLV_wait_mouse(&x, &y);
        fillPoint(p, x, y);
        newPointRec(&convexs, 0, p);
        MLV_clear_window(MLV_COLOR_WHITE);
        for (int i = 0; i < convexs.size; i++) {
            drawPoly(*(convexs.tabconvex[i]), tabcolora[i % SIZECOLOR],
                     MLV_draw_filled_polygon);
            drawPoints(convexs.tabconvex[i]->poly, RADIUS,
                       tabcolor[i % SIZECOLOR]);
        }
        printInfoRec(&window, convexs);
        MLV_update_window();
    }
    freeAllList(&convexs);
}

int main(void) {
    drawInceptionClick();
    return 0;
}