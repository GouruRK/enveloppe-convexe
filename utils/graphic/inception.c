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

/*
clang -c ../args/errs.c -Wall -std=c17
clang -c ../list/list.c -Wall -std=c17
clang -c ../math/math.c list.o -Wall -std=c17
clang -c draw.c -Wall -std=c17
clang -c graphic.c -Wall -std=c17 -lMLV
clang inception.c graphic.o math.o list.o draw.o errs.o -Wall -std=c17 -o inc -lMLV -lm
*/

void newPoint2(InceptionConvex* convexs, int depth, Point* p) {
    // si tableau trop petit
    if (convexs->size == depth) {
        ConvexHull* temp = convexs->tabconvex;
        temp = realloc(temp, (++convexs->size) * sizeof(ConvexHull));
        if (!temp) {
            printf("%s Problème d'allocation mémoire %s\n", RED, RESET);
            exit(1);
        }
        convexs->tabconvex = temp;
        convexs->tabconvex[depth] = createConvex(-1);
    }

    // si cas init
    if (convexs->tabconvex[depth].curlen < 2) {
        addPoint(&(convexs->tabconvex[depth].poly), p, addVertexTail);
        convexs->tabconvex[depth].curlen++;
        return;
    }

    // On regarde si le point est a l'intérieur de l'enveloppe
    Vertex* head = NULL;
    Vertex* point;
    int direct;
    while (head != convexs->tabconvex[depth].poly) {
        if (!head) {
            head = convexs->tabconvex[depth].poly;
        }
        direct = isDirect(p, convexs->tabconvex[depth].poly->p, convexs->tabconvex[depth].poly->next->p);
        convexs->tabconvex[depth].poly = convexs->tabconvex[depth].poly->next;
        if (direct) {
            continue;
        } else {
            // on insère p entre [Si, Si+1]
            // on insère a (*poly)->next pcq sinon on insère avant Si
            // *poly = (*poly)->next;
            addPoint(&(convexs->tabconvex[depth].poly), p, addVertexHead);
            // point devient l'endroit où on a insérer le point
            point = convexs->tabconvex[depth].poly;
            convexs->tabconvex[depth].curlen++;
            break;
        }
    }
    if (direct) {
        newPoint2(convexs, depth + 1, p);
        return;
    }
    // On fixe le début de poly au nouveau point
    convexs->tabconvex[depth].poly = point;

    // nettoyage avant
    while (1) {
        direct = isDirect(convexs->tabconvex[depth].poly->p, convexs->tabconvex[depth].poly->next->p, convexs->tabconvex[depth].poly->next->next->p);
        if (!direct) {
            Vertex* v = extractVertexHead(&(convexs->tabconvex[depth].poly->next));
            newPoint2(convexs, depth + 1, v->p);
            convexs->tabconvex[depth].curlen--;
        } else {
            break;
        }
    }
    // nettoyage arriere
    while (1) {
        direct = isDirect(convexs->tabconvex[depth].poly->p, convexs->tabconvex[depth].poly->prev->prev->p, convexs->tabconvex[depth].poly->prev->p);
        if (!direct) {
            Vertex* keep = convexs->tabconvex[depth].poly;
            convexs->tabconvex[depth].poly = convexs->tabconvex[depth].poly->prev;
            Vertex* v = extractVertexHead(&(convexs->tabconvex[depth].poly));
            newPoint2(convexs, depth + 1, v->p);
            convexs->tabconvex[depth].poly = keep;
            convexs->tabconvex[depth].curlen--;
        } else {
            break;
        }
    }
}

void printInfoRec(Window* window, InceptionConvex convexs) {
    int points = 0;
    for (int i = 0; i < convexs.size; i++) {
        points += convexs.tabconvex[i].curlen;
    }
    
    MLV_draw_line(0, window->clickableHeight, window->infoWidth, window->clickableHeight, MLV_COLOR_GRAY);
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

void DrawInceptionClick(void) {
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
    convexs.tabconvex = (ConvexHull*)malloc(sizeof(ConvexHull));
    convexs.tabconvex[0] = createConvex(-1);
    convexs.size = 1;
    printInfoRec(&window, convexs);
    MLV_update_window();
    while (1) {
        Point* p = createPoint();
        MLV_wait_mouse(&x, &y);
        fillPoint(p, x, y);
        newPoint2(&convexs, 0, p);
        MLV_clear_window(MLV_COLOR_WHITE);
        for (int i = 0; i < convexs.size; i++) {
            drawPoly(convexs.tabconvex[i], tabcolora[i % SIZECOLOR], MLV_draw_filled_polygon);
            drawPoints(convexs.tabconvex[i].poly, 2, tabcolor[i % SIZECOLOR]);
        }
        printInfoRec(&window, convexs);
        MLV_update_window();
    }
    MLV_free_window();
}

int main(void) {
    DrawInceptionClick();
    return 0;
}