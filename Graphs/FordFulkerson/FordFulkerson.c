#include "Graph.h"

// ------- implementacao do Dijkistra --------
void Dijkstra(Graph* g, int origin){
    
    // -- inicia tabela --
    int n = g->NodesNum;
    int nodeTable[n + 1][2];

    for(int i = 1; i <=n; i++){
        nodeTable[i][1] = __INT_MAX__;
        nodeTable[i][0] = 0;
    }
    nodeTable[origin][1] = 0;

    // -- select no nao verificado com menor dist --
    for(int i = 1; i<=n; i++){
        int u = -1;
        int mindist = __INT_MAX__;
        for(int j = 1; j<=n; j++){
            if(!nodeTable[j][0] && nodeTable[j][1] < mindist){
                mindist = nodeTable[j][1];
                u = j;
            }
        }

        if(u==-1){
        break;
        }else{
            nodeTable[u][0] = 1;
        }

        // -- faz o reaxamento --
        for(int j = 0; j < g->quantity; j++){
            if(g->edges[j].node1 == u){
                if(nodeTable[u][1] != __INT_MAX__ && g->edges[j].weight + nodeTable[u][1] < nodeTable[g->edges[j].node2][1]){
                    nodeTable[g->edges[j].node2][1] = nodeTable[u][1] + g->edges[j].weight;
                }
            }
        }

    }

    // -- imprime o resultado --
    printf("Distance from the node %d:\n", origin);
    for (int i = 1; i <= n; i++) {
    if (nodeTable[i][1] == __INT_MAX__)
        printf("Node: %d = INF\n", i);
    else
        printf("Node: %d = %d\n", i, nodeTable[i][1]);
    }
}


// ------- main --------
int main() {
    Graph* g = LoadGraphFromFile("grafo.txt");
    int startNode;

    printGraph(g);
    printf("\n");
    printf("insert the origin node: ");
    scanf("%d", &startNode);
    printf("\n");
    Dijkstra(g,startNode);
    destroyGraph(g);

    return 0;
}