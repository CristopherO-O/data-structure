package src;
public class Edge{
    private final int node1;
    private final int node2;
    private final int weight;

    public Edge(int node1, int node2, int weight){
        this.node1 = node1;
        this.node2 = node2;
        this.weight = weight;
    }

    public int getNode1(){ return this.node1; }
    public int getNode2(){ return this.node2; }
    public int getWeight(){ return this.weight; }

}