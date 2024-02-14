// Implementation of the Wall ADT

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Wall.h"

struct wall {
    // TODO
    int height;
    int width;
    int numRocks;
    struct rock *rocks;
}; 

static int compareRocks(const void *ptr1, const void *ptr2);
static int square (int a);
static int straightLineDistance(int row1, int row2, int col1, int col2);

/**
 * Creates a new blank wall with the given dimensions
 */
Wall WallNew(int height, int width) {
    // TODO

    assert(height > 0);
    assert(width > 0);

    Wall newWall = malloc(sizeof(struct wall));
    if (newWall == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    newWall->height = height;
    newWall->width = width;
    newWall->numRocks = 0;
    newWall->rocks = malloc(height*width*sizeof(struct rock));
    return newWall;
}

/**
 * Frees all memory allocated to the wall 
 */
void WallFree(Wall w) {
    //TODO
    // for (int i = 0; i < w->numRocks; i++) {
    //     free(w->rocks[i]);
    // }
    free(w->rocks);
    free(w);
}

/**
 * Returns the height of the wall
 */
int WallHeight(Wall w) {
    // TODO
    return w->height;
}

/**
 * Returns the width of the wall
 */
int WallWidth(Wall w) {
    // TODO
    return w->width;
}

/**
 * Adds a rock to the wall
 * If there is already a rock at the given coordinates, replaces it
 */
void WallAddRock(Wall w, struct rock rock) {
    // TODO
    assert(w != NULL);

    w->rocks[w->numRocks] = rock;
    w->numRocks++;
}

/**
 * Returns the number of rocks on the wall
 */
int WallNumRocks(Wall w) {
    // TODO
    return w->numRocks;
}

/**
 * Stores all rocks on the wall in the given `rocks` array and returns
 * the number of rocks stored. Assumes that the array is at least as
 * large as the number of rocks on the wall.
 */
int WallGetAllRocks(Wall w, struct rock rocks[]) {
    // TODO
    int i = 0;
    //struct rock currRock = w->rocks[i]; 
    while (i < w->numRocks) {
        rocks[i] = w->rocks[i];
        i++;
    }

    return w->numRocks;
}

/**
 * Stores all rocks that are within a distance of `dist` from the given
 * coordinates in the given `rocks` array and returns the number of rocks
 * stored. Assumes that the array is at least as large as the number of
 * rocks on the wall.
 */
int WallGetRocksInRange(Wall w, int row, int col, int dist,
                        struct rock rocks[])
{
    // TODO
    int i = 0;
    int count = 0;
    //struct rock currRock = w->rocks[i]; 
    while (i < w->numRocks) {
        if (straightLineDistance(w->rocks[i].row, row, w->rocks[i].col, col)<= dist
            && straightLineDistance(w->rocks[i].row, row, w->rocks[i].col, col) > 0){  // change this x@ - y@
            rocks[count] = w->rocks[i];
            count++;
        }
        
        i++;
    }

    return count;
}

static int square (int a) { 
    int squaredA = a*a;
    return squaredA;
}
static int straightLineDistance(int row1, int row2, int col1, int col2) { 
    double distance_double = sqrt(square(row1 - row2) + square(col1 - col2));
    int distance = ceil(distance_double);
    return distance;
}

/**
 * Stores all rocks with the colour `colour` that are within a distance
 * of `dist` from the given coordinates in the given `rocks` array and
 * returns the number of rocks stored. Assumes that the array is at
 * least as large as the number of rocks on the wall.
 */
int WallGetColouredRocksInRange(Wall w, int row, int col, int dist,
                                Colour colour, struct rock rocks[])
{
    // TODO

    int i = 0;
    int count = 0;
    //struct rock currRock = w->rocks[i]; 
    while (i < w->numRocks) {
        if (straightLineDistance(w->rocks[i].row, row, w->rocks[i].col, col) <= dist
            && straightLineDistance(w->rocks[i].row, row, w->rocks[i].col, col) > 0
            && colour == w->rocks[i].colour) {  // change this x@ - y@
            rocks[count] = w->rocks[i];
            count++;
        }
        
        i++;
    }

    return count;
}




////////////////////////////////////////////////////////////////////////

/**
 * Prints the wall out in a nice format
 * NOTE: DO NOT MODIFY THIS FUNCTION! This function will work once
 *       WallGetAllRocks and all the functions above it work.
 */
void WallPrint(Wall w) {
    int height = WallHeight(w);
    int width = WallWidth(w);
    int numRocks = WallNumRocks(w);
    struct rock *rocks = malloc(numRocks * sizeof(struct rock));
    WallGetAllRocks(w, rocks);
    qsort(rocks, numRocks, sizeof(struct rock), compareRocks);

    int i = 0;
    for (int y = height; y >= 0; y--) {
        for (int x = 0; x <= width; x++) {
            if ((y == 0 || y == height) && (x == 0 || x % 5 == 0)) {
                printf("+ ");
            } else if ((x == 0 || x == width) && (y == 0 || y % 5 == 0)) {
                printf("+ ");
            } else if (y == 0 || y == height) {
                printf("- ");
            } else if (x == 0 || x == width) {
                printf("| ");
            } else if (i < numRocks && y == rocks[i].row && x == rocks[i].col) {
                char *color;
                switch (rocks[i].colour) {
                    case GREEN: color = "\x1B[32m"; break;
                    case TEAL:  color = "\x1B[96m"; break;
                    case PINK:  color = "\x1B[95m"; break;
                    case RED:   color = "\x1B[91m"; break;
                    default:    color = "\x1B[0m";  break;
                }
                printf("%so %s", color, RESET);
                i++;
            } else {
                printf("\u00B7 ");
            }
        }
        printf("\n");
    }

    free(rocks);
}

static int compareRocks(const void *ptr1, const void *ptr2) {
    struct rock *r1 = (struct rock *)ptr1;
    struct rock *r2 = (struct rock *)ptr2;
    if (r1->row != r2->row) {
        return r2->row - r1->row;
    } else {
        return r1->col - r2->col;
    }
}

