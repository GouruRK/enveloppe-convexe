#include "../utils.h"

/*
gcc -c list.c -Wall -std=c17
*/

/**
 * @brief Permet de savoir si le point `A` est égal au point `B`
 *        coordonnées du point B, `0` sinon     
 * 
 * @param A 
 * @param B 
 * @return int Renvoie `1` si les coordonnées des points sont égales,
 *         `0` sinon
 */
int isPointEqual(const Point* A, const Point* B) {
    return A->x == B->x && A->y == B->y;
}

/**
 * @brief Permet d'afficher un point
 * 
 * @param p
 */
void printPoint(const Point* p) {
    printf("(%d; %d)", p->x, p->y);
}

/**
 * @brief Permet de savoir si l'abscisse du point `A` est inférieure 
 *        a l'abscisse du point `B`
 * 
 * @param A 
 * @param B 
 * @return int Renvoie `1` si l'abscisse du point `A` est inférieure a 
 *         l'abscisse du point B, `0` sinon. Si les deux abscisses sont
 *         égales, on regarde les ordonnées
 */
int minX(const Point* A, const Point* B) {
    return A->x == B->x ? A->y < B->y : A->x < B->x;
}

/**
 * @brief Permet de savoir si l'abscisse du point `A` est supérieure 
 *        a l'abscisse du point `B`
 * 
 * @param A 
 * @param B 
 * @return int Renvoie `1` si l'abscisse du point `A` est supérieure a 
 *         l'abscisse du point B, `0` sinon. Si les deux abscisses sont 
 *         égales, on regarde les ordonnées
 */
int maxX(const Point* A, const Point* B) {
    return A->x == B->x ? A->y > B->y : A->x > B->x;
}

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
 * @brief Crée un pointeur Vertex vide qui pointe sur lui même
 *        exit si erreur dans l'allocation
 * 
 * @return Vertex* 
 */
Vertex* createVertex(void) {
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    if (!v) {
        exit(1);
    }
    v->prev = v;
    v->next = v;
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
 * @brief Enleve le dernier Vertex du Polygon, et retourne l'adresse de
 *        l'élément retiré
 * 
 * @param poly 
 * @return Vertex* 
 */
Vertex* extractVertexTail(Polygon* poly) {
    if (!(*poly)) {
        return NULL;
    }
    Vertex* vertex = (*poly)->prev;
    if (vertex == *poly) {
        *poly = NULL;
    } else {
        vertex->prev->next = *poly;
        vertex->next = vertex;
        (*poly)->prev = vertex->prev;
        vertex->prev = vertex;
    }
    return vertex;
}

Vertex* extractVertexHead(Polygon* poly) {
    // Comme pour l'insertion, on déplace la tête sur le dernier élément
    // et ainsi, l'ancienne tête devient la queue
    *poly = (*poly)->next;
    return extractVertexTail(poly);
}

/**
 * @brief Enleve de la liste un Vertex contenant le point `p` et le retourne
 * 
 * @param poly 
 * @param p 
 * @return Vertex* 
 */
Vertex* extractPoint(Polygon* poly, Point* p) {
    if (!(*poly)) {
        return NULL;
    }
    Vertex* head = *poly;
    if (isPointEqual(head->p, p)) {
        return extractVertexHead(poly);
    }
    *poly = (*poly)->next;
    while (head != *poly) {
        if (isPointEqual((*poly)->p, p)) {
            return extractVertexHead(poly);
        }
    }
    return NULL;
}

/**
 * @brief Renvoie un élément satisfaisant les conditions d'une fonction
 *        Utile pour la recherche de minimum et de maximum
 * 
 * @param poly 
 * @param compare 
 * @return Vertex* 
 */
Vertex* searchVertexByFunction(Polygon* poly,
                              int (*compare)(const Point*, const Point*))
                              {
    if (!(*poly)) {
        return NULL;
    }
    Vertex* head = *poly;
    Vertex* elem = head;
    *poly = (*poly)->next;
    while (head != *poly) {
        if (compare((*poly)->p, elem->p)) {
            elem = *poly;
        }
        *poly = (*poly)->next;
    }
    return elem;
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
 * @brief Affiche une réprésentation de liste doublement chainnée
 * 
 * @param poly 
 * @param printPointFunction La fonction pour afficher les points
 */
void printPoly(Polygon poly, void (*printPointFunction)(const Point*)) {
    printf("<-> HEAD <-> ");
    Vertex* head = poly;
    printPointFunction(head->p);
    printf(" <-> ");
    poly = poly->next;
    while (head != poly) {
        printPointFunction(poly->p);
        printf(" <-> ");
        poly = poly->next;
    }
    printf("TAIL <->\n");
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


/*int main(void) {
    Polygon poly = createPolygon();
    Vertex* v1 = createVertex();
    Vertex* v2 = createVertex();
    Vertex* v3 = createVertex();
    Point* p1 = createPoint();    
    Point* p2 = createPoint();
    Point* p3 = createPoint();
    fillPoint(p1, 0, 0);
    fillPoint(p2, 1, 1);
    fillPoint(p3, 2, 2);
    fillVertex(v1, p1);
    fillVertex(v2, p2);
    fillVertex(v3, p3);
    addVertexHead(&poly, v1);
    addVertexHead(&poly, v2);
    addVertexHead(&poly, v3);
    printPoly(poly, printPoint);
    Vertex* v = searchVertexByFunction(&poly, maxX);
    printPoint(v->p);
    printf("\n");
    freePolygon(&poly);
    return 0;
}*/