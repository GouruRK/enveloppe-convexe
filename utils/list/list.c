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
 * @brief Ajoute un vertex a la fin de l'enveloppe
 * 
 * @param poly 
 * @param vertex 
 */
void addVertexTail(ConvexHull* convex, Vertex* vertex) {
    if (convex->curlen == convex->maxlen) {
        return;
    }
    convex->curlen++;
    Polygon* poly = &(convex->poly);
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
 * @brief Ajoute un vertex au début de l'enveloppe
 *  
 * @param poly 
 * @param vertex 
 */
void addVertexHead(ConvexHull* convex, Vertex* vertex) {
    // On remarque que ajouter un vertex au début ou a la fin de la liste
    // revient a faire les mêmes opérations, puis déplacer la tête
    // puisque la liste est circulaire
    addVertexTail(convex, vertex);
    convex->poly = vertex;
}

/**
 * @brief Permet d'ajouter un point dans l'enveloppe convexe en fonction
 *        de la fonction `addFunction`
 * 
 * @param convex 
 * @param p 
 * @param addFunction 
 */
void addPoint(ConvexHull* convex, Point* p,
              void (*addFunction)(ConvexHull*, Vertex*)) {
    Vertex* vertex = createVertex();
    fillVertex(vertex, p);
    addFunction(convex, vertex);
}

/**
 * @brief Permet d'ajouter un point dans l'enveloppe convexe en fonction
 *        de la fonction `addFunction` a partir de ses coordonnées
 * 
 * @param convex 
 * @param p 
 * @param addFunction 
 */
void addPointCoordinates(ConvexHull* convex, int x, int y,
                         void (*addFunction)(ConvexHull*, Vertex*)) {
    Point* p = createPoint();
    fillPoint(p, x, y);
    addPoint(convex, p, addFunction);
}

/**
 * @brief Enleve le dernier Vertex de l'enveloppe, et retourne l'adresse de
 *        l'élément retiré
 * 
 * @param poly 
 * @return Vertex* 
 */
Vertex* extractVertexTail(ConvexHull* convex) {
    if (!(convex->curlen)) {
        return NULL;
    }
    convex->curlen--;
    Polygon* poly = &(convex->poly);
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

Vertex* extractVertexHead(ConvexHull* convex) {
    // Comme pour l'insertion, on déplace la tête sur l'élément suivant
    // et ainsi, l'ancienne tête devient la queue
    convex->poly = convex->poly->next;
    // *poly = (*poly)->next;
    return extractVertexTail(convex);
}

/**
 * @brief Enleve de l'enveloppe un Vertex contenant le point `p` et 
 *        le retourne
 * 
 * @param poly 
 * @param p 
 * @return Vertex* 
 */
Vertex* extractPoint(ConvexHull* convex, Point* p) {
    if (!convex->curlen) {
        return NULL;
    }
    if (isPointEqual(convex->poly->p, p)) {
        return extractVertexHead(convex);
    }
    Vertex* head = convex->poly;
    convex->poly = convex->poly->next;
    while (head != convex->poly) {
        if (isPointEqual(convex->poly->p, p)) {
            return extractVertexHead(convex);
        }
        convex->poly = convex->poly->next;
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
Vertex* searchVertexByFunction(ConvexHull* convex,
                              int (*compare)(const Point*, const Point*))
                              {
    if (!(convex->curlen)) {
        return NULL;
    }
    Polygon* poly = &(convex->poly);
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
void concatConvex(ConvexHull* convex1, ConvexHull* convex2) {
    if (!(convex2->curlen)) {
        return;
    }
    if (!(convex1->curlen)) {
        convex1->poly = convex2->poly;
        convex1->curlen += convex2->curlen;
        convex1->maxlen += convex2->maxlen;
        convex2->poly = NULL;
        convex2->curlen = 0;
        return;
    }
    convex1->curlen += convex2->curlen;
    convex1->maxlen += convex2->maxlen;

    Polygon* poly1 = &(convex1->poly);
    Polygon* poly2 = &(convex2->poly);

    Vertex* temp = *poly1;
    
    (*poly1)->prev->next = *poly2;
    (*poly2)->prev->next = *poly1;
    (*poly1)->prev = (*poly2)->prev;
    (*poly2)->prev = temp->prev->next;
    convex2->poly = NULL;
    convex2->curlen = 0;
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
/**
 * @brief Libère le contenu d'une enveloppe convexe
 * 
 * @param poly 
 */
void freeConvex(ConvexHull* convex) {
    freePolygon(&(convex->poly));
    convex->curlen = 0;
}


/*int main(void) {
    ConvexHull convex1 = createConvex(10);
    ConvexHull convex2 = createConvex(10);

    addPointCoordinates(&convex1, 0, 0, addVertexHead);
    addPointCoordinates(&convex1, 1, 1, addVertexHead);
    addPointCoordinates(&convex1, 2, 2, addVertexHead);
    addPointCoordinates(&convex2, 3, 3, addVertexHead);
    addPointCoordinates(&convex2, 4, 4, addVertexHead);

    printf("Convex 1 : %d/%d\n", convex1.curlen, convex1.maxlen);
    printf("Convex 2 : %d/%d\n", convex2.curlen, convex2.maxlen);

    concatConvex(&convex1, &convex2);

    printf("Convex 1 : %d/%d\n", convex1.curlen, convex1.maxlen);
    printf("Convex 2 : %d/%d\n", convex2.curlen, convex2.maxlen);

    freeConvex(&convex1);
}*/