import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.event.ActionListener;
import java.util.Random;
import java.awt.event.ActionEvent;
import java.awt.Choice;
import javax.swing.JLabel;
import java.awt.Button;
import java.awt.Color;
import javax.swing.border.LineBorder;

import org.jfree.ui.RefineryUtilities;
import org.jfugue.player.Player;
import javax.swing.UIManager;
import javax.swing.WindowConstants;

import Plot.Graphs;


public class Interface extends JFrame {
	//static final int numNot = 32;
	static final int numInd = 200;
	static final int numGen = 50;
	
	// Define das frequencias de cada nota
	static final int freqC = 261;
	static final int freqCs = 277;
	static final int freqD = 293;
	static final int freqDs = 311;
	static final int freqE = 329;
	static final int freqF = 349;
	static final int freqFs = 369;
	static final int freqG = 391;
	static final int freqGs = 415;
	static final int freqA = 440;
	static final int freqAs = 466;
	static final int freqB = 493;
	
	// Perfect
	static final int unisonCent = 0;
	static final int perfFourthCent = 500;
	static final int perfFifthCent = 700;
	
	// Imperfect
	static final int majThirdCent = 400;
	static final int minSixthCent = 800;
	static final int minThirdCent = 300;
	static final int majSixthCent = 900;
	
	String song = "", lixo = "";
	String song1 = "", song2 = "", song3 = "", song4 = "", song5 = "";
	String key, melody, melody2a, melody2b, melodybateria, melodynua, melodynua2, melody3;
	int list = 0, items = 0;
	
	double[] PontosGraficos = new double[numGen] ;
	
	String randomKey() {
		Random randomGenerator = new Random();
	    
	    int randomInt = randomGenerator.nextInt(24);
	    
	    switch(randomInt) {
	    	case 0: 
	    		return "Amaj";
	    	case 1: 
	    		return "Amin"; 
	    	case 2: 
	    		return "A#maj"; 
	    	case 3: 
	    		return "A#min"; 
	    	case 4: 
	    		return "Bmaj"; 
	    	case 5: 
	    		return "Bmin";
	    	case 6: 
	    		return "Cmaj"; 
	    	case 7: 
	    		return "Cmin";
	    	case 8: 
	    		return "C#maj";
	    	case 9: 
	    		return "C#min";
	    	case 10: 
	    		return "Dmaj"; 
	    	case 11: 
	    		return "Dmin";
	    	case 12: 
	    		return "D#maj";
	    	case 13: 
	    		return "D#min"; 
	    	case 14: 
	    		return "Emaj"; 
	    	case 15: 
	    		return "Emin"; 
	    	case 16: 
	    		return "Fmaj"; 
	    	case 17: 
	    		return "Fmin";
	    	case 18: 
	    		return "F#maj"; 
	    	case 19: 
	    		return "F#min";
	    	case 20: 
	    		return "Gmaj";
	    	case 21: 
	    		return "Gmin";
	    	case 22: 
	    		return "G#maj"; 
	    	case 23: 
	    		return "G#min";
	    	default: 
	    		return "Cmaj";
	    }
	}
	
	String chooseNote() {
		
	    Random randomGenerator = new Random();
	    
	    int randomInt = randomGenerator.nextInt(12);

	    switch(randomInt) {
	    	case 0: 
	    		return "C "; // 261.626
	    	case 1: 
	    		return "C# "; // 277.183
	    	case 2: 
	    		return "D "; // 293.665
	    	case 3: 
	    		return "D# "; // 311.127
	    	case 4: 
	    		return "E "; // 329.628
	    	case 5: 
	    		return "F "; // 349.228
	    	case 6: 
	    		return "F# "; // 369.994
	    	case 7: 
	    		return "G "; // 391.995
	    	case 8: 
	    		return "G# "; // 415.305
	    	case 9: 
	    		return "A "; // 440.000
	    	case 10: 
	    		return "A# "; // 466.164
	    	case 11: 
	    		return "B "; // 493.883
	    	default: 
	    		return "C ";
	    }
	}
	
