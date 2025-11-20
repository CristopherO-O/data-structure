package src;
import java.util.List;

public class PathResult {
    public List<Integer> path;
    public int totalCost;

    public PathResult(List<Integer> path, int totalCost) {
        this.path = path;
        this.totalCost = totalCost;
    }
}