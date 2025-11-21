/*
 * Autor: Cristopher Resende
 * Data: 20/11/2025
 * Descrição: Main
 */

package src;

public class Main {
    public static void main(String[] args) {
        try {
            Graph g = Graph.loadGraphFromFile("Graph.txt");

            Interface inter = new Interface(g);
            javax.swing.JFrame frame = new javax.swing.JFrame();

            // >>>>>Painel superior (para vários botões)<<<<<
            javax.swing.JPanel topPanel = new javax.swing.JPanel();
            topPanel.setLayout(new java.awt.FlowLayout());

            // Botao adicionar aresta
            javax.swing.JButton btnAdd = new javax.swing.JButton("Adicionar aresta");
            btnAdd.addActionListener(e -> inter.addArestaManual());
            topPanel.add(btnAdd);

            // Botao calcular dijkstra
            javax.swing.JButton btnDijk = new javax.swing.JButton("Calcular Dijkstra");
            btnDijk.addActionListener(e -> inter.calcularDijkstra());
            topPanel.add(btnDijk);

            // Botao de calcular PERT
            javax.swing.JButton btnPERT = new javax.swing.JButton("Calcular PERT");
            btnPERT.addActionListener(e -> inter.calcularPERT());
            topPanel.add(btnPERT);

            // Botao AGM
            javax.swing.JButton btnAGM = new javax.swing.JButton("AGM");
            btnAGM.addActionListener(e -> inter.calcularAGM());
            topPanel.add(btnAGM);

            // Adiciona o painel ao topo da janela
            frame.add(topPanel, java.awt.BorderLayout.NORTH);

            // >>>>>Painel inferior (para o botão Limpar Caminho)<<<<<
            javax.swing.JPanel bottomPanel = new javax.swing.JPanel();
            bottomPanel.setLayout(new java.awt.FlowLayout());

            // Botao Clear
            javax.swing.JButton btnClear = new javax.swing.JButton("Limpar Resultados");
            btnClear.addActionListener(e -> inter.clearPath());
            bottomPanel.add(btnClear);

            // Adiciona o em baixo da janela
            frame.add(bottomPanel, java.awt.BorderLayout.SOUTH);

            // janela  
            frame.add(inter);
            frame.setTitle("Melhor exercicios de grafos que você vai ver na vida");
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
