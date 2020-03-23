
/*
Lucas Nascimento Camolezi 10276932
Matheus Victal Cerqueira 10276661
Felipe Barbosa de Oliveira 10276928
Afonso Henrique Piacentini Garcia 9795272
Grupo 15
 */

import javax.swing.*;


//Classe que é o Jframe do programa
public class Aplication extends JFrame {

    private Mapa mapa;

    public Aplication(Mapa mapa){
        this.mapa = mapa;
        inicializarJogo();
    }

    private void inicializarJogo(){

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500,500);

        setTitle("PacMan the POO Game");
        setLocationRelativeTo(null);

        add(mapa);

        //Faz o frame ficar do mesmo tamanho que o mapa
        pack();

        setResizable(false);
        setVisible(true);
    }

    public void reiniciarMapa(Mapa mapaNew){
        dispose();
    }
}
