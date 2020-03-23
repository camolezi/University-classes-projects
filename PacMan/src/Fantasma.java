
/*
Lucas Nascimento Camolezi 10276932
Matheus Victal Cerqueira 10276661
Felipe Barbosa de Oliveira 10276928
Afonso Henrique Piacentini Garcia 9795272
Grupo 15
 */

import java.util.Random;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

//Fantasmas do jogo
public class Fantasma extends Entidade{

    private String cor;


    private Image imagemUP;
    private Image imagemRIGHT;
    private Image imagemLEFT;
    private Image imagemDOWN;

    public Fantasma(int x , int y, String end ,String nome, String cor){
        super(x,y,end, nome);
        this.cor = cor;
        inicializarImagens();
    }


    //Direção para andar
    public enum Direction {
        UP,DOWN,LEFT,RIGHT
    }

    private static final int velocidade = 2;
    private Direction direction = Direction.RIGHT;

    //Todo frame verifica se pode andar, anda e atualiza a imagem caso possa. Se naõ puder andar sorteia uma nova direção para andar
    @Override
    public void runEveryFrame(){

        switch (direction){
            case UP:
                if(canGoUp){
                    setY(getY() - velocidade);
                    setImagem(imagemUP);
                }else{
                    escolherDirection();
                }
                break;
            case DOWN:
                if(canGoDown){
                    setY(getY() + velocidade);
                    setImagem(imagemDOWN);

                }else{
                    escolherDirection();
                }
                break;
            case LEFT:
                if(canGoLeft){
                    setX(getX() - velocidade);
                    setImagem(imagemLEFT);
                }else{
                    escolherDirection();
                }
                break;
            case RIGHT:
                if(canGoRight){
                    setX(getX() + velocidade);
                    setImagem(imagemRIGHT);
                }else{
                    escolherDirection();
                }
                break;
        }
    }

    //Sorteia uma direção para andar
    private void escolherDirection(){
        Random rand = new Random();

        int sorteio = rand.nextInt(4);

        switch (sorteio){
            case 0:
                direction = Direction.UP;
                break;
            case 1:
                direction = Direction.DOWN;
                break;
            case 2:
                direction = Direction.LEFT;
                break;
            case 3:
                direction = Direction.RIGHT;
                break;

                default:
                    direction = Direction.RIGHT;
                    break;
        }
    }


    //Inicializa as imagens dependendo da cor do fantasma
    private void inicializarImagens(){
        if(cor.equals("laranja")) {
            ImageIcon iconeUP = createImageIcon("clydeU.png");
            imagemUP = iconeUP.getImage();

            ImageIcon iconeRIGHT = createImageIcon("clydeR.png");
            imagemRIGHT = iconeRIGHT.getImage();

            ImageIcon iconeLEFT = createImageIcon("clydeL.png");
            imagemLEFT = iconeLEFT.getImage();

            ImageIcon iconeDOWN = createImageIcon("clydeD.png");
            imagemDOWN = iconeDOWN.getImage();

        } else if(cor.equals("azul")) {
            ImageIcon iconeUP = createImageIcon("inkyU.png");
            imagemUP = iconeUP.getImage();

            ImageIcon iconeRIGHT = createImageIcon("inkyR.png");
            imagemRIGHT = iconeRIGHT.getImage();

            ImageIcon iconeLEFT = createImageIcon("inkyL.png");
            imagemLEFT = iconeLEFT.getImage();

            ImageIcon iconeDOWN = createImageIcon("inkyD.png");
            imagemDOWN = iconeDOWN.getImage();

        } else if(cor.equals("rosa")) {
            ImageIcon iconeUP = createImageIcon("pinkyU.png");
            imagemUP = iconeUP.getImage();

            ImageIcon iconeRIGHT = createImageIcon("pinkyR.png");
            imagemRIGHT = iconeRIGHT.getImage();

            ImageIcon iconeLEFT = createImageIcon("pinkyL.png");
            imagemLEFT = iconeLEFT.getImage();

            ImageIcon iconeDOWN = createImageIcon("pinkyD.png");
            imagemDOWN = iconeDOWN.getImage();

        } else if(cor.equals("vermelho")) {
            ImageIcon iconeUP = createImageIcon("blinkyU.png");
            imagemUP = iconeUP.getImage();

            ImageIcon iconeRIGHT = createImageIcon("blinkyR.png");
            imagemRIGHT = iconeRIGHT.getImage();

            ImageIcon iconeLEFT = createImageIcon("blinkyL.png");
            imagemLEFT = iconeLEFT.getImage();

            ImageIcon iconeDOWN = createImageIcon("blinkyD.png");
            imagemDOWN = iconeDOWN.getImage();
        }
    }




}