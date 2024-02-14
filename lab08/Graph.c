// Implementation of the Undirected Weighted Graph ADT
// Uses an adjacency matrix

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "PQ.h"

// DO NOT modify this struct
struct graph {
    int nV;         // #vertices
    int nE;         // #edges
    double **edges; // adjacency matrix storing positive weights
                    // 0 if nodes not adjacent
};

static bool doHasCycle(Graph g, Vertex v, Vertex prev, bool *visited);
static int  validVertex(Graph g, Vertex v);

////////////////////////////////////////////////////////////////////////

Graph GraphNew(int nV) {
    assert(nV > 0);

    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nV = nV;
    g->nE = 0;

    g->edges = malloc(nV * sizeof(double *));
    if (g->edges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        g->edges[i] = calloc(nV, sizeof(double));
        if (g->edges[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    return g;
}

void GraphFree(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

////////////////////////////////////////////////////////////////////////

int GraphNumVertices(Graph g) {
    return g->nV;
}

bool GraphInsertEdge(Graph g, Edge e) {
    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));
    assert(e.v != e.w);
    assert(e.weight > 0.0);

    if (g->edges[e.v][e.w] == 0.0) {
        g->edges[e.v][e.w] = e.weight;
        g->edges[e.w][e.v] = e.weight;
        g->nE++;
        return true;
    } else {
        return false;
    }
}

bool GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));

    if (g->edges[v][w] != 0.0) {   // edge e in graph
        g->edges[v][w] = 0.0;
        g->edges[w][v] = 0.0;
        g->nE--;
        return true;
    } else {
        return false;
    }
}

double GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));
    
    return g->edges[v][w];
}

void GraphShow(Graph g) {
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (int v = 0; v < g->nV; v++) {
        for (int w = v + 1; w < g->nV; w++) {
            if (g->edges[v][w] != 0.0) {
                printf("Edge %d - %d: %lf\n", v, w, g->edges[v][w]);
            }
        }
    }
}

bool GraphHasCycle(Graph g) {
    bool *visited = calloc(g->nV, sizeof(bool));
    assert(visited != NULL); // lazy error checking
    
    for (int v = 0; v < g->nV; v++) {
        if (!visited[v] && doHasCycle(g, v, v, visited)) {
            free(visited);
            return true;
        }
    }

    free(visited);
    return false;
}

static bool doHasCycle(Graph g, Vertex v, Vertex prev, bool *visited) {
    visited[v] = true;
    for (int w = 0; w < g->nV; w++) {
        if (g->edges[v][w] != 0.0) {
            if (!visited[w]) {
                if (doHasCycle(g, w, v, visited)) {
                    return true;
                }
            } else if (w != prev) {
                return true;
            }
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////
// Your task

Graph GraphMST(Graph g) {
    Graph MST = GraphNew(GraphNumVertices(g));
    
    // initialise the priority queue by inerting every edge in
    // pseudocode: unusedE = edges(g)
    PQ unusedEdges = PQNew();
    for (int i = 0; i < g->nV; i++) { 
        for (int j = 0; j < g->nV; j++) { 
            if(g->edges[i][j] != 0) { 
                Edge newEdge;
                newEdge.v = i;
                newEdge.w = j; 
                newEdge.weight = g->edges[i][j];
                PQInsert(unusedEdges, newEdge);
            }
        }
    }
    int numVertices = g->nV;
    printf("%d\n", numVertices);
    for (int i = 0; i < numVertices*numVertices; i++) { 
        // step 1: find the lowest weighted edge
        Edge curr = PQExtract(unusedEdges);
        
        //step 2: insert it in the MST 
        if (curr.v != curr.w) { 
            GraphInsertEdge(MST, curr);
        }
        

        // step 3: check that it doesn't create a cycle
        if (GraphHasCycle(MST) == true) { 
            GraphRemoveEdge(MST, curr.v , curr.w);
        }

        // if edges = vertices - 1, then the MST is found
        // divide by 2
        if (MST->nE == (numVertices - 1)) { 
            PQFree(unusedEdges);
            return MST;
        }
        // MST Tree does not exist 
        if (PQIsEmpty(unusedEdges) == true && MST->nE != (MST->nV - 1)) { 
            PQFree(unusedEdges);
            GraphFree(MST);
            return NULL;
        }
    }
    PQFree(unusedEdges);
    GraphFree(MST);
    return NULL;
}

////////////////////////////////////////////////////////////////////////

static int validVertex(Graph g, Vertex v) {
    return v >= 0 && v < g->nV;
}