	int freqNote(String not) {
	    switch(not) {
		case "C ": 
			return freqC;
		case "C# ": 
			return freqCs;
		case "D ": 
			return freqD;
		case "D# ": 
			return freqDs;
		case "E ": 
			return freqE;
		case "F ": 
			return freqF;
		case "F# ": 
			return freqFs;
		case "G ": 
			return freqG;
		case "G# ": 
			return freqGs;
		case "A ": 
			return freqA;
		case "A# ": 
			return freqAs; 
		case "B ": 
			return freqB; 
		default: 
			return freqC; 
	    }
	}
	
	int fitnessAux(String not1, String not2){
		double freq1, freq2;
		double ratio, result;
		
		freq1 = freqNote(not1);
		freq2 = freqNote(not2);

		ratio = freq1/freq2;
		
		result = Math.abs((Math.log(ratio)/ Math.log(2))*1200);
		
		if(result >= 495 && result <= 505) { //perfect
			return 4;
		} else if (result >= 695 && result <= 705) { //perfect
			return 4;
		} else if (result >= 395 && result <= 405) {
			return 3;
		} else if (result >= 795 && result <= 805) {
			return 3;
		} else if (result >= 295 && result <= 305) {
			return 3;
		} else if (result >= 895 && result <= 905) {
			return 3;
		} else if (result <= 5) {
			return 3;
		} 
		return -3;
	}
	
	double returnFitness(String[] ind, int numNot){
		double fitness;		
		fitness = 0;
		for(int x = 1; x < numNot ; x++) {
			fitness += fitnessAux(ind[x-1],ind[x]);
		}
			
		return fitness;
	}

	int torneioDeDois(double[] fitness) {
	    Random randomGenerator = new Random();
	    int ind2 = randomGenerator.nextInt(numInd);
	    int ind1 = randomGenerator.nextInt(numInd);
	    
	    if(fitness[ind1] > fitness[ind2]) {
	    	return ind1;
	    } else {
	    	return ind2;
	    }	   	    
	}
	
	
	String[] crossingOver(String[] pai, String[] mae, int numNot) {
		
		Random randomGenerator = new Random();
		
		int ponto = randomGenerator.nextInt(numNot);
		
	    String[] filho = new String[numNot];
	    
		for(int x = 0; x < numNot; x++) {
			
		   if(x < ponto) {
			   filho[x] = pai[x];
			
		   }else {
			   
			   filho[x] = mae[x];
		   }
			
		    
		}
	    
	    
		return filho;
		
	}
	
