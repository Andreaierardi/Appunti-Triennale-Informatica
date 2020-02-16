
import java.awt.Color;

public class SeamCarver {
    private static final int BORDER_ENERGY = 195075;
    private Picture pict;
    private int width;
    private int height;
    private double[][] energy;
  
    private double[][] costo;
    private int[][] from;

    public SeamCarver(Picture picture) { // create a seam carver object based on
                                         // the given picture
        pict = new Picture(picture);
        width = pict.width();
        height = pict.height();
        costo= new double[width][height];
        from = new int[width][height];
        
        energy = new double[width][height];
        
        init();
    }
    
    private void init(){
    	
    	for(int x = 0 ;x<energy.length;x++)
    		for(int y = 0 ;y <energy[x].length;y++)
    			{


    				if(x==0 || y == 0 || x==energy.length-1|| y == energy[x].length-1)
    				{
    						energy[x][y] = BORDER_ENERGY;
    						continue;
    				}
     				Color leftColor = pict.get(x-1, y);
    	    	
    				Color rightColor=pict.get(x+1,y);
    				
    				int	deltaR	=	leftColor.getRed()	-	rightColor.getRed();
    				int	deltaG	=	leftColor.getGreen()	-	rightColor.getGreen();
    				int	deltaB	=	leftColor.getBlue()	-	rightColor.getBlue();
    				
    				int deltaX	=	(deltaR*deltaR)+(deltaG*deltaG)+(deltaB*deltaB);
    				
    				Color upColor = pict.get(x, y+1);
    				Color bottomColor = pict.get(x, y-1);
    				deltaR	=	upColor.getRed()	-	bottomColor.getRed();
    				deltaG	=	upColor.getGreen()	-	bottomColor.getGreen();
    				deltaB	=	upColor.getBlue()	-	bottomColor.getBlue();
    				
    				int deltaY	=	(deltaR*deltaR)+(deltaG*deltaG)+(deltaB*deltaB);

    				energy[x][y] = deltaX +deltaY;
    			}
    }
    

    public Picture picture() { // current picture
        return pict;
    }

    public int width() { // width of current picture
        return width;
    }

    public int height() { // height of current picture
        return height;
    }

 
    public double energy(int x, int y) { // energy of pixel at column x and row y
        return energy[x][y];
    }

    public double[] getCosto(int riga){
    	if ((riga < 0) || (riga >= height)){
    		throw new java.lang.IndexOutOfBoundsException();
    	} else {
    	double[] costLine = new double[width()];
    	for (int x = 0; x < width() ; ++x){
    		costLine[x] = costo[x][riga];
    	}
    	return costLine;
    	}
    }
   
    private void bellmanFordVert() {
    	
    	for(int x = 0 ; x< costo.length;x++)
    		costo[x][0]= BORDER_ENERGY;
    	
    	for(int x = 0 ; x< costo.length;x++)
        	for(int y = 0 ; y< costo[x].length;y++)
        	{
    			if(x==0)
    				costo[x][y]=Math.min(costo[x][y-1], costo[x+1][y-1])+energy[x][y];
        		else if(x == costo.length-1)
        			costo[x][y]=Math.min(costo[x-1][y-1], costo[x][y-1])+energy[x][y];
        		else
        			costo[x][y]=Math.min(Math.min(costo[x-1][y-1], costo[x][y-1]),costo[x+1][y-1])+energy[x][y];

    			int prec = 0;
    			for(int i = x-1 ;i<x+2;i++)
    				if(costo[x][y]== costo[i][y-1] + energy[x][y])
    					prec = i;
    			from[x][y] = prec;
        	}
    		
        		

    	
    }
    


    private int[] ricostruisciSeamVerticale() { //da implementare: a partire da from ricostruisce il seam verticale
    	
    	
    	int [] seam = new int[costo.length];
    	double minX = Double.POSITIVE_INFINITY;
    	for(int x = 0;x<costo.length;x++)
    	{
    		if(costo[x][0]<minX)
    			minX = costo[x][0];
    	}
    	double last = costo[costo.length-1][costo.length-1];
    	
        return null;
    }
    

  
    
    public int[] findVerticalSeam() { // sequence of indices for vertical seam
        bellmanFordVert();
        return ricostruisciSeamVerticale();
    }

    
    public int[] findHorizontalSeam() { // sequence of indices for horizontal seam
    	//non implementato, lo potete fare come progetto futuro, aggiungendo un BellmanFordOrizzontale ecc
    	return null;
    }

    
    private boolean isLegalSeam(int[] seam) {
        boolean isLegal = true;
        for (int h = 1; h < seam.length; ++h) {
            int diff = seam[h] - seam[h - 1];
            if ((diff * diff) > 1) {
                isLegal = false;
            }
        }
        return isLegal;
    }

    public void removeHorizontalSeam(int[] seam) { // remove horizontal seam
                                                   // from current picture
        //non implementato (se si vuole implementarlo successivamente insieme a tutto
    	//quello che serve per il seam orizzontale
    }

    
    public void removeVerticalSeam(int[] seam) { // remove vertical seam from
                                                 // current picture
        if (seam == null) {
            throw new java.lang.NullPointerException();
        } else {
            if ((height <= 1) || (width <= 1) || (seam.length != height)
                    || (!isLegalSeam(seam))) {
                throw new java.lang.IllegalArgumentException();
            } else {
                Picture nuPict = new Picture(width() - 1, height());

                for (int y = 0; y < height; ++y) {
                    int w = 0;
                    for (int x = 0; x < width; ++x) {
                        if (seam[y] != x) {
                            nuPict.set(w, y, pict.get(x, y));
                            ++w;
                        }
                    }
                }
                pict = nuPict;
                width = pict.width();
                height = pict.height();
                
                costo= new double[width][height];
                from = new int[width][height];
                
                energy = new double[width][height];
                init();
            }
        }
    }
    
}
