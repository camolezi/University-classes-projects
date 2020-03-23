package Plot;

import java.awt.Color; 
import java.awt.BasicStroke; 

import org.jfree.chart.ChartPanel; 
import org.jfree.chart.JFreeChart; 
import org.jfree.data.xy.XYDataset; 
import org.jfree.data.xy.XYSeries; 
import org.jfree.ui.ApplicationFrame; 
import org.jfree.ui.RefineryUtilities; 
import org.jfree.chart.plot.XYPlot; 
import org.jfree.chart.ChartFactory; 
import org.jfree.chart.plot.PlotOrientation; 
import org.jfree.data.xy.XYSeriesCollection; 
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;

public class Graphs extends ApplicationFrame {

   public Graphs( String applicationTitle, String chartTitle ) {
      super(applicationTitle);
      JFreeChart xylineChart = ChartFactory.createXYLineChart(
         chartTitle ,
         "Gerações" ,
         "Fitness" ,         
         createDataset() ,
         PlotOrientation.VERTICAL ,
         true , true , false);
         
      ChartPanel chartPanel = new ChartPanel( xylineChart );
      chartPanel.setPreferredSize( new java.awt.Dimension( 560 , 367 ) );
      final XYPlot plot = xylineChart.getXYPlot( );
      
      XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer( );
      renderer.setSeriesPaint( 0 , Color.RED );
      renderer.setSeriesPaint( 1 , Color.GREEN );
      renderer.setSeriesPaint( 2 , Color.YELLOW );
      renderer.setSeriesStroke( 0 , new BasicStroke( 4.0f ) );
      renderer.setSeriesStroke( 1 , new BasicStroke( 3.0f ) );
      renderer.setSeriesStroke( 2 , new BasicStroke( 2.0f ) );
      plot.setRenderer( renderer ); 
      setContentPane( chartPanel ); 
   }
   
   final XYSeries melody1 = new XYSeries( "Melodia 1" );
   
   public void receberParametros(double[] pontos) {
	   
	  
	      
	      for(int x = 0; x< pontos.length ; x++) {
	    	  
	    	  melody1.add( x , pontos[x] ); 
	    	  
	      }
	                
	      
	      final XYSeries melody2 = new XYSeries( "Melodia 2" );          
	      melody2.add( 1.0 , 4.0 );          
	      melody2.add( 2.0 , 5.0 );          
	      melody2.add( 3.0 , 6.0 );          
	      
	      final XYSeries melody3 = new XYSeries( "Melodia 3" );          
	      melody3.add( 3.0 , 4.0 );          
	      melody3.add( 4.0 , 5.0 );          
	      melody3.add( 5.0 , 4.0 );          
	      
	 	   
	   
	   
	   
   }
   
  
   
   private XYDataset createDataset( ) {
    
      
      final XYSeriesCollection dataset = new XYSeriesCollection( );          
      dataset.addSeries( melody1 );          
     // dataset.addSeries( melody2 );          
      //dataset.addSeries( melody3 );
      return dataset;
   }

   public static void main( String[ ] args ) {
      Graphs chart = new Graphs("Browser Usage Statistics",
         "Which Browser are you using?");
      chart.pack( );          
      RefineryUtilities.centerFrameOnScreen( chart );          
      chart.setVisible( true ); 
   }
}