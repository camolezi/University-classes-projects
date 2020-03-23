
/*
Lucas Nascimento Camolezi 10276932
Matheus Victal Cerqueira 10276661
Felipe Barbosa de Oliveira 10276928
Afonso Henrique Piacentini Garcia 9795272
Grupo 15
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.font.ImageGraphicAttribute;

//Classe que representa o pacman
public class Pacman extends Entidade implements ActionListener {

    private Image frameFechado;

    private Image frameDown;
    private Image frameUp;
    private Image frameLeft;
    private Image frameRight;


    private Image frameSecundario;

    private Timer timerAnimation;

    //A animação do pacman fica trocando entre frameSecundario e frameFechado

    //Contatentes
    private static final int tempoAnimation = 200;
    private static final int velocidade = 2;

    private boolean animation = false;

    //Direção para andar
    public enum Direction {
        UP,DOWN,LEFT,RIGHT
    }
    private Direction direction = Direction.RIGHT;

    private Adpter inputTeclas;

    public Pacman(int x , int y, String end, String nome ){
        super(x,y,end, nome);
        inicializarImagens();
        timerAnimation = new Timer(tempoAnimation,this);
        timerAnimation.start();
        inputTeclas = new Adpter();
    }

    //Inicializa todas as imagens da animação do pacman
    private void inicializarImagens(){
        ImageIcon icone = createImageIcon("pacmanOpen.png");
        frameRight = icone.getImage();
        icone = createImageIcon("pacmanClosed.png");
        frameFechado = icone.getImage();
        icone = createImageIcon("PacDown.png");
        frameDown = icone.getImage();
        icone = createImageIcon("PacUp.png");
        frameUp = icone.getImage();
        icone = createImageIcon("PacLeft.png");
        frameLeft = icone.getImage();

        frameSecundario = frameRight;
    }

    //Todo frame ve se pode ir para a direção e anda naquela direção
    @Override
    public void runEveryFrame(){
        switch (direction){
            case UP:
                if(canGoUp){
                    setY(getY() - velocidade);
                }
                break;
            case DOWN:
                if(canGoDown){
                    setY(getY() + velocidade);
                }
                break;
            case LEFT:
                if(canGoLeft){
                    setX(getX() - velocidade);
                }
                break;
            case RIGHT:
                if(canGoRight){
                    setX(getX() + velocidade);
                }
                break;
        }
    }


    public Adpter getInputTeclas() {
        return inputTeclas;
    }

    // A cada ação do timer troca a imagem da animalão
    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource().equals(timerAnimation)){
            if(animation){
                setImagem(frameFechado);
            }else{
                setImagem(frameSecundario);
            }
            animation = !animation;
        }
    }

    //Todo evendo de tecla, muda a direção e a imagem secundaria da animação
    private class Adpter extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            if(e.getKeyCode() == KeyEvent.VK_RIGHT){
                direction = Direction.RIGHT;
                frameSecundario = frameRight;

            }
            if(e.getKeyCode() == KeyEvent.VK_DOWN){
                direction = Direction.DOWN;
                frameSecundario = frameDown;
            }
            if(e.getKeyCode() == KeyEvent.VK_LEFT){
                direction = Direction.LEFT;
                frameSecundario = frameLeft;
            }
            if(e.getKeyCode() == KeyEvent.VK_UP ){
                direction = Direction.UP;
                frameSecundario = frameUp;
            }
            setImagem(frameSecundario);
        }
    }

}