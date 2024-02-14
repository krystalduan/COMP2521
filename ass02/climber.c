// Implementation of boulder climbing algorithms

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "climber.h"
#include "Wall.h"
#include "Queue.h"

// task 2 functions
static int weight(struct rock r, int Costs[NUM_COLOURS] );
static bool isValid(int **distance, struct rock curr, struct rock adjRock, int Costs[NUM_COLOURS]);

// functions used by both
static void initialiseRockMatrix(struct rock **matrix, int height, int weight, struct rock empty);
static void reverseArray(struct rock *originalPath, int numRocks);
void freeBoolMatrix(bool **matrix, int height);
void freeRockMatrix(struct rock **matrix, int height);
void freeIntMatrix(int **matrix, int height);

// task 1: find the shortest path from the bottom to the top of the wall
struct path findShortestPath(Wall w, int reach, Colour colour) {
    int height = WallHeight(w);
    int width = WallWidth(w);
    int wRocks = WallNumRocks(w);
    struct rock *rockPath = malloc(wRocks * sizeof(struct rock));
    struct rock emptyRock = {-1,-1, -1};

    // get all the rocks in the queue
    struct rock allRocks[wRocks];
    int allRocksSize = WallGetAllRocks(w, allRocks);
    struct rock allRocksColour[allRocksSize]; 
    int numRocks = 0;

    // create predecessor 2d array and visited 2d array
    struct rock **predecessor = malloc(sizeof(struct rock *) * height * width);
    if (predecessor == NULL) {
		fprintf(stderr, "couldn't allocate predecessor - task 1\n");
		exit(EXIT_FAILURE);
	}
    initialiseRockMatrix(predecessor, height, width, emptyRock);

    bool **visited =  malloc(sizeof(bool *) * height);
    if (visited == NULL) {
		fprintf(stderr, "couldn't allocate visited - task 1\n");
		exit(EXIT_FAILURE);
	}
    for (int a = 0; a < height; a++){
        visited[a] = malloc(sizeof(bool) * width);
        for(int b = 0; b < width; b++){
            visited[a][b] = false;
        }
    }
    
    // start climbing by finding a reachable rock from the bottom 
    // count is the number of rocks in the correct colour that are on the wall
    int count = 0;
    for (int i = 0; i < allRocksSize; i++) { 
        if (allRocks[i].colour == colour) { 
            allRocksColour[count] = allRocks[i];
            count++;
        }
    }
    
    // queue to make bfs traversal 
    Queue q = QueueNew(wRocks);

    for (int m = 0; m < count; m++) { 
        if (allRocksColour[m].row <= reach && allRocksColour[m].row > 0) { 
            QueueEnqueue(q, allRocksColour[m]);
        }
    }

    // start of bfs traversal
    while (QueueIsEmpty(q) != true) { 
        struct rock currRock = QueueDequeue(q);

        // mark as visited 
        visited[currRock.row][currRock.col] = true;

        // path found
        if ((height - currRock.row) <= reach) {
            // add rocks to path
            struct rock curr = currRock;
            while (!(predecessor[curr.row][curr.col].row == -1)) {
                rockPath[numRocks] = curr;
                numRocks++;
                curr = predecessor[curr.row][curr.col];
            }
            rockPath[numRocks] = curr;
            numRocks++;

            //  reverse the array
            reverseArray(rockPath, numRocks);
            freeBoolMatrix(visited, height);
            visited = NULL;
            freeRockMatrix(predecessor, height);
            predecessor = NULL;
            QueueFree(q);
            break;
        } 

        // traversal: get array of rocks in range
        struct rock queueInRange[count];
        int numRocksinRange = WallGetColouredRocksInRange(w, currRock.row, currRock.col, reach, colour, queueInRange);

        // add all rocks in range to the queue, add the queuecounter
        for (int k = 0; k < numRocksinRange; k++) {
            if (visited[queueInRange[k].row][queueInRange[k].col] == false) { 
                QueueEnqueue(q, queueInRange[k]);
                visited[queueInRange[k].row][queueInRange[k].col] = true;
                predecessor[queueInRange[k].row][queueInRange[k].col] = currRock;
            }
        }

    } 
    if (visited != NULL) {
        freeBoolMatrix(visited, height);
        freeRockMatrix(predecessor, height);
        QueueFree(q);
    }
    struct path p = {numRocks, rockPath};
    return p;
}

struct path findMinEnergyPath(Wall w, int reach, int Costs[NUM_COLOURS]) {
    int height = WallHeight(w);
    int width = WallWidth(w);
    int wRocks = WallNumRocks(w);

    // allocate memory for final path
    struct rock *rockPath = malloc(wRocks * sizeof(struct rock));
    
    struct rock emptyRock = {-1, -1, -1};

    // initialise 2d array to kep track of parent rock 
    struct rock **predecessor = malloc(sizeof(struct rock *) * height * width);
    if (predecessor == NULL) {
		fprintf(stderr, "couldn't allocate predecessor - task 2\n");
		exit(EXIT_FAILURE);
	}
    initialiseRockMatrix(predecessor, height, width, emptyRock);
    
