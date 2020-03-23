
/*
Lucas Nascimento Camolezi 10276932
Matheus Victal Cerqueira 10276661
Felipe Barbosa de Oliveira 10276928
Afonso Henrique Piacentini Garcia 9795272
Grupo 15
 */

//Obstaculo basico para o mapa
public class Obstaculo extends Entidade {
    public Obstaculo(int x , int y, String end ,String nome){
        super(x,y,end, nome);
        canGoDown = false;
        canGoUp = false;
        canGoRight = false;
        canGoLeft = false;
    }
}
