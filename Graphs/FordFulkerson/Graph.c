#include "Graph.h"

// ------- cria o Grafo --------
Graph* createGraph(int NodeNum, int maxEdge) {
    Graph* g = malloc(sizeof(Graph));
    g->NodesNum = NodeNum;
    g->MaxEdges = maxEdge;
    g->quantity = 0;
    g->edges = malloc(maxEdge * sizeof(Edge));
    return g;
}

// ------- libera a memoria --------
void destroyGraph(Graph* g) {
    free(g->edges);
    free(g);
}

// ------- insere aresta --------
void InsertEdge(Graph* g, int node1, int node2, int weight) {
    if (g->quantity >= g->MaxEdges) {
        g->MaxEdges *= 2;
        g->edges = realloc(g->edges, g->MaxEdges * sizeof(Edge));
    }
    g->edges[g->quantity].node1 = node1;
    g->edges[g->quantity].node2 = node2;
    g->edges[g->quantity].weight = weight;
    g->quantity++;
}

// ------- imprime Grafo --------
void printGraph(Graph* g) {
    printf("The graph has %d nodes and %d edges:\n", g->NodesNum, g->quantity);
    for (int i = 0; i < g->quantity; i++) {
        printf("%d -> %d ; weight:%d\n",
               g->edges[i].node1,
               g->edges[i].node2,
               g->edges[i].weight);
    }
}

// ------- carregar grafo de arquivo --------
Graph* LoadGraphFromFile(const char* filename) {
    FILE* f = fopen("Graph.txt", "r");
    if (!f) {
        printf("error opening file\n");
        return NULL;
    }

    int a, b, c;
    int maxNode = 0, edgeCount = 0;

    while (fscanf(f, "%d %d %d", &a, &b, &c) == 3) {
        if (a > maxNode) maxNode = a;
        if (b > maxNode) maxNode = b;
        edgeCount++;
    }

    Graph* g = createGraph(maxNode, edgeCount);

    rewind(f);
    while (fscanf(f, "%d %d %d", &a, &b, &c) == 3) {
        InsertEdge(g, a, b, c);
    }

    fclose(f);
    return g;
}
