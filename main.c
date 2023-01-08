/**
 * @file main.c
 * @author Quentin Laborde - Kies Rémy
 * @brief Fichier principal
 * @date 2023-01-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "main.h"

/*
clang -c ./utils/args/errs.c -Wall -std=c17
clang -c ./utils/list/list.c -Wall -std=c17
clang -c ./utils/math/math.c -Wall -std=c17
clang -c ./utils/graphic/draw.c -Wall -std=c17
clang -c ./utils/graphic/graphic.c -Wall -std=c17
clang -c ./utils/graphic/enveloppe.c -Wall -std=c17
clang -c ./utils/graphic/inception.c -Wall -std=c17
clang main.c errs.o list.o math.o draw.o graphic.o enveloppe.o inception.o -Wall -std=c17 -o main -lMLV -lm
*/

/**
 * @brief Permet de lancer la simulation
 * 
 * @param window 
 * @param initArray 
 * @param stop 
 */
void lunchGameFromArray(Window* window, int initArray[], int* stop) {
    srand(time(NULL));
    ConvexHull convex = createConvex(-1);

    MLV_create_window("Convex Hull", "Convex Hull", window->width, window->height);
    MLV_clear_window(MLV_COLOR_WHITE);
    printInfo(window, NULL, NULL);
    MLV_update_window();

    if (!initArray[0]) {
        if (!initArray[1]) {
            drawConvexClick(window, &convex, stop);
        } else {
            DrawInceptionClick(window, stop);
        }
    } else {
        if (initArray[1] == 0) {
            if (initArray[2]) {
                if (!initArray[5]) {
                    drawCircleRandomRising(window, &convex, initArray[4], initArray[3], 0, 1);
                } else {
                    drawCircleRandomRising(window, &convex, initArray[4], initArray[3], initArray[6], 1);
                }
            } else {
                if (!initArray[5]) {
                    drawCircleRandom(window, &convex, initArray[4], initArray[3], 0, 1);
                } else {
                    drawCircleRandom(window, &convex, initArray[4], initArray[3], initArray[6], 1);
                }
            }
        }
        if (initArray[1] == 1) {
            if (initArray[2]) {
                if (!initArray[5]) {
                    drawSquareRandomRising(window, &convex, initArray[4], initArray[3], 0, 1);
                } else {
                    drawSquareRandomRising(window, &convex, initArray[4], initArray[3], initArray[6], 1);
                }
            } else {
                if (!initArray[5]) {
                    drawSquareRandom(window, &convex, initArray[4], initArray[3], 0, 1);
                } else {
                    drawSquareRandom(window, &convex, initArray[4], initArray[3], initArray[6], 1);
                }
            }
        }
        if (initArray[1] == 2) {
            if (initArray[2]) {
                if (!initArray[5]) {
                    drawSquareRandomRising(window, &convex, initArray[4], initArray[3], 0, 0.7);
                } else {
                    drawSquareRandomRising(window, &convex, initArray[4], initArray[3], initArray[6], 0.7);
                }
            } else {
                if (!initArray[5]) {
                    drawSquareRandom(window, &convex, initArray[4], initArray[3], 0, 0.7);
                } else {
                    drawSquareRandom(window, &convex, initArray[4], initArray[3], initArray[6], 0.7);
                }
            }
        }
        if (initArray[1] == 3) {
            if (initArray[2]) {
                if (!initArray[5]) {
                    drawCircleRandomRising(window, &convex, initArray[4], initArray[3], 0, 0.7);
                } else {
                    drawCircleRandomRising(window, &convex, initArray[4], initArray[3], initArray[6], 0.7);
                }
            } else {
                if (!initArray[5]) {
                    drawCircleRandom(window, &convex, initArray[4], initArray[3], 0, 0.7);
                } else {
                    drawCircleRandom(window, &convex, initArray[4], initArray[3], initArray[6], 0.7);
                }
            }
        }
    }
    MLV_wait_seconds(2);
    MLV_free_window();
}

int main(void) {
    Window window;
    int initArray[6] = {};
    int winWidth = 1000, winHeight = 1000, stop = 0;
    MLV_execute_at_exit(exit_function, &stop);
    initWindowParam(&winWidth, &winHeight, initArray, &stop);
    initWindow(&window, winWidth, winHeight, 50);
    stop = 0;
    lunchGameFromArray(&window, initArray, &stop);
}
