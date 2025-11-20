package src;

public class Main {
    public static void main(String[] args) {
        try {
            Graph g = Graph.loadGraphFromFile("Graph.txt");

            Interface inter = new Interface(g);
            javax.swing.JFrame frame = new javax.swing.JFrame();

            g.printGraph();

            // >>>>>Painel superior (para vários botões)<<<<<
            javax.swing.JPanel topPanel = new javax.swing.JPanel();
            topPanel.setLayout(new java.awt.FlowLayout());

            // Botão adicionar aresta
            javax.swing.JButton btnAdd = new javax.swing.JButton("Adicionar aresta");
            btnAdd.addActionListener(e -> inter.addArestaManual());
            topPanel.add(btnAdd);

            // Botão calcular dijkstra
            javax.swing.JButton btnDijk = new javax.swing.JButton("Calcular Dijkstra");
            btnDijk.addActionListener(e -> inter.calcularDijkstra());
            topPanel.add(btnDijk);

            // Botão limpar caminho
            javax.swing.JButton btnClear = new javax.swing.JButton("Limpar caminho");
            btnClear.addActionListener(e -> {
                inter.clearPath();  // você vai criar esse método
            });
            topPanel.add(btnClear);

            // Adiciona o painel ao topo da janela
            frame.add(topPanel, java.awt.BorderLayout.NORTH);

            

            frame.add(inter);
            frame.setTitle("Grafo Visual");
            frame.pack();
            frame.setLocationRelativeTo(null);
            frame.setDefaultCloseOperation(javax.swing.JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);

            g.printGraph();
            new Thread(inter).start();

        } catch (Exception e) {
            System.out.println("Erro ao carregar o grafo:");
            e.printStackTrace();
        }
    }
}
