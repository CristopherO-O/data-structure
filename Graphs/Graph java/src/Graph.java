package src;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;


public class Graph {
    private int nodesNum;
    private int quantity;
    private ArrayList<Edge> edges;

    public Graph(int nodesNum) {
        this.nodesNum = nodesNum;
        this.quantity = 0;
        this.edges = new ArrayList<>();
    }
    
    
    // ----- getters -----
    public int getNodesNum(){ return this.nodesNum; }
    public int getQuantity(){ return this.quantity; }
    public List<Edge> getEdges() { return Collections.unmodifiableList(edges); }

    // ----- setters -----
    public void setNodesNum(int x){ this.nodesNum = x; }

    // ----- insere aresta no Grafo -----
    public void insertEdge(int node1, int node2, int weight){
        edges.add(new Edge(node1, node2, weight));
        this.quantity++;
    }

    // ----- imprime o grafo -----
    public void printGraph(){
        System.out.printf("The graph has %d nodes and %d edges:\n", nodesNum, quantity);
        for(Edge e : edges){
            System.out.printf("%d -> %d ; weight:%d\n", e.getNode1(), e.getNode2(), e.getWeight());
        }
    }

    // ----- Carrega grafo do arquivo de texto -----
    public static Graph loadGraphFromFile(String filename) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(filename));

        String line;
        ArrayList<Edge> list = new ArrayList<>();
        HashSet<Integer> uniqueNodes = new HashSet<>();

        while ((line = br.readLine()) != null) {
            String[] parts = line.split("\\s+");

            int u = Integer.parseInt(parts[0]);
            int v = Integer.parseInt(parts[1]);
            int w = Integer.parseInt(parts[2]);

            list.add(new Edge(u, v, w));
            uniqueNodes.add(u);
            uniqueNodes.add(v);
        }

        br.close();

        Graph g = new Graph(uniqueNodes.size());

        for (Edge e : list)
            g.insertEdge(e.getNode1(), e.getNode2(), e.getWeight());

        return g;
    }
   
    // ----- Dijkstra -----
    public void dijkstra(int origin) {

        int n = this.nodesNum;

        // nodeTable[i][0] = visitado
        // nodeTable[i][1] = distancia
        int[][] nodeTable = new int[n + 1][2];
        int[] parent = new int[n + 1];

        // inicializa
        for (int i = 1; i <= n; i++) {
            nodeTable[i][1] = Integer.MAX_VALUE;
            nodeTable[i][0] = 0;
            parent[i] = -1;
        }

        nodeTable[origin][1] = 0;
        parent[origin] = origin;

        for (int i = 1; i <= n; i++) {

            int u = -1;
            int mindist = Integer.MAX_VALUE;

            // escolhe nó não visitado com menor distância
            for (int j = 1; j <= n; j++) {
                if (nodeTable[j][0] == 0 && nodeTable[j][1] < mindist) {
                    mindist = nodeTable[j][1];
                    u = j;
                }
            }

            if (u == -1)
                break;

            nodeTable[u][0] = 1;

            // relaxamento
            for (Edge e : edges) {
                if (e.getNode1() == u) {

                    int v = e.getNode2();
                    int w = e.getWeight();

                    if (nodeTable[u][1] != Integer.MAX_VALUE &&
                        nodeTable[u][1] + w < nodeTable[v][1]) {

                        nodeTable[v][1] = nodeTable[u][1] + w;
                        parent[v] = u;
                    }
                }
            }
        }

        // imprime resultado
        System.out.println("Distance from node " + origin + ":");
        for (int i = 1; i <= n; i++) {

            if (nodeTable[i][1] == Integer.MAX_VALUE) {
                System.out.println("Node " + i + " = INF (sem caminho)");
            } else {

                System.out.print("Node " + i + " = " + nodeTable[i][1] + " | Caminho: ");

                //caminho invertido
                ArrayList<Integer> path = new ArrayList<>();
                int curr = i;

                while (curr != origin) {
                    if (curr == -1) break;
                    path.add(curr);
                    curr = parent[curr];
                }
                path.add(origin);

                // imprime na ordem correta
                for (int k = path.size() - 1; k >= 0; k--) {
                    System.out.print(path.get(k));
                    if (k > 0) System.out.print(" -> ");
                }
                System.out.println();
            }
        }
    }
    

    public PathResult dijkstraPath(int origin, int target) {

        int n = this.nodesNum;
        int[][] nodeTable = new int[n + 1][2];
        int[] parent = new int[n + 1];

        for (int i = 1; i <= n; i++) {
            nodeTable[i][1] = Integer.MAX_VALUE;
            nodeTable[i][0] = 0;
            parent[i] = -1;
        }

        nodeTable[origin][1] = 0;
        parent[origin] = origin;

        for (int i = 1; i <= n; i++) {
            int u = -1, mindist = Integer.MAX_VALUE;

            for (int j = 1; j <= n; j++) {
                if (nodeTable[j][0] == 0 && nodeTable[j][1] < mindist) {
                    mindist = nodeTable[j][1];
                    u = j;
                }
            }

            if (u == -1) break;
            nodeTable[u][0] = 1;

            for (Edge e : edges) {
                if (e.getNode1() == u) {
                    int v = e.getNode2();
                    int w = e.getWeight();
                    if (nodeTable[u][1] + w < nodeTable[v][1]) {
                        nodeTable[v][1] = nodeTable[u][1] + w;
                        parent[v] = u;
                    }
                }
            }
        }

        // reconstruir caminho até o target
        ArrayList<Integer> path = new ArrayList<>();
        if (nodeTable[target][1] == Integer.MAX_VALUE) {
            return new PathResult(null, -1);
        }

        int curr = target;
        while (curr != origin) {
            path.add(curr);
            curr = parent[curr];
        }
        path.add(origin);
        Collections.reverse(path);

        return new PathResult(path, nodeTable[target][1]);
    }

    
}


