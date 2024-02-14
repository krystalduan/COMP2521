
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"
static bool dfs(Graph g, Vertex v, bool *visited, int *predecessor);
bool hasCycle(Graph g) {
	// TODO
	int nV = GraphNumVertices(g);
	int *predecessor = malloc(nV * sizeof(int));
	bool *visited = malloc(nV * sizeof(bool));
	for (int a = 0; a < nV; a++){ 
		predecessor[a] = -1;
		visited[a] = false;
	}
	//visited[0] = true;
	for (int b = 0; b < nV; b++) { 
		if (visited[b] == false) { 
			if (dfs(g, b, visited, predecessor) == true) { 
				return true;
			}
		}
	}

	
	// for (int b = 0; b < nV; b++) { 
	// 	if (GraphIsAdjacent(g, v, b) == true && visited[b] != true) { 
	// 		predecessor[b] = v;
	// 		if (hasCycle(b)) { 
	// 			cycleFound = true;
	// 		};
	// 	} else if (predecessor[v] != b ) { 
	// 		cycleFound = true;
	// 	}
	// }
	free(predecessor);
	free(visited);
	return false;
}

static bool dfs(Graph g, Vertex v, bool *visited, int *predecessor) { 
	visited[v] = true;
	int nV = GraphNumVertices(g);
	for (int b = 0; b < nV; b++) { 
		if (GraphIsAdjacent(g, v, b) == true && visited[b] != true) { 
			predecessor[b] = v;
			if (dfs(g, b, visited, predecessor) == true);
			return true;
		} else if (GraphIsAdjacent(g, v, b) == true && predecessor[b] != v  && visited[b] == true ) { 
			
			return true;
		}

	}
	return false;
}