	String[] mutation(String[] ind, int numNot) {
		
        Random randomGenerator = new Random();
			    
	    for(int x = 0; x < numNot;x++ ) {
	    	
			int rand  = randomGenerator.nextInt(100);

	    	if(rand < 2){
	    		
	    		switch(ind[x]){
	    		
	    		case "C ":
	    			if(rand == 1){
	    				ind[x] = "C# ";
	    			} else {
	    				ind[x] = "B ";			
	    			}
	    			
	    			break;
	    			
	    		case "C# ": 
	    			if(rand == 1){
	    				ind[x] = "D ";
	    			} else {
	    				ind[x] = "C ";			
	    			}
	    			
	    			break;
	    			
	    		case "D ": 
	    			if(rand == 1){
	    				ind[x] = "D# ";
	    			} else {
	    				ind[x] = "C# ";			
	    			}
	    			
	    			break;
	    			
	    		case "D# ": 
	    			if(rand == 1){
	    				ind[x] = "E ";
	    			} else {
	    				ind[x] = "D ";			
	    			}
	    			
	    			break;
	    			
	    		case "E ": 
	    			if(rand == 1){
	    				ind[x] = "F ";
	    			}else{
	    				ind[x] = "D# ";			
	    			}
	    			
	    			break;
	    			
	    		case "F ": 
	    			if(rand == 1){
	    				ind[x] = "F# ";
	    			}else{
	    				ind[x] = "E ";			
	    			}
	    			
	    			break;
	    			
	    		case "F# ": 
	    			if(rand == 1){
	    				ind[x] = "G ";
	    			}else{
	    				ind[x] = "F ";			
	    			}
	    			
	    			break;
	    			
	    		case "G ": 
	    			if(rand == 1){
	    				ind[x] = "G# ";
	    			}else{
	    				ind[x] = "F# ";			
	    			}
	    			
	    			break;
	    			
	    		case "G# ": 
	    			if(rand == 1){
	    				ind[x] = "A ";
	    			}else{
	    				ind[x] = "G ";			
	    			}
	    			
	    			break;
	    			
	    		case "A ": 
	    			if(rand == 1){
	    				ind[x] = "A# ";
	    			}else{
	    				ind[x] = "G# ";			
	    			}
	    			
	    			break;
	    			
	    		case "A# ": 
	    			if(rand == 1){
	    				ind[x] = "B ";
	    			}else{
	    				ind[x] = "A ";			
	    			}
	    			
	    			break;
	    			 
	    		case "B ": 
	    			if(rand == 1){
	    				ind[x] = "C ";
	    			}else{
	    				ind[x] = "A# ";			
	    			}
	    			
	    			break;
	    			
	    		default: 
	    			if(rand == 1){
	    				ind[x] = "C ";
	    			}else{
	    				ind[x] = "A# ";			
	    			}
	    			
	    			break;
	    	    }   		
	    		
	    	}
	    }
			
		return ind;
	}
	
    /*String[] addintervalos(String[] melody) {
    	 
        Random randomGenerator = new Random();
 			
        float blow = 0;
        int contador = 0;
        
 	    for(int x = 0; x < numNot; x++) {
 	    		    
 	    	 melody[x] = melody[x].substring(0, melody[x].length() - 1);
 	    	 
 	     	 int rand = randomGenerator.nextInt(100);
 	    
 	     	 
 	    	 if( rand <= 40) {
 	    		 
 	    		blow += 1;
 	    		contador++;
 	    				
 	    		melody[x] += "q"; 
 
 	    		 
 	    	 }else if( rand <= 60){
 	    		 
  	    		blow += 0.5;
 	    		contador++;

 	    		melody[x] += "i"; 
 	    		 
 	    	 }else if(rand <= 75) {
 	    		
   	    		blow += 2;
 	    		contador++;

 	    		melody[x] += "h"; 
 	    		 
 	    	 }else if(rand <= 90){
 	    		
 	    		 blow += 0.25;
  	    		contador++;

 	    		 
  	    		melody[x] += "s"; 
  	    		  	    		 
 	    	 }else if(rand<= 99) {
 	    		
 	    		blow += 1; 
  	    		contador++;
 
 	    		melody[x] += "q"; 
 	    		 
 	    		 
 	    	 }
 	    	 
 	    	 if(blow >= 4  ) {
 	    		 
 	    		 if(blow == 4) {
 	    			 
 	    			 blow = 0;
 	    			 contador = 0;
 	    			 
 	    		 }else {
 	    			 
 	    			 blow = 0;
 	    			 
 	    			 x = x-(contador - 1);
 	    			 
 	    			 
 	    			 
 	    			 contador = 0;
 	    			 
 	    			 if(x < 0) {
 	    				 x = 0;
 	    			 }
 	    			 
 	    		 }
 	    		 
 	    		 
 	    	 }
 	    	    	
 	    }
 	    
 	    for(int x = 0; x <  numNot ; x++) {
 	    
 	    	melody[x] += " ";
 	    	
 	    }
 	    
 	    
 	    
 		return melody;		
		
	 }*/
	
