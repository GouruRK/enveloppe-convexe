#include "../utils.h"

/*
gcc -c ../list/list.c -Wall -std=c17
gcc math.c list.o -Wall -std=c17 -o math
*/

static inline int isRight(Point* A, Point* B, Point* p) {
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
void rightPoints(Polygon* poly, Point* A, Point* B, Polygon* res) {
    Vertex* head = NULL;
    Vertex* vertex;
    while (head != *poly) {
        if (!head) {
            head = *poly;
        }
        if (isRight(A, B, (*poly)->p)) {
            vertex = createVertex();
            fillVertex(vertex, (*poly)->p);
            addVertexHead(res, vertex);
        }
        *poly = (*poly)->next;
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
Point* furtherestPoint(Polygon* poly, Point* A, Point* B) {
    int maxDist = 0;
    Point* maxPoint = NULL;
    Vertex* head = NULL;
    int dist;
    while (head != *poly) {
        if (!head) {
            head = *poly;
        }
        dist = crossProduct(A, B, (*poly)->p);
        if (dist > maxDist) {
            maxDist = dist;
            maxPoint = (*poly)->p;
        }
        *poly = (*poly)->next;
    }
    return maxPoint;
}

void quickHull(Polygon* poly, Polygon* res) {
    Point* p = searchVertexByFunction(poly, minX)->p;
    Point* q = searchVertexByFunction(poly, maxX)->p;
    Polygon E1 = createPolygon();
    Polygon E2 = createPolygon();
    quickHullAux(poly, &E1, p, q);
    quickHullAux(poly, &E2, q, p);
    // On retire le point d'intersection entre E1 et E2
    extractVertexHead(&E2);
    // On concatène le résultat
    concatPolygon(&E1, &E2);
    concatPolygon(res, &E1);
}

void quickHullAux(Polygon* poly, Polygon* res, Point* p, Point* q) {
    Polygon onRight = createPolygon();
    rightPoints(poly, p, q, &onRight);
    if (!onRight) {
        Vertex* v1 = createVertex(); 
        Vertex* v2 = createVertex();
        fillVertex(v1, p);
        fillVertex(v2, q);
        addVertexTail(res, v1);
        addVertexTail(res, v2);
        return;
    }
    Point* r = furtherestPoint(&onRight, p, q);
    Polygon E1 = createPolygon();
    Polygon E2 = createPolygon();
    quickHullAux(&onRight, &E1, p, r);
    quickHullAux(&onRight, &E2, r, q);
    // On retire le point d'intersection entre E1 et E2
    extractVertexHead(&E2);
    // On concatène le résultat
    concatPolygon(&E1, &E2);
    concatPolygon(res, &E1);
}

/*int main(void) {
    Point* A = createPoint();
    Point* B = createPoint();
    fillPoint(A, 0, 0);
    fillPoint(B, 1, 1);
    printf("%d\n", dist(A, B));
    return 0;
}*/