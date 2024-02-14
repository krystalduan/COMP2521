
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Graph.h"
#include "Queue.h"
#include <limits.h>

int shortestDistance(Graph g, int src, int dest) {
	//int *predecessor = malloc(GraphNumVertices(g) * sizeof(int *));
	bool *visited = malloc(GraphNumVertices(g) * sizeof(bool *));

	int *distance = malloc(GraphNumVertices(g)* sizeof(int *));
	for (int a = 0; a < GraphNumVertices(g); a++){ 
		distance[a] = INT_MAX;
		visited[a] = false;
	}

	Queue q = QueueNew();
	// for (int a = 0; a < GraphNumVertices(g); a++){ 
	// 	QueueEnqueue(q, a);
	// }
	QueueEnqueue(q, src);
	distance[src] = 0;
	while (QueueIsEmpty(q) != true) { 
		int v = QueueDequeue(q);
		visited[v]= true;
		for (int b = 0; b < GraphNumVertices(g); b++) {
			if (GraphIsAdjacent(g, v, b) == true && (distance[v] + 1) < distance[b] && visited[b] == false) { 
				//predecessor[b] = v;
				distance[b] = distance[v] + 1;
				QueueEnqueue(q, b);
			}
		}
			
	}
	//free(predecessor);
	free(visited);
	int dist = 0;
	if (distance[dest] == INT_MAX) { 
		dist = -1;
	} else { 
		dist = distance[dest];
	}
	free(distance);
	QueueFree(q);
	return dist;
}