	String createMelody(int numNot) {

	    String[][] genes = new String[numInd][numNot];
	    double[] fitnessInd = new double[numInd];
	    
	    String[] genesDoMelhor = {""};
	    

	    //gera a primeira população aleatoria
	    for(int i = 0; i < numInd; i++) {
	    	for(int j = 0; j < numNot; j++) {
		    	genes[i][j] = chooseNote();
	    	}
	    }
	    
	    lixo = ""; 
	    
	    for(int y = 0; y < numNot; y++){
	    	lixo += genes[0][y];
	    }	
	  
	    //player.play(lixo);

	    String sum = "";
	    
	    double max = 0;
	    int maxpos = 0;

	    for(int t = 0; t < numGen; t++) { // Roda as gerações
	    	
	    	 for(int i = 0; i < numInd; i++) { //verifica o fitness para cada individuo
			    fitnessInd[i] = returnFitness(genes[i], numNot);
			 }
			  		    
			 for(int i = 0; i < numInd; i++) {
			    if(fitnessInd[i] > max) {
			    	max = fitnessInd[i];
			    	maxpos = i;
			    	sum = "";
				    genesDoMelhor = genes[maxpos];

			    	//for(int y = 0; y < numNot; y++){
				    	//sum += genes[maxpos][y];
				     //}				    	
			    }    	
			 }
			 
			 String[][] newGen = new String[numInd][numNot];

			 for(int i = 0; i < numInd; i++){
				 newGen[i] = crossingOver(genes[torneioDeDois( fitnessInd )], genes[torneioDeDois(fitnessInd)], numNot); 
			 }
			 
			 for(int i = 0; i < numInd; i++) {
				 genes[i] = newGen[i];
			 }
			 
			 for(int i = 0; i < numInd; i++){
				genes[i] = mutation(genes[i], numNot);
			}
			 
			 PontosGraficos[t] = max; 
			 	        	
	    }
	    
	    
		   for(int y = 0; y < numNot; y++){
	    	 sum += genesDoMelhor[y];
	       }		 
		    
		   melodybateria = sum;
		   
		   if(list == 0) {
			   
			   melodynua = sum;
		   }else {
			   
			   melodynua2 = sum;
		   }
		   
		   
		   sum = "";
	    
	    for(int x = 0 ; x < numInd; x++) {
	    	System.out.println(	fitnessInd[x]);    			
	    }
	   
	   
	   for(int y = 0; y < numNot; y++){
    	 sum += genesDoMelhor[y];
       }		 
	    
	    
    	System.out.println(max);  
    	System.out.println(sum);
    	
    	return sum;
	}
	// w h q i s
	String returnInstrument(String instrument, int channel) {
		switch(instrument) {
		case "Guitarra Elétrica":
			return "KEY:" + key + " V" + channel + " I[OVERDRIVEN_GUITAR] (" + melodynua +  melodynua2 + melodynua + melodynua2 + ")3i ";
		case "Baixo Elétrico":
			return "KEY:" + key + " V" + channel + " I[ELECTRIC_BASS_FINGER] (" + melodynua2 + melodynua + melodynua2 + melodynua +  ")7i ";
		case "Trompete":
			return "KEY:" + key + " V" + channel + " I[Trumpet] (" + melodynua2 + melodynua + melodynua2 + melodynua + ")4i ";
		case "Piano":
			return "KEY:" + key + " V" + channel + " I[Piano]   (" + melodynua2 +  melodynua + melodynua2 + melodynua + ")6i ";
		case "Flauta":
			return "KEY:" + key + " V" + channel + " I[Flute]  (" + melodynua +  melodynua2 + melodynua + melodynua2 + ")7i ";
		case "Bateria":
			return "KEY:" + key + " V9 I[Piano] (" + melodynua + melodynua2 + melodynua + melodynua2 + ")36q ";
		default:
			
		}
		
		return "";
	}
	
