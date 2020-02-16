import static org.junit.Assert.*;

import org.junit.Test;


public class TestSeamCarver {
	
	String filename;
    Picture inputImg;
    SeamCarver sc;
    
    /**
   	 * Returns a string representation of the input, as a sequence of
   	 * blank separated strings
   	 * @param arr n array of doubles
   	 * @return a string representation of arr as blank separated strings
   	 */
       private static String getString(double[] arr){
           StringBuilder buf = new StringBuilder();
           for (int i = 0; i < arr.length; ++i){
           buf.append(arr[i]+" ");
           }
           return buf.toString().trim();
       }
       
       /**
   	 * Returns a string representation of the input, as a sequence of
   	 * blank separated strings
   	 * @param arr n array of integers
   	 * @return a string representation of arr as blank separated strings
   	 */
       private static String getString(int[] arr){
           StringBuilder buf = new StringBuilder();
           for (int i = 0; i < arr.length; ++i){
           buf.append(arr[i]+" ");
           }
           return buf.toString().trim();
       }

	@Test
	public void testEnergy3x7() {
		
		filename = "seamCarving/3x7.png";
		inputImg = new Picture(filename);
		sc = new SeamCarver(inputImg);
		
		String[] energies = {"195075.0 195075.0 195075.0",
							"195075.0 86627.0 195075.0",
							"195075.0 55775.0 195075.0",
							"195075.0 105720.0 195075.0",
							"195075.0 63180.0 195075.0",
							"195075.0 78196.0 195075.0",
							"195075.0 195075.0 195075.0"};
		
		String list;
		double[] enLine = new double[sc.width()];
		for (int y = 0; y < sc.height(); ++y){
		for(int x = 0; x < sc.width(); ++x){
			enLine[x] = sc.energy(x, y);
		}
		list = getString(enLine);
		assertTrue(list.equals(energies[y]));
		}	
	}
	
	@Test
	public void testEnergy6x5() {
		filename = "seamCarving/6x5.png";
		inputImg = new Picture(filename);
		sc = new SeamCarver(inputImg);
		
		String[] energies = {"195075.0 195075.0 195075.0 195075.0 195075.0 195075.0",
								"195075.0 23346.0 51304.0 31519.0 55112.0 195075.0",
								"195075.0 47908.0 61346.0 35919.0 38887.0 195075.0",
								"195075.0 31400.0 37927.0 14437.0 63076.0 195075.0",
								"195075.0 195075.0 195075.0 195075.0 195075.0 195075.0"};
		
		String list;
		double[] enLine = new double[sc.width()];
		for (int y = 0; y < sc.height(); ++y){
		for(int x = 0; x < sc.width(); ++x){
			enLine[x] = sc.energy(x, y);
		}
		list = getString(enLine);
		assertTrue(list.equals(energies[y]));
		}	
	}
	
	@Test
	public void testCosto4x6() {
		
		filename = "seamCarving/4x6.png";
		inputImg = new Picture(filename);
		sc = new SeamCarver(inputImg);
		
		String[] costs = {"195075.0 195075.0 195075.0 195075.0",
							"390150.0 271065.0 225078.0 390150.0",
							"466140.0 255080.0 328124.0 420153.0",
							"450155.0 284595.0 293353.0 523199.0",
							"479670.0 357998.0 319994.0 488428.0",
							"553073.0 515069.0 515069.0 515069.0"};
		
		String list;
		sc.findVerticalSeam();
		for (int y = 0; y < sc.height(); ++y){
			double[] costLine = sc.getCosto(y);
			list = getString(costLine);
		
		assertTrue(list.equals(costs[y]));
		}	
	}
	
	@Test
	public void testCosto7x3() {
		
		filename = "seamCarving/7x3.png";
		inputImg = new Picture(filename);
		sc = new SeamCarver(inputImg);
		
		String[] costs = {"195075.0 195075.0 195075.0 195075.0 195075.0 195075.0 195075.0",
					"390150.0 251299.0 267315.0 243015.0 265445.0 280554.0 390150.0",
					"446374.0 446374.0 438090.0 438090.0 438090.0 460520.0 475629.0"};
		
		String list;
		sc.findVerticalSeam();
		for (int y = 0; y < sc.height(); ++y){
			double[] costLine = sc.getCosto(y);
			list = getString(costLine);
		
		assertTrue(list.equals(costs[y]));
		}	
	}
	
	@Test
	public void testSeam3x7() {
		
		filename = "seamCarving/3x7.png";
		inputImg = new Picture(filename);
		sc = new SeamCarver(inputImg);
		
		String list = getString(sc.findVerticalSeam());
		assertTrue(list.substring(2, list.length()-2).equals("1 1 1 1 1"));
	}
	
	@Test
	public void testSeam10x12() {
		
		filename = "seamCarving/10x12.png";
		inputImg = new Picture(filename);
		sc = new SeamCarver(inputImg);
		
		String list = getString(sc.findVerticalSeam());
		assertTrue(list.substring(2, list.length()-2).equals("6 7 8 7 7 6 7 6 5 6") && 
				(list.charAt(0) == '5' || list.charAt(0) == '6' || list.charAt(0) == '7') &&
				(list.charAt(list.length()-1) == '5' || list.charAt(list.length()-1) == '6' || list.charAt(list.length()-1) == '7'));
	}
	
	@Test
	public void testSeam12x10() {
		
		filename = "seamCarving/12x10.png";
		inputImg = new Picture(filename);
		sc = new SeamCarver(inputImg);
		
		String list = getString(sc.findVerticalSeam());
		assertTrue(list.substring(2, list.length()-2).equals("7 7 6 6 7 7 7 8") && 
				(list.charAt(0) == '6' || list.charAt(0) == '7' || list.charAt(0) == '8') &&
				(list.charAt(list.length()-1) == '7' || list.charAt(list.length()-1) == '8' || list.charAt(list.length()-1) == '9'));
	}

}
