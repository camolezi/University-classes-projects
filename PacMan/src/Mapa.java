
/*
Lucas Nascimento Camolezi 10276932
Matheus Victal Cerqueira 10276661
Felipe Barbosa de Oliveira 10276928
Afonso Henrique Piacentini Garcia 9795272
Grupo 15
 */


import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

//Mapa é a classe que é base do jogo, ele contem todas as entidades do jogo, além de conter toda a parte gráfica e colisão
public class Mapa extends JPanel{

    //Campos privados
    private Image backGroundImage;
    private ArrayList<Entidade> entidades;

    private boolean fimJogo = false;


    public Mapa(){

        setFocusable(true);
        //Inicializa o vetor de entidades
        entidades = new ArrayList<Entidade>();

        //Inicializa a imagem de fundo
        inicializarMapa();
    }

    //Adiciona uma entidade para a lista de entidades
    public void addEntidade(Entidade ent){
        entidades.add(ent);
        ent.setH(ent.getImagem().getHeight(this));
        ent.setL(ent.getImagem().getWidth(this));
    }


    private void inicializarMapa(){
        //Carrega a imagem
        ImageIcon imagem = createImageIcon("mapa.png");
        backGroundImage = imagem.getImage();
        setPreferredSize(new Dimension(backGroundImage.getWidth(this),backGroundImage.getHeight(this)));
    }


    //Essa função é chamada pelo repaint()(que é chamado todo frame) e imprime na tela todos os objetos novamente (atualiza a posição)
    private void atualizarImagem(Graphics g){
        g.drawImage(backGroundImage, 0, 0, null);
        for(Entidade ent : entidades){
            g.drawImage(ent.getImagem(),ent.getX(),ent.getY(),null);
        }
    }

    //Chama a função runEveryFrame de cada entidade
    private void atualizarEntidades(){
        for(Entidade ent : entidades){
            ent.runEveryFrame();
        }
    }

    //Função base que é chamada todo frame pelo gameManejar
    public void atualizarFrame(){
        atualizarEntidades();
        atualizarColisao();
        repaint();
    }

    //Função para carregar a imagem na tela
    @Override
    public void paintComponent(Graphics g) {
        atualizarImagem(g);
        Toolkit.getDefaultToolkit().sync();
    }

    //Consegue o endereço da imagem e solta um erro caso não consiga
    private ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = getClass().getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Caminho não encontrado: " + path);
            return null;
        }
    }


    //Função chaamda todo frame para testar as colisões
    public void atualizarColisao(){
        //Teste de colisão para o pacman

        for(Entidade ent : entidades){
            //Calcula a colisão para todas as entidades que se movem
            if(ent.getNome() == "PacMan" || ent.getNome()== "Fantasma"){
                calcularColisao(ent);
            }
        }
    }

    int erro = 5;

    private int calcularColisao(Entidade entidade){

        entidade.canGoRight = true;
        entidade.canGoLeft = true;
        entidade.canGoDown = true;
        entidade.canGoUp = true;

        //Calcula as equações da reta
        int bordaSupAlvo = entidade.getY();
        int bordaInfAlvo = entidade.getY() + entidade.getH();
        int bordaDirAlvo = entidade.getX() + entidade.getL();
        int bordaEsqAlvo = entidade.getX();

        for(Entidade ent : entidades){

            //Algumas combinações precisam ser ignoradas
            if(entidade.getNome() == "Fantasma"){
                if(ent.getNome() == "Fantasma" || ent.getNome() == "Fruta"){
                    continue;
                }
            }

            boolean colidiu = false;
            //Calcula as bordas da entidade;
            int bordaSup = ent.getY();
            int bordaInf = ent.getY() + ent.getH();
            int bordaDir = ent.getX() + ent.getL();
            int bordaEsq = ent.getX();

            //Faz os calculos para ver se ocorreu alguma colisão, e atualiza a variavel se a entidade pode ou nao se mover
            if(!ent.equals(entidade)){
                if(bordaInfAlvo >= bordaSup && bordaSupAlvo < bordaInf){
                    if(Math.abs(bordaEsq- bordaDirAlvo) <= erro){
                        colidiu = true;
                        entidade.canGoRight = false;
                    }else if(Math.abs(bordaDir - bordaEsqAlvo) <= erro){
                        colidiu = true;
                        entidade.canGoLeft = false;
                    }
                }
                //Faz os calculos para ver se ocorreu alguma colisão, e atualiza a variavel se a entidade pode ou nao se mover
                if(bordaEsqAlvo <= bordaDir && bordaDirAlvo >= bordaEsq ){
                    if(Math.abs(bordaInfAlvo - bordaSup) <= erro){
                        colidiu = true;
                        entidade.canGoDown = false;
                    }else if(Math.abs(bordaSupAlvo - bordaInf) <= erro ){
                        colidiu = true;
                        entidade.canGoUp = false;
                    }
                }
            }

            //Se ocorreu uma colisão é necessário verificar se é uma colisão especial, como o fim do jogo, ou a coleta de uma fruta
            if(colidiu){
                if(ent.getNome() == "Fruta" && entidade.getNome() == "PacMan"){
                    Fruta frutinha = (Fruta) ent;
                    frutinha.autoDestruir();
                }else if(ent.getNome() == "Fantasma" && entidade.getNome() == "PacMan"){
                    fimJogo = true;
                }
            }

        }
        return 0;
    }

    //Checa se é o fim do jogo
    public boolean checarCondicaoJogo(){
        for(Entidade ent : entidades){
        }
        return fimJogo;

    }



}