	String returnIntroduction(String instrument, int channel, String rest) {
		
		switch(instrument) {
		
		case "Guitarra Elétrica":
			return "KEY:" + key + " V" + channel + " I[DISTORTION_GUITAR] (" + rest + melody + melody + ")4";
		case "Baixo Elétrico":
			return "KEY:" + key + " V" + channel + " I[ELECTRIC_BASS_FINGER] (" + rest + melody + melody + ")3";
		case "Trompete":
			return "KEY:" + key + " V" + channel +  " I[Trumpet] (" + rest + melody + melody + ")4"; 
		case "Piano":
			return "KEY:" + key + " V" + channel +  " I[Piano] (" + rest + melody + melody + ")6" ;
		case "Flauta":
			return "KEY:" + key + " V" + channel +  " I[Flute] (" + rest + melody + melody + ")5" ;
		case "Bateria":
			return "KEY:" + key + " V9 I[Piano] (" + rest + melody + melody + ")36";
		default:
			
		}
		
		return "";	
		
	}
	
	String returnVerse(String instrument, int channel, String rest) {
		
		switch(instrument) {
		
		case "Guitarra Elétrica":
			return "KEY:" + key + " V" + channel + " I[DISTORTION_GUITAR] (" + rest + melody2a + melody2a + melody2b + melody2b + ")4";
		case "Baixo Elétrico":
			return "KEY:" + key + " V" + channel + " I[ELECTRIC_BASS_FINGER] (" + rest + melody2a + melody2a + melody2b + melody2b + ")3";
		case "Trompete":
			return "KEY:" + key + " V" + channel +  " I[Trumpet] (" + rest + melody2a + melody2a + melody2b + melody2b + ")4"; 
		case "Piano":
			return "KEY:" + key + " V" + channel +  " I[Piano] (" + rest + melody2a + melody2a + melody2b + melody2b + ")6" ;
		case "Flauta":
			return "KEY:" + key + " V" + channel +  " I[Flute] (" + rest + melody2a + melody2a + melody2b + melody2b + ")5" ;
		case "Bateria":
			return "KEY:" + key + " V9 I[Piano] (" + rest + melody2a + melody2a + melody2b + melody2b + ")36";
		default:
			
		}
		
		return "";	
		
	}
	
	String returnChorus(String instrument, int channel, String rest) {
		
		switch(instrument) {
		
		case "Guitarra Elétrica":
			return "KEY:" + key + " V" + channel + " I[DISTORTION_GUITAR] (" + rest + melody2a + melody + melody2b + melody + ")4";
		case "Baixo Elétrico":
			return "KEY:" + key + " V" + channel + " I[ELECTRIC_BASS_FINGER] (" + rest + melody2a + melody + melody2b + melody + ")3";
		case "Trompete":
			return "KEY:" + key + " V" + channel +  " I[Trumpet] (" + rest + melody2a + melody + melody2b + melody + ")4"; 
		case "Piano":
			return "KEY:" + key + " V" + channel +  " I[Piano] (" + rest + melody2a + melody + melody2b + melody + ")6" ;
		case "Flauta":
			return "KEY:" + key + " V" + channel +  " I[Flute] (" + rest + melody2a + melody + melody2b + melody + ")5" ;
		case "Bateria":
			return "KEY:" + key + " V9 I[Piano] (" + rest + melody2a + melody + melody2b + melody + ")36";
		default:
			
		}
		
		return "";	
		
	}
	
	String returnSolo(String instrument, int channel, String rest) {
		
		switch(instrument) {
		
		case "Guitarra Elétrica":
			return "KEY:" + key + " V" + channel + " I[DISTORTION_GUITAR] (" + rest + melody3 + ")3i";
		case "Baixo Elétrico":
			return "KEY:" + key + " V" + channel + " I[ELECTRIC_BASS_FINGER] (" + rest + melody2a + melody + melody2b + melody + ")3";
		case "Trompete":
			return "KEY:" + key + " V" + channel +  " I[Trumpet] (" + rest + melody2a + melody + melody2b + melody + ")4"; 
		case "Piano":
			return "KEY:" + key + " V" + channel +  " I[Piano] (" + rest + melody2a + melody + melody2b + melody + ")6" ;
		case "Flauta":
			return "KEY:" + key + " V" + channel +  " I[Flute] (" + rest + melody2a + melody + melody2b + melody + ")5" ;
		case "Bateria":
			return "KEY:" + key + " V9 I[Piano] (" + rest + melody2a + melody + melody2b + melody + ")36";
		default:
			
		}
		
		return "";	
		
	}
	
