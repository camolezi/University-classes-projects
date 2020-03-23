
/*
Lucas Nascimento Camolezi 10276932
Matheus Victal Cerqueira 10276661
Felipe Barbosa de Oliveira 10276928
Afonso Henrique Piacentini Garcia 9795272
Grupo 15
 */



import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

//Classe que é inicializada pela main, cuida do inicalizamente e gerenciamento dos estados de jogo, além de contar o tempo dos frames
public class GameManager implements ActionListener{

    private Mapa mapaJogo;
    private Aplication aplication;

    //Atualiza o frame a cada FrameSpam segundos
    private Timer timer;
    private static final int FrameSpam = 15;

    public GameManager(){
        mapaJogo = new Mapa();
        aplication = new Aplication(mapaJogo);

        criarObstaculos();
        criarFrutas();
        criarFantasmas();

        timer = new Timer(FrameSpam , this);
        timer.start();
    }

    //Carrega o pacman e os fantasmas
    private void criarFantasmas(){


        Entidade pac = new Pacman(0,0,"pacmanClosed.png","PacMan");

        mapaJogo.addEntidade(pac);
        mapaJogo.addKeyListener(((Pacman) pac).getInputTeclas());


        Entidade fantasma1 = new Fantasma(100,100, "clydeU.png","Fantasma","laranja");
        Entidade fantasma2 = new Fantasma(150,150, "blinkyU.png","Fantasma", "vermelho");
        Entidade fantasma3 = new Fantasma(450,450, "inkyU.png","Fantasma", "azul");
        Entidade fantasma4 = new Fantasma(200,300, "pinkyU.png","Fantasma", "rosa");


        mapaJogo.addEntidade(fantasma1);
        mapaJogo.addEntidade(fantasma2);
        mapaJogo.addEntidade(fantasma3);
        mapaJogo.addEntidade(fantasma4);
    }

    //Carrega as imagens das frutas
    private void criarFrutas(){
        Entidade banana = new Fruta(10,465,"bananap.jpg","Fruta");
        Entidade cereja = new Fruta(465,10,"cerejap.jpg","Fruta");
        Entidade pera = new Fruta(465,465,"perap.jpg","Fruta");
        Entidade abacaxi = new Fruta(275,165,"abacaxip.jpg","Fruta");
        Entidade morango = new Fruta(275,350,"morangop.jpg","Fruta");


        mapaJogo.addEntidade(abacaxi);
        mapaJogo.addEntidade(morango);
        mapaJogo.addEntidade(pera);
        mapaJogo.addEntidade(cereja);
        mapaJogo.addEntidade(banana);

    }

    //Carrega as imagens das paredes
    private void criarObstaculos(){

        Entidade paredeVerticalEsquerda = new Obstaculo(-23,-23,"ParedeVertical.png","Parede");
        Entidade paredeVerticalDireita = new Obstaculo(498,-23,"ParedeVertical.png","Parede");
        Entidade paredeHorizontalCima = new Obstaculo(23,-23,"ParedeHorizontal.png","Parede");
        Entidade paredeHorizontalBaixo = new Obstaculo(23,498,"ParedeHorizontal.png","Parede");
        Entidade quadrado1 = new Obstaculo(50,50,"quadrado.png","Parede");
        Entidade quadrado2 = new Obstaculo(175,50,"quadrado.png","Parede");
        Entidade quadrado3 = new Obstaculo(375,50,"quadrado.png","Parede");
        Entidade quadrado4 = new Obstaculo(375,375,"quadrado.png","Parede");
        Entidade quadrado5 = new Obstaculo(50,375,"quadrado.png","Parede");
        Entidade retB = new Obstaculo(175,450,"RetanguloB.png","Parede");
        Entidade retC = new Obstaculo(225,200,"RetanguloC.png","Parede");
        Entidade retE = new Obstaculo(0,175,"RetanguloE.png","Parede");
        Entidade retD = new Obstaculo(400,175,"RetanguloD.png","Parede");

        mapaJogo.addEntidade(retD);
        mapaJogo.addEntidade(retE);
        mapaJogo.addEntidade(retC);
        mapaJogo.addEntidade(retB);
        mapaJogo.addEntidade(quadrado5);
        mapaJogo.addEntidade(quadrado4);
        mapaJogo.addEntidade(quadrado3);
        mapaJogo.addEntidade(quadrado2);
        mapaJogo.addEntidade(quadrado1);
        mapaJogo.addEntidade(paredeVerticalEsquerda);
        mapaJogo.addEntidade(paredeVerticalDireita);
        mapaJogo.addEntidade(paredeHorizontalBaixo);
        mapaJogo.addEntidade(paredeHorizontalCima);

    }

    //Atualiza o frame a cada evento do timer
    @Override
    public void actionPerformed(ActionEvent e) {
        mapaJogo.atualizarFrame();
        testarFimDeJogo();
    }

    //Ve se é o fim do jogo
    private void testarFimDeJogo(){
        boolean fimDeJogo = mapaJogo.checarCondicaoJogo();
        if(fimDeJogo){
            reiniciar();
        }
    }

    //Reinicia o jogo
    private void reiniciar(){
        aplication.reiniciarMapa(mapaJogo);
        mapaJogo = new Mapa();
        aplication = new Aplication(mapaJogo);

        criarObstaculos();
        criarFrutas();
        criarFantasmas();
    }

}