    // initialise 2d array to keep track of distance in dijkstra
    int  **distance =  malloc(sizeof(int *) * height);
    if (distance == NULL) {
		fprintf(stderr, "couldn't allocate distance - task 2\n");
		exit(EXIT_FAILURE);
	}
    for (int a = 0; a < height; a++){
        distance[a] = malloc(sizeof(int) * width);
        for(int b = 0; b < width; b++){
            distance[a][b] = INT_MAX;
        }
    }
    

    // get all the rocks in the queue
    struct rock allRocks[wRocks];
    int allRocksSize = WallGetAllRocks(w, allRocks);
    int numRocks = 0;

    // initialise queue
    Queue q = QueueNew(wRocks);

    // start climbing by finding a reachable rock from the bottom 
    for (int m = 0; m < allRocksSize; m++) { 
        // Enqueue all the rocks to make vSet{}
        // pseudocode from lecture slide on dijkstra's
        QueueEnqueue(q, allRocks[m]);
        if (allRocks[m].row <= reach && allRocks[m].row > 0) { 
            distance[allRocks[m].row][allRocks[m].col] = Costs[allRocks[m].colour];
        }
    }

    // start of dijkstra's traversal
    while (QueueIsEmpty(q) != true) { 
        struct rock currRock = PriorityQueueDequeue(q, distance);
        int currRow = currRock.row;
        int currCol = currRock.col;
 
        // found the last rock
        if ((height - currRow) <= reach) {
            struct rock curr = currRock;
            while (!(predecessor[curr.row][curr.col].row == -1)) {
                rockPath[numRocks] = curr;
                curr = predecessor[curr.row][curr.col];
                numRocks++;
            }
            rockPath[numRocks] = curr;
            numRocks++;

            // reverse the array so it's the right way
            reverseArray(rockPath, numRocks);
            freeRockMatrix(predecessor, height);
            predecessor = NULL;
            freeIntMatrix(distance, height);
            distance = NULL;
            QueueFree(q);
            break;
        } 

        // keep traversing 
        struct rock adjacentRocks[wRocks];
        int numRocksAdjacent =  WallGetRocksInRange(w, currRock.row, currRock.col, reach, adjacentRocks);
        for (int v = 0; v < numRocksAdjacent; v++) { 
            // if the path is valid, change pred and distance
            int adjRow = adjacentRocks[v].row;
            int adjCol = adjacentRocks[v].col;
            if (isValid(distance, currRock, adjacentRocks[v], Costs) == true) { 
                predecessor[adjRow][adjCol] = currRock;
                distance[adjRow][adjCol] = distance[currRow][currCol] + weight(adjacentRocks[v], Costs);
            }
        }
    }

    // free everything if no path is found
    if (distance != NULL) {
        freeIntMatrix(distance, height);
        freeRockMatrix(predecessor, height);
        QueueFree(q);
    }

    struct path p = {numRocks, rockPath};
    return p;
}

struct path findMinTurnsPath(Wall w, int reach, int energyCosts[NUM_COLOURS],
                             int maxEnergy) {
    // TODO - Task 3
    struct path p = {0, NULL};
    return p;
}

// helper function to return the energy in task 2
static int weight(struct rock r, int Costs[NUM_COLOURS] ) {
    int weight = Costs[r.colour];
    return weight;
}

// helper function to reverse the array
static void reverseArray(struct rock *originalPath, int numRocks) { 
    struct rock realRockPath[numRocks];
    for (int i = 0; i < numRocks; i++) {
        realRockPath[numRocks - 1 - i] = originalPath[i];
    }
    for (int i = 0; i < numRocks; i++) {
        originalPath[i] = realRockPath[i];
    }
}

// function to initialiase a struct rock 2d array
static void initialiseRockMatrix(struct rock **matrix, int height, int width, 
    struct rock empty) { 
    for (int a = 0; a < height; a++){
        matrix[a] = malloc(sizeof(struct rock) * width);
        for(int b = 0; b < width; b++){
            matrix[a][b] = empty;
        }
    }
}
// function to check if the distance matrix needs to be updated
static bool isValid(int **distance, struct rock curr, struct rock adjRock, 
    int Costs[NUM_COLOURS]) {
    int row = curr.row;
    int col = curr.col;
    if (distance[row][col] == INT_MAX) {
        return false;
    }
    int adjR = adjRock.row;
    int adjC = adjRock.col;
    if (distance[row][col] + weight(adjRock, Costs) >= distance[adjR][adjC]) { 
        return false;
    }
    return true; 

}

// function that frees a boolean 2d array
void freeBoolMatrix(bool **matrix, int height) { 
    for (int a = 0; a < height; a++){
        free(matrix[a]);
    }
    free(matrix);
}

// function that frees a rock 2d array
void freeRockMatrix(struct rock **matrix, int height) {
    for (int a = 0; a < height; a++){
        free(matrix[a]);
    }
    free(matrix);
}

// function that frees an integer 2d array
void freeIntMatrix(int **matrix, int height) {
    for (int a = 0; a < height; a++){
        free(matrix[a]);
    }
    free(matrix);
}


