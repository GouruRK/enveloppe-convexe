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

/* Lignes de compilation :
clang -c ../args/errs.c -Wall -std=c17
clang -c ../list/list.c -Wall -std=c17
clang -c ../math/math.c list.o -Wall -std=c17
clang -c draw.c -Wall -std=c17
clang -c graphic.c -Wall -std=c17 -lMLV
clang inception.c graphic.o math.o list.o draw.o errs.o -g3 -Wall -O0 -std=c17 -o inc -lMLV -lm
*/

void freeAllList(InceptionConvex* convexs) {
    for (int i = 0; i < convexs->size; i++) {
        freePolygon(&(convexs->tabconvex[i]->poly));
        free(convexs->tabconvex[i]);
    }
    free(convexs->tabconvex);
}

void newPoint2(InceptionConvex* convexs, int depth, Point* p) {
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
        convexs->tabconvex[depth] = createConvexPointeur(-1);
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
        newPoint2(convexs, depth+1, p);
        return;
    }
    // On fixe le début de poly au nouveau point
    convex->poly = point;

    // nettoyage avant
    while (1) {
        direct = isDirect(convex->poly->p, convex->poly->next->p, convex->poly->next->next->p);
        if (!direct) {
            Vertex* v = extractVertexHead(&(convex->poly->next));
            newPoint2(convexs, depth+1, v->p);
            convexs->tabconvex[depth]->curlen--;
        } else {
            break;
        }
    }
    // nettoyage arriere
    while (1) {
        direct = isDirect(convex->poly->p, convex->poly->prev->prev->p, convex->poly->prev->p);
        if (!direct) {
            Vertex* keep = convex->poly;
            convex->poly = convex->poly->prev;
            Vertex* v = extractVertexHead(&(convex->poly));
            newPoint2(convexs, depth+1, v->p);
            convex->poly = keep;
            convexs->tabconvex[depth]->curlen--;
        } else {
            break;
        }
    }
}

void DrawInceptionClick(void) {
    MLV_create_window("", "", 1000, 1000);
    MLV_clear_window(MLV_COLOR_WHITE);
    MLV_update_window();
    int x, y;
    InceptionConvex convexs;
    convexs.tabconvex = (ConvexHull**)malloc(sizeof(ConvexHull*));
    if (!convexs.tabconvex) {
        exit(1);
    }
    convexs.tabconvex[0] = createConvexPointeur(-1);
    if (!convexs.tabconvex[0]) {
        free(convexs.tabconvex);
        exit(1);
    }
    convexs.size = 1;
    while (1) {
        Point* p = createPoint();
        if (!p) {
            freeAllList(&convexs);
            exit(1);
        }
        MLV_wait_mouse(&x, &y);
        fillPoint(p, x, y);
        newPoint2(&convexs, 0, p);
        MLV_clear_window(MLV_COLOR_WHITE);
        for (int i = 0; i < convexs.size; i++) {
            drawPoly(*(convexs.tabconvex[i]), MLV_COLOR_BLACK, MLV_draw_polygon);
            drawPoints(convexs.tabconvex[i]->poly, 2, MLV_COLOR_BLUE);
        }
        MLV_update_window();
    }
    freeAllList(&convexs);
}

int main(void) {
    DrawInceptionClick();
    return 0;
}