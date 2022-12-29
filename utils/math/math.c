#include "../utils.h"

/*
gcc -c ../list/list.c -Wall -std=c17
gcc math.c list.o -Wall -std=c17 -o math
*/

int isRight(Point* A, Point* B, Point* p) {
    return crossProduct(A, B, p) > 0;
}

/**
 * @brief Renvoie la distance entre deux points
 * 
 * @param A 
 * @param B 
 * @return float 
 */
int dist(Point* A, Point* B) {
    float distX = B->x - A->x;
    float distY = B->y - A->y;
    return distX*distX + distY*distY;
}


/**
 * @brief Renvoie le produit en croix des vecteurs pq et pr, qui est :
 *        - Positif si r est à droite du segment [p, q]
 *        - Négatif si r est à gauche du segment [p, q]
 *        - Nul si les trois points sont alignés
 * 
 * @param p 
 * @param q 
 * @param r 
 * @return int 
 */
int crossProduct(Point* p, Point* q, Point* r) {
    return (q->x - p->x)*(r->y - p->y) - (r->x - p->x)*(q->y - p->y);
}

/**
 * @brief Renvoie la liste des points qui sont a droite du segment [A, B]
 * 
 * @param poly 
 * @param A 
 * @param B 
 * @return int 
 */
void rightPoints(ConvexHull* convex, Point* A, Point* B, ConvexHull* res) {
    Vertex* head = NULL;
    while (head != convex->poly) {
        if (!head) {
            head = convex->poly;
        }
        if (isRight(A, B, convex->poly->p)) {
            addPoint(res, convex->poly->p, addVertexHead);
        }
        convex->poly = convex->poly->next;
    }
}

/**
 * @brief Renvoie le point le plus éloigné du segment [A, B]
 * 
 * @param poly 
 * @param A 
 * @param B 
 * @return Point* 
 */
Point* furtherestPoint(ConvexHull* convex, Point* A, Point* B) {
    int maxDist = 0;
    Point* maxPoint = NULL;
    Vertex* head = NULL;
    int dist;
    while (head != convex->poly) {
        if (!head) {
            head = convex->poly;
        }
        dist = crossProduct(A, B, convex->poly->p);
        if (dist > maxDist) {
            maxDist = dist;
            maxPoint = convex->poly->p;
        }
        convex->poly = convex->poly->next;
    }
    return maxPoint;
}

void quickHull(ConvexHull* convex, ConvexHull* res) {
    Point* p = searchVertexByFunction(convex, minX)->p;
    Point* q = searchVertexByFunction(convex, maxX)->p;
    ConvexHull E1 = createConvex(-1);
    ConvexHull E2 = createConvex(-1);
    quickHullAux(convex, &E1, p, q);
    quickHullAux(convex, &E2, q, p);
    // On retire le point d'intersection entre E1 et E2
    extractVertexHead(&E2);
    // On concatène le résultat
    concatConvex(&E1, &E2);
    concatConvex(res, &E1);
}

void quickHullAux(ConvexHull* convex, ConvexHull* res, Point* p, Point* q) {
    ConvexHull onRight = createConvex(-1);
    rightPoints(convex, p, q, &onRight);
    if (!onRight.poly) {
        addPoint(res, p, addVertexTail);
        addPoint(res, q, addVertexTail);
        return;
    }
    Point* r = furtherestPoint(&onRight, p, q);
    ConvexHull E1 = createConvex(-1);
    ConvexHull E2 = createConvex(-1);
    quickHullAux(&onRight, &E1, p, r);
    quickHullAux(&onRight, &E2, r, q);
    // On retire le point d'intersection entre E1 et E2
    extractVertexHead(&E2);
    // On concatène le résultat
    concatConvex(&E1, &E2);
    concatConvex(res, &E1);
}

/*int main(void) {
    Point* A = createPoint();
    Point* B = createPoint();
    fillPoint(A, 0, 0);
    fillPoint(B, 1, 1);
    printf("%d\n", dist(A, B));
    return 0;
}*/
