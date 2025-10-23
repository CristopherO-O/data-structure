#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>

// --------- STRUCTS ---------
typedef struct {
    int node1;
    int node2;
    int weight;
} Edge;

typedef struct {
    int NodesNum;
    int MaxEdges;
    int quantity;
    Edge* edges;
} Graph;

// --------- FUNCOES ---------
Graph* createGraph(int NodeNum, int maxEdge);
void destroyGraph(Graph* g);
void InsertEdge(Graph* g, int node1, int node2, int weight);
void printGraph(Graph* g);
Graph* LoadGraphFromFile(const char* filename);

#endif