	String returnConclusion(String instrument, int channel, String rest) {
		
		switch(instrument) {
		
		case "Guitarra Elétrica":
			return "KEY:" + key + " V" + channel + " I[DISTORTION_GUITAR] (" + rest + melody + melody2a + melody2b + melody + ")3";
		case "Baixo Elétrico":
			return "KEY:" + key + " V" + channel + " I[ELECTRIC_BASS_FINGER] (" + rest + melody + melody2a + melody2b + melody + ")3";
		case "Trompete":
			return "KEY:" + key + " V" + channel +  " I[Trumpet] (" + rest + melody + melody2a + melody2b + melody + ")4"; 
		case "Piano":
			return "KEY:" + key + " V" + channel +  " I[Piano] (" + rest + melody + melody2a + melody2b + melody + ")6" ;
		case "Flauta":
			return "KEY:" + key + " V" + channel +  " I[Flute] (" + rest + melody + melody2a + melody2b + melody + ")5" ;
		case "Bateria":
			return "KEY:" + key + " V9 I[Piano] (" + rest + melody + melody2a + melody2b + melody + ")36";
		default:
			
		}
		
		return "";	
		
	}
	
	String doRest(int div, int numNot) {
		String rest = "";
		
		for(int i = 0; i < numNot/div; i++) {
			rest += "Ri ";
		}
		
		return rest;
	}
	
	private JPanel contentPane;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Interface frame = new Interface();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public Interface() {
		Player player = new Player();
		
		setTitle("Bach Evolution");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 449, 365);
		contentPane = new JPanel();
		contentPane.setForeground(Color.WHITE);
		contentPane.setBorder(new LineBorder(Color.RED));
		setContentPane(contentPane);
		setLocationRelativeTo(null);
		contentPane.setLayout(null);
		
		Choice choice1 = new Choice();
		choice1.setForeground(Color.BLACK);
		choice1.setBounds(203, 39, 155, 20);
		contentPane.add(choice1);
		
		choice1.add("Nenhum");
		choice1.add("Guitarra Elétrica");
		choice1.add("Piano");
		choice1.add("Baixo Elétrico");
		choice1.add("Bateria");
		choice1.add("Flauta");
		choice1.add("Trompete");

		
		JLabel lblNewLabel = new JLabel("Instrumento 1");
		lblNewLabel.setBounds(61, 45, 89, 14);
		contentPane.add(lblNewLabel);
		
		JLabel lblInstrumento = new JLabel("Instrumento 2");
		lblInstrumento.setBounds(61, 94, 89, 14);
		contentPane.add(lblInstrumento);
		
		JLabel lblInstrumento_1 = new JLabel("Instrumento 3");
		lblInstrumento_1.setBounds(61, 145, 89, 14);
		contentPane.add(lblInstrumento_1);
		
		JLabel lblInstrumento_2 = new JLabel("Instrumento 4");
		lblInstrumento_2.setBounds(61, 196, 89, 14);
		contentPane.add(lblInstrumento_2);
		
		JLabel lblInstrumento_3 = new JLabel("Instrumento 5");
		lblInstrumento_3.setBounds(61, 246, 89, 14);
		contentPane.add(lblInstrumento_3);
		
		Choice choice2 = new Choice();
		choice2.setForeground(Color.BLACK);
		choice2.setBounds(203, 88, 155, 20);
		contentPane.add(choice2);
		
		choice2.add("Nenhum");
		choice2.add("Guitarra Elétrica");
		choice2.add("Piano");
		choice2.add("Baixo Elétrico");
		choice2.add("Bateria");
		choice2.add("Flauta");
		choice2.add("Trompete");

		Choice choice3 = new Choice();
		choice3.setForeground(Color.BLACK);
		choice3.setBounds(203, 139, 155, 20);
		contentPane.add(choice3);
		
