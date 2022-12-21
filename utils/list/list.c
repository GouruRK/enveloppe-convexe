#include "../utils.h"

/**
 * @brief Crée un pointeur Point vide
 *        exit si erreur dans l'allocation
 * 
 * @return Point* 
 */
Point* createPoint(void) {
    Point* p = (Point*)malloc(sizeof(Point));
    if (!p) {
        exit(1);
    }
    return p;
}

/**
 * @brief Affecte les valeurs `x` `y` au Point `p`
 * 
 * @param p 
 * @param x 
 * @param y 
 */
void fillPoint(Point* p, int x, int y) {
    p->x = x;
    p->y = y;
}

/**
 * @brief Crée un pointeur Vertex vide
 *        exit si erreur dans l'allocation
 * 
 * @return Vertex* 
 */
Vertex* createVertex(void) {
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    if (!v) {
        exit(1);
    }
    return v;
}

/**
 * @brief Initialise les attributs de  `vertex`
 * 
 * @param vertex 
 * @param p 
 */
void fillVertex(Vertex* vertex, Point* p) {
    vertex->p = p;
    vertex->prev = vertex;
    vertex->next = vertex;
}

/**
 * @brief Crée un Polygon vide
 * 
 * @return Polygon 
 */
Polygon createPolygon(void) {
    return NULL;
}

/**
 * @brief Ajoute un vertex a la fin de la liste
 * 
 * @param poly 
 * @param vertex 
 */
void addVertexTail(Polygon* poly, Vertex* vertex) {
    if (!(*poly)) {
        *poly = vertex;
        return;
    }
    (*poly)->prev->next = vertex;
    vertex->next = *poly;
    vertex->prev = (*poly)->prev;
    (*poly)->prev = vertex;
}


/**
 * @brief Ajoute un vertex au début de la liste
 *  
 * 
 * @param poly 
 * @param vertex 
 */
void addVertexHead(Polygon* poly, Vertex* vertex) {
    // On remarque que ajouter un vertex au début ou a la fin de la liste
    // revient a faire les mêmes opérations, puis déplacer la tête
    // puisque la liste est circulaire
    addVertexTail(poly, vertex);
    *poly = vertex;
}

/**
 * @brief Effectue la concaténation de deux Polygon.
 * 
 * @param poly1 Polygon qui contiendra les vertex de `poly1` et de `poly2`
 * @param poly2 Une fois la concaténation effectuée, `poly2` sera vide
 */
void concatPolygon(Polygon* poly1, Polygon* poly2) {
    if (!(*poly2)) {
        return;
    }
    if (!(*poly1)) {
        *poly1 = *poly2;
        *poly2 = NULL;
        return;
    }
    Vertex* temp = *poly1;
    
    (*poly1)->prev->next = *poly2;
    (*poly2)->prev->next = *poly1;
    (*poly1)->prev = (*poly2)->prev;
    (*poly2)->prev = temp->prev->next;
    *poly2 = NULL;
}

/**
 * @brief Permet de connaître la longueur d'un Polygon
 * 
 * @param poly 
 * @return int 
 */
int length(Polygon poly) {
    if (!poly) {
        return 0;
    }
    Vertex* head = poly;
    poly = poly->next;
    int len = 1;
    while (head != poly) {
        len++;
        poly = poly->next;
    }
    return len;
}

/**
 * @brief Libère le contenu d'un Polygon
 * 
 * @param poly 
 */
void freePolygon(Polygon* poly) {
    if (!(*poly)) {
        return;
    }
    Vertex* temp;
    Vertex* head = *poly;
    *poly = (*poly)->next;
    while (head != *poly) {
        temp = (*poly)->next;
        free((*poly)->p);
        free(*poly);
        *poly = temp;
    }
    free(head->p);
    free(head);
}

int main(void) {
    Polygon poly1 = createPolygon();
    Polygon poly2 = createPolygon();
    Vertex* v1 = createVertex();
    Vertex* v2 = createVertex();
    Vertex* v3 = createVertex();
    Vertex* v4 = createVertex();
    Vertex* v5 = createVertex();
    Point* p1 = createPoint();    
    Point* p2 = createPoint();
    Point* p3 = createPoint();
    Point* p4 = createPoint();
    Point* p5 = createPoint();
    fillPoint(p1, 0, 0);
    fillPoint(p2, 1, 1);
    fillPoint(p3, 2, 2);
    fillPoint(p4, 3, 3);
    fillPoint(p3, 4, 4);
    fillVertex(v1, p1);
    fillVertex(v2, p2);
    fillVertex(v3, p3);
    fillVertex(v4, p4);
    fillVertex(v5, p5);
    addVertexHead(&poly1, v1);
    addVertexHead(&poly1, v2);
    addVertexHead(&poly1, v3);
    addVertexHead(&poly2, v4);
    addVertexHead(&poly2, v5);
    printf("poly1: %d\n", length(poly1));
    printf("poly2: %d\n", length(poly2));
    concatPolygon(&poly2, &poly1);
    printf("concat: %d\n", length(poly2));
    printf("res: %d\n", length(poly1));
    freePolygon(&poly2);
    return 0;
}