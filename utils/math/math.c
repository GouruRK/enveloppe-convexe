/**
 * @file math.c
 * @author Quentin Laborde - Kies Rémy
 * @brief Fonctions de maths utiles au projet
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../utils.h"

/*
gcc -c ../list/list.c -Wall -std=c17
gcc math.c list.o -Wall -std=c17 -o math
*/

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
int crossProduct(Point* A, Point* B, Point* C) {
    return (B->x - A->x)*(C->y - A->y) - (C->x - A->x)*(B->y - A->y);
}

/**
 * @brief Permet de savoir si un triangle est direct
 * 
 * @param A 
 * @param B 
 * @param C 
 * @return int Renvoie `1` si direct, `0` sinon
 */
int isDirect(Point* A, Point* B, Point* C) {
    return crossProduct(A, B, C) >= 0;
}

/**
 * @brief Renvoie l'élément le plus petit des deux
 * 
 * @param x 
 * @param y 
 * @return int 
 */
int min(int x, int y) {
    return x < y ? x : y;
}