#include "../utils.h"

/*
gcc testList.c list.o -std=c17 -Wall -o testList
*/

static const char red[] = "\x1b[31m";
static const char green[] = "\x1b[32m";
static const char cyan[] = "\x1b[36m";
static const char reset[] = "\x1b[0m";

void printSucess(void) {
    printf("%s%s%s%s", green, "succeed !", reset, "\n");
}

void printFail(void) {
    printf("%s%s%s%s", red, "failed !", reset, "\n");
}

// Teste la longueur d'une liste chainée

int testLength1(void) {
    // Teste la longueur d'une liste vide
    Polygon poly = createPolygon();
    printf("%s%s", cyan, "Test length 1 : ");
    if (length(poly) == 0) {
        printSucess();
        return 1;
    }
    printFail();
    return 0;
}

int testLength2(void) {
    // Teste la longueur d'une liste a un élément
    Polygon poly = createPolygon();
    Vertex* v = createVertex();
    addVertexHead(&poly, v);
    printf("%s%s", cyan, "Test length 2 : ");
    if (length(poly) == 1) {
        printSucess();
        freePolygon(&poly);
        return 1;
    }
    printFail();
    freePolygon(&poly);
    return 0;
}

#define NB_TEST_LENGTH 2

int testLength(void) {
    int (*testLengthFunctions[NB_TEST_LENGTH])(void) = {
        testLength1,
        testLength2
    };
    int acc = 0;
    for (int i = 0; i < NB_TEST_LENGTH; i++) {
        acc += testLengthFunctions[i]();
    }
    printf("%d sur %d tests de length réussis\n", acc, NB_TEST_LENGTH);
    return acc;
}

#define NB_GROUP_TEST 1

int main(void) {
    int (*groupTest[1])(void) = {
        testLength
    };
    int acc = 0;
    for (int i = 0; i < NB_GROUP_TEST; i++) {
        acc += groupTest[i]();
    } 
    printf("%d sur %d tests réussis\n", acc, NB_TEST_LENGTH);
    return 0;
}