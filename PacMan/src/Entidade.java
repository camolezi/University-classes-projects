
/*
Lucas Nascimento Camolezi 10276932
Matheus Victal Cerqueira 10276661
Felipe Barbosa de Oliveira 10276928
Afonso Henrique Piacentini Garcia 9795272
Grupo 15
 */


import javax.swing.*;
import java.awt.*;


//Entidade é classe base para tudo que está presente na tela do jogo
public class Entidade {

    //x e y é posição
    //H e l são altura e largura da imagem
    private int x,y,h,l;
    private Image imagem;
    private String nome;

    //Variaveis para checagem de colisão
    public boolean canGoUp = true;
    public boolean canGoDown = true;
    public boolean canGoRight = true;
    public boolean canGoLeft = true;

    public void setImagem(Image imagem) {
        this.imagem = imagem;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getH() {
        return h;
    }

    public void setH(int h) {
        this.h = h;
    }

    public void setL(int l) {
        this.l = l;
    }

    public int getL() {
        return l;
    }

    public void setX(int x) {
        this.x = x;
    }

    public Image getImagem() {
        return imagem;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public String getNome() {
        return nome;
    }

    public Entidade(int x, int y, String endereco, String nome){
        inicializar(endereco);
        this.x = x;
        this.y = y;
        this.nome = nome;
    }


    private void inicializar(String end){
        ImageIcon icone = createImageIcon(end);
        imagem = icone.getImage();
    }

    //Função que é usada nas classes derivadas do filhos
    //è chamada todo frame pelo gameManager
    public void runEveryFrame(){}

    //Função para recuperar o endereço de uma imagem
    protected ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = getClass().getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Caminho não encontrado: " + path);
            return null;
        }
    }
}