		choice3.add("Nenhum");
		choice3.add("Guitarra Elétrica");
		choice3.add("Piano");
		choice3.add("Baixo Elétrico");
		choice3.add("Bateria");
		choice3.add("Flauta");
		choice3.add("Trompete");
		
		Choice choice4 = new Choice();
		choice4.setForeground(Color.BLACK);
		choice4.setBounds(203, 190, 155, 20);
		contentPane.add(choice4);
		
		choice4.add("Nenhum");
		choice4.add("Guitarra Elétrica");
		choice4.add("Piano");
		choice4.add("Baixo Elétrico");
		choice4.add("Bateria");
		choice4.add("Flauta");
		choice4.add("Trompete");
		
		Choice choice5 = new Choice();
		choice5.setForeground(Color.BLACK);
		choice5.setBounds(203, 240, 155, 20);
		contentPane.add(choice5);
		Button button_2 = new Button("Tocar m\u00FAsica");
		Button button = new Button("Gerar m\u00FAsica");
		
		button_2.setEnabled(false);
		
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				key = randomKey();
				song = "";
				items = 0;
				
				if(choice1.getSelectedItem() != "Nenhum") {
					items++;
					
				}

				if(choice2.getSelectedItem() != "Nenhum") {
					items++;
					
				}
				
				if(choice3.getSelectedItem() != "Nenhum") {
					items++;
			
				}
				
				if(choice4.getSelectedItem() != "Nenhum") {
					items++;
					
				}
				
				if(choice5.getSelectedItem() != "Nenhum") {
					items++;
					
				}
			    
				if(items != 0) {
					button_2.setEnabled(true);
				}
				
				if(items > 0) {
					melody = createMelody(8); // Introdução
					list++;
					melody2a = createMelody(4); // Verso
					melody2b = createMelody(4);
					list++;
					melody3 = createMelody(32); // Solo
					
					if(items < 5) {
						for(int i = 0; i < 5; i++) {
							switch(i) {
							case 0:
								song += returnInstrument(choice1.getSelectedItem(), 0);							
								break;
							case 1:
								song += returnInstrument(choice2.getSelectedItem(), 1);			
								break;
							case 2:
								song += returnInstrument(choice3.getSelectedItem(), 2);
								break;
							case 3:
								song += returnInstrument(choice4.getSelectedItem(), 3);
								break;
							case 4:
								song += returnInstrument(choice5.getSelectedItem(), 4);
								break;
							}
						}

					} else {
						for(int i = 0; i < 5; i++) { // Introdução
							switch(i) {
							case 0:
								song1 += returnIntroduction(choice1.getSelectedItem(), 0, "") + " ";							
								break;
							case 1:
								song1 += returnIntroduction(choice2.getSelectedItem(), 1, doRest(4, 8)) + " ";			
								break;
							case 2:
								song1 += returnIntroduction(choice3.getSelectedItem(), 2, doRest(2, 8)) + " ";
								break;
							case 3:
								//song1 += returnIntroduction(choice4.getSelectedItem(), 3);
								break;
							case 4:
								//song1 += returnIntroduction(choice5.getSelectedItem(), 4);
								break;
							}
						}
						
						for(int i = 0; i < 5; i++) { // Verso
							switch(i) {
							case 0:
								//song2 += returnVerse(choice1.getSelectedItem(), 0, "") + " ";							
								break;
							case 1:
								//song2 += returnVerse(choice2.getSelectedItem(), 1, doRest(4, 8)) + " ";			
								break;
							case 2:
								song2 += returnVerse(choice3.getSelectedItem(), 2, "") + " ";
								break;
							case 3:
								song2 += returnVerse(choice4.getSelectedItem(), 3, doRest(2, 8)) + "i ";
								break;
							case 4:
								//song2 += returnIntroduction(choice5.getSelectedItem(), 4);
								break;
							}
						}
						
						for(int i = 0; i < 5; i++) { // Chorus
							switch(i) {
							case 0:
								song3 += returnChorus(choice1.getSelectedItem(), 0, "") + " ";							
								break;
							case 1:
								song3 += returnChorus(choice2.getSelectedItem(), 1, doRest(4, 8)) + " ";			
								break;
							case 2:
								//song3 += returnChorus(choice3.getSelectedItem(), 2, "") + " ";
								break;
							case 3:
								song3 += returnChorus(choice4.getSelectedItem(), 3, doRest(1, 8)) + "i ";
								break;
							case 4:
								song3 += returnChorus(choice5.getSelectedItem(), 4, " ");
								break;
							}
						}
						
						for(int i = 0; i < 5; i++) { // Solo
							switch(i) {
							case 0:
								song4 += returnSolo(choice1.getSelectedItem(), 0,"" ) + " ";							
								break;
							case 1:
								//song3 += returnChorus(choice2.getSelectedItem(), 1, doRest(4, 8)) + " ";			
								break;
							case 2:
								song4 += returnSolo(choice3.getSelectedItem(), 2, "") + "i ";
								break;
							case 3:
								//song3 += returnChorus(choice4.getSelectedItem(), 3, doRest(1, 8)) + "i ";
								break;
							case 4:
								//song3 += returnChorus(choice5.getSelectedItem(), 4, " ");
								break;
							}
						}
						
						for(int i = 0; i < 5; i++) { // Solo
							switch(i) {
							case 0:
								song4 += returnConclusion(choice1.getSelectedItem(), 0, "" ) + " ";							
								break;
							case 1:
								song4 += returnConclusion(choice2.getSelectedItem(), 1, "") + " ";			
								break;
							case 2:
								song4 += returnConclusion(choice3.getSelectedItem(), 2, doRest(1, 16)) + "h ";
								break;
							case 3:
								//song3 += returnChorus(choice4.getSelectedItem(), 3, doRest(1, 8)) + "i ";
								break;
							case 4:
								song4 += returnConclusion(choice5.getSelectedItem(), 4, "h ");
								break;
							}
						}
					}
				} 
					
