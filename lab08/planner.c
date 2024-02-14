// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Place.h"
#include "PQ.h"

////////////////////////////////////////////////////////////////////////
// Your task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid1(Place cities[], int numCities, Place powerPlant,
              PowerLine powerLines[]) {

    // treat the powerplant like a city and add it to cities[]
    Graph newGraph = GraphNew(numCities + 1);
    cities[numCities] = powerPlant;
    // initialise the priority queue by inerting every edge in
    // pseudocode: unusedE = edges(g)
 
    for (int i = 0; i <= numCities; i++) { 
        for (int j = i; j <= numCities; j++) { 
            if(i != j) { 
                Edge newEdge;
                newEdge.v = i;
                newEdge.w = j; 
                newEdge.weight = sqrt(pow(cities[i].x - cities[j].x, 2) + pow(cities[i].y - cities[j].y, 2));
                GraphInsertEdge(newGraph, newEdge);
            }
        }
    }
    Graph newMSTGraph = GraphMST(newGraph);
    int numLines = 0;

    for (int i = 0; i <= numCities; i++) { 
        for (int j = i; j <= numCities; j++) { 
            if(GraphIsAdjacent(newMSTGraph, i, j) != 0) { 
                PowerLine newLine;
                newLine.p1 = cities[i];
                newLine.p2 = cities[j]; 
                powerLines[numLines] = newLine;
                numLines++;
           
            }
        }
    }
    GraphFree(newMSTGraph);
    GraphFree(newGraph);
    return numLines;
} 

////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(Place cities[], int numCities,
              Place powerPlants[], int numPowerPlants,
              PowerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
