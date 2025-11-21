/*
 * Autor: Cristopher Resende
 * Data: 20/11/2025 (altero isso aqui toda hora)
 * Descrição: essa classe cuida da interface grafica do programa
 */


package src;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.image.BufferStrategy;
import java.util.HashMap;
import java.util.List;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;


public class Interface extends Canvas implements Runnable{
    
    //dimensões da janela
    public static int WIDTH = 600, HEIGHT = 600;

    //arrastar com o mouse
    private int selectedNode = -1;
    private int offsetX = 0, offsetY = 0; 

    //relativo ao grafo
    private Graph graph;  
    private HashMap<Integer, NodePos> pos; 

    // caminho dijkstra
    private List<Integer> shortestPath = null;
    private int shortestCost = -1;
    
    // caminho PERT
    private PERT pert;
    private List<Edge> pertCriticalPath = null;
    private int pertDuration = -1;

    // AGM
    private Graph agmGraph = null;
    private boolean showAGM = false;



    // ----- Construtor -----
    public Interface(Graph graph){
        this.graph = graph;
        this.pos = generateNodePositions(graph.getNodesNum());
        this.pert = new PERT(graph);
        this.setPreferredSize(new Dimension(WIDTH, HEIGHT));


        this.addMouseListener(new MouseAdapter() {
        @Override
        public void mousePressed(MouseEvent e) {
            int mx = e.getX();
            int my = e.getY();

            // Verifica se clicou em algum nó
            for (int node = 1; node <= graph.getNodesNum(); node++) {
                NodePos n = pos.get(node);
                int dx = mx - n.x;
                int dy = my - n.y;
                if (dx * dx + dy * dy <= 100) { 
                    selectedNode = node;
                    offsetX = dx;
                    offsetY = dy;
                    break;
                }
            }
        }

        @Override
        public void mouseReleased(MouseEvent e) {
            selectedNode = -1;
        }
        });

        this.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                if (selectedNode != -1) {
                    NodePos n = pos.get(selectedNode);
                    n.x = e.getX() - offsetX;
                    n.y = e.getY() - offsetY;
                }
            }
        });

    }

    // ----- calcula posição dos nós -----
    private HashMap<Integer, NodePos> generateNodePositions(int total) {
        HashMap<Integer, NodePos> map = new HashMap<>();

        int centerX = WIDTH / 2;
        int centerY = HEIGHT / 2;
        int radius = 200;

        double angleStep = 2 * Math.PI / total;
        double angle = 0;

        for (int node = 1; node <= total; node++) {
            int x = (int)(centerX + radius * Math.cos(angle));
            int y = (int)(centerY + radius * Math.sin(angle));
            map.put(node, new NodePos(x, y));
            angle += angleStep;
        }

        return map;
    }

    //>>>>>----- BOTOES-----<<<<<

    // ----- botao AGM -----
    public void calcularAGM() {
        agmGraph = AGM.kruskalMST(graph);
        showAGM = true;
    }

    // ----- botao pert -----
    public void calcularPERT() {
        if (!graph.isDAG()) {
            javax.swing.JOptionPane.showMessageDialog(null, "Grafo não é acíclico!");
            return;
        }
        pert.calcularPERT();
        pertCriticalPath = pert.getCriticalPath();
        pertDuration = pert.getProjectDuration();
    }

    // ----- botao limpar caminho -----
    public void clearPath(){
        shortestPath = null;
        shortestCost = -1;
        pertCriticalPath = null;
        pertDuration = -1;
        showAGM = false;
    }

    // ----- botao dijkstra -----
    public void calcularDijkstra() {
        try {
            String s1 = javax.swing.JOptionPane.showInputDialog("Origem:");
            String s2 = javax.swing.JOptionPane.showInputDialog("Destino:");

            if (s1 == null || s2 == null) return;

            int origin = Integer.parseInt(s1);
            int target = Integer.parseInt(s2);

            PathResult result = graph.dijkstraPath(origin, target);

            shortestPath = result.path;
            shortestCost = result.totalCost;

            if (shortestPath == null) {
                javax.swing.JOptionPane.showMessageDialog(null, "Não existe caminho!");
            } else {
                System.out.println("Menor caminho: " + shortestPath + " | custo = " + shortestCost);
            }

        } catch (Exception e) {
            javax.swing.JOptionPane.showMessageDialog(null, "Entrada inválida!");
        }
    }

    // ----- logica do botao de adicionar aresta ------
    public void addArestaManual() {
        try {
            String s1 = javax.swing.JOptionPane.showInputDialog("Node 1:");
            String s2 = javax.swing.JOptionPane.showInputDialog("Node 2:");
            String s3 = javax.swing.JOptionPane.showInputDialog("Peso:");

            if (s1 == null || s2 == null || s3 == null) return;

            int n1 = Integer.parseInt(s1);
            int n2 = Integer.parseInt(s2);
            int w  = Integer.parseInt(s3);

            //recalcula caso adicionado um no novo
            int maior = Math.max(n1, n2);
            if (maior > graph.getNodesNum()) {
                graph.setNodesNum(maior);
                pos = generateNodePositions(maior);
            }

            graph.insertEdge(n1, n2, w);

            // Atualiza o desenho
            pos = generateNodePositions(graph.getNodesNum());

            System.out.println("Aresta adicionada: " + n1 + " -> " + n2 + " (peso " + w +")");

        } catch (Exception ex) {
            javax.swing.JOptionPane.showMessageDialog(null, "Entrada inválida!");
        }
    }

    // >>>>>>>>>>----- desenha o grafo -----<<<<<<<<<<
    private void drawGraph(Graphics g) {

        Graph drawGraph = showAGM ? agmGraph : graph; 

        if (drawGraph == null) return; // caso ainda não tenha calculado a AGM

        // Desenhar arestas
        g.setColor(Color.black);
        for (Edge e : drawGraph.getEdges()) {
            NodePos a = pos.get(e.getNode1());
            NodePos b = pos.get(e.getNode2());
            g.drawLine(a.x, a.y, b.x, b.y);

            int mx = (a.x + b.x) / 2;
            int my = (a.y + b.y) / 2;
            g.drawString(String.valueOf(e.getWeight()), mx, my);
        }


        if (!showAGM) {
            // Caminho crítico PERT
            if (pertCriticalPath != null) {
                g.setColor(Color.red);
                for (Edge e : pertCriticalPath) {
                    NodePos a = pos.get(e.getNode1());
                    NodePos b = pos.get(e.getNode2());
                    g.drawLine(a.x, a.y, b.x, b.y);
                }
                g.setColor(Color.black);
                g.drawString("Caminho critico em vermelho!", 20, HEIGHT - 35);
                g.drawString("Duração total do projeto: " + pertDuration, 20, HEIGHT - 20);
            }

            // Caminho Dijkstra
            if (shortestPath != null && shortestPath.size() > 1) {
                g.setColor(Color.red);
                for (int i = 0; i < shortestPath.size() - 1; i++) {
                    int a = shortestPath.get(i);
                    int b = shortestPath.get(i + 1);
                    NodePos p1 = pos.get(a);
                    NodePos p2 = pos.get(b);
                    g.drawLine(p1.x, p1.y, p2.x, p2.y);
                }
                g.setColor(Color.black);
                g.drawString("Custo total: " + shortestCost, 20, HEIGHT - 20);
            }

            if(pertCriticalPath == null && shortestPath == null){
                g.setColor(Color.black);
                g.drawString("numero de arestas: " + graph.getNodesNum(), 20, HEIGHT - 35);
                g.drawString("numero de nos: " + graph.getNodesNum(), 20, HEIGHT - 20);
            }
        } else {
            g.setColor(Color.black);
            g.drawString("Custo total: " + agmGraph.getTotalWeight(), 20, HEIGHT - 20);
        }

        // Desenha nos
        for (int node = 1; node <= graph.getNodesNum(); node++) {
            NodePos n = pos.get(node);
            g.setColor(Color.blue);
            g.fillOval(n.x - 10, n.y - 10, 20, 20);

            g.setColor(Color.white);
            g.drawString(String.valueOf(node), n.x - 4, n.y + 4);
        }
    }

    // renderiza
    public void render(){
        BufferStrategy bs = this.getBufferStrategy();
        if(bs == null){
            this.createBufferStrategy(3);
            return;
        }
        Graphics g = bs.getDrawGraphics();

        int w = getWidth();
        int h = getHeight();
        g.setColor(Color.white);
        g.fillRect(0, 0, w, h);

        // >>>>>adicionar oque sera rederizado:<<<<<
        drawGraph(g); 

        g.setColor(Color.blue);
        g.drawString("Arraste os nos para move-los", 20,  30);

        //>>>>>fim<<<<<

        bs.show();
    }

    // ----- thread -----
    public void run(){
        while(true){
            render();
            try{
                Thread.sleep(1000/20);
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        } 
        
    }

}