				//}
				
				System.out.println(items);
				
				Graphs graphs = new Graphs("Gráfico",
				         "Fitness x Geração");
				graphs.pack();
				
				graphs.receberParametros(PontosGraficos);
				
				RefineryUtilities.centerFrameOnScreen(graphs);          
			    graphs.setVisible(true);
			    graphs.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
			}
		});
		
		button.setForeground(Color.BLACK);
		button.setBackground(UIManager.getColor("Button.background"));
		button.setBounds(31, 284, 82, 22);
		contentPane.add(button);
		
		Button button_1 = new Button("M\u00FAsica aleat\u00F3ria");
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				player.play(lixo);
			}
		});
		button_1.setForeground(Color.BLACK);
		button_1.setBackground(UIManager.getColor("Button.background"));
		button_1.setBounds(166, 284, 98, 22);
		contentPane.add(button_1);

		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.out.println(song);
				if(items < 5) {
					player.play(song);
				} else {
					System.out.println(song1);
					player.play(song1); // INTRODUÇÃO
					Player player1 = new Player();
					System.out.println(song2);
					player1.play(song2); // VERSO
					Player player2 = new Player();
					System.out.println(song3);
					player2.play(song3); // CHORUS
					
					Player player3 = new Player();
					System.out.println("Verso");
					player3.play(song2); // VERSO
					
					Player player4 = new Player();
					player4.play(song4); // SOLO
					
					Player player5 = new Player();
					player5.play(song3); // CHORUS
					
					Player player6 = new Player();
					player6.play(song5); // CONCLUSÃO
					
					//player.play(song2); // VERSO
				}
			}
		});
		

		
		button_2.setForeground(Color.BLACK);
		button_2.setBounds(315, 284, 82, 22);
		contentPane.add(button_2);
		
		if(song != ""){
			button_2.setEnabled(true);
		}
		
		choice5.add("Nenhum");
		choice5.add("Guitarra Elétrica");
		choice5.add("Piano");
		choice5.add("Baixo Elétrico");
		choice5.add("Bateria");
		choice5.add("Flauta");
		choice5.add("Trompete");
	}
}
