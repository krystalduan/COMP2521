
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"
#include <limits.h>

int furthestReachable(Graph g, int src) {
	// TODO
	bool *visited = malloc(GraphNumVertices(g) * sizeof(bool));

	int *distance = malloc(GraphNumVertices(g)* sizeof(int));
	for (int a = 0; a < GraphNumVertices(g); a++){ 
		distance[a] = INT_MAX;
		visited[a] = false;
	}

	Queue q = QueueNew();
	QueueEnqueue(q, src);
	distance[src] = 0;
	while (QueueIsEmpty(q) != true) { 
		int v = QueueDequeue(q);
		visited[v]= true;
		for (int b = 0; b < GraphNumVertices(g); b++) {
			if (GraphIsAdjacent(g, v, b) == true && (distance[v] + 1) < distance[b] && visited[b] == false) { 
				distance[b] = distance[v] + 1;
				QueueEnqueue(q, b);
			}
		}
			
	}
	//free(predecessor);	free(visited);
	int furthestDist = 0;
	Vertex furthestVert = src;
	for (int a = 0; a < GraphNumVertices(g); a++){ 
		if (distance[a] != INT_MAX &&  distance[a] >= furthestDist) { 
			furthestDist = distance[a];
			furthestVert = a;
		}
		
	}
	
	free(distance);
	free(visited);
	QueueFree(q);
	return furthestVert;
}

