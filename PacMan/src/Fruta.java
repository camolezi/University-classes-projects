
/*
Lucas Nascimento Camolezi 10276932
Matheus Victal Cerqueira 10276661
Felipe Barbosa de Oliveira 10276928
Afonso Henrique Piacentini Garcia 9795272
Grupo 15
 */

//Fruta pegaveis no jogo
public class Fruta extends Entidade {

    private boolean foiDestruida = false;

    public Fruta(int x , int y, String end ,String nome){
        super(x,y,end, nome);
        canGoDown = false;
        canGoUp = false;
        canGoRight = false;
        canGoLeft = false;
    }

    public boolean isFoiDestruida() {
        return foiDestruida;
    }

    //Destroi o objeto tirando ele do jogo
    public void autoDestruir(){
        setX(-200);
        setY(-200);
        foiDestruida = true;
    }

}
