/**
 * @file errs.c
 * @author Quentin laborde - Rémy Kies
 * @brief Fichier avec les fonctions d'affichages des erreurs
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../utils.h"

/**
 * @brief Affiche une erreur si erreur d'allocation mémoire
 * 
 */
void errAlloc(void) {
    fprintf(stderr, "%sErreur%s : Erreur lors de l'allocation mémoire\n", 
            RED, RESET);
}
