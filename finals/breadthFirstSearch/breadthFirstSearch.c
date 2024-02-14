
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"
static void bfs(Graph g, int *visited, Queue q);
void breadthFirstSearch(Graph g, int src) {
	// TODO
	int *visited = (int *)malloc(GraphNumVertices(g) * sizeof(int));
	for (int a = 0; a < GraphNumVertices(g); a++){
		visited[a] = 0;
	}
	Queue q = QueueNew();
	QueueEnqueue(q, src);
	visited[src] = 1;
	while (QueueIsEmpty(q) == false) { 
		bfs(g, visited, q);
	}
	
	free(visited);
	QueueFree(q);
}

static void bfs(Graph g, int *visited, Queue q) { 
	Vertex v = QueueDequeue(q);

	printf("%d ", v);

	for (int a = 0; a < GraphNumVertices(g); a++) { 
		if (GraphIsAdjacent(g, v, a) == true && visited[a] != 1) { 
			QueueEnqueue(q, a);
			visited[a] = 1;

		}
	}

	
}
