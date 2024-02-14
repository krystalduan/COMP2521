
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
static void dfs(Graph g, Vertex v, int *visited);
void depthFirstSearch(Graph g, int src) {
	// TODO
	// int count = 0;
	int *visited = (int *)malloc(GraphNumVertices(g) * sizeof(int));
	for (int a = 0; a < GraphNumVertices(g); a++){
		visited[a] = 0;
	}
	dfs(g, src, visited);
	free(visited);

}
static void dfs(Graph g, Vertex v, int *visited) { 
	visited[v] = 1;
	printf("%d ", v);
	int counter = 0;
	while (counter < GraphNumVertices(g)) { 
		if (visited[counter] != true && GraphIsAdjacent(g,v,counter) == true) { 
			dfs(g, counter, visited); 
		}
		counter++;
	}
	

}

