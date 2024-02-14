
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
static void dfs(Graph g, bool *visited, Vertex v);
int numReachable(Graph g, int src) {
	// TODO
	bool *visited = malloc (GraphNumVertices(g) * sizeof(bool *)); 
	for (int a = 0; a < GraphNumVertices(g); a++){ 
		//distance[a] = INT_MAX;
		visited[a] = false;
	}
	visited[src] = true;
	dfs(g, visited, src);
	int reachable = 0;
	for (int a = 0; a < GraphNumVertices(g); a++){ 
		//distance[a] = INT_MAX;
		if (visited[a] == true) {
			reachable++;
		}
	}
	// for (int b = 0; b < GraphNumVertices(g); b++) {
	// 		if (GraphIsAdjacent(g, v, b) == true && visited[b] == false) { 
	// 			//predecessor[b] = v;
	// 			visited[b] = true;
	// 			dfs(g, visited, b)
				
	// 		}
	// 	}
	free(visited);
	return reachable;
}

static void dfs(Graph g, bool *visited, Vertex v) {
	for (int b = 0; b < GraphNumVertices(g); b++) {
		if (GraphIsAdjacent(g, v, b) == true && visited[b] == false) { 
			//predecessor[b] = v;
			visited[b] = true;
			dfs(g, visited, b);
			
		}
	}
}

