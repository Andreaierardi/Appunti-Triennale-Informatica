package meteturistiche;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.UndirectedGraph;

public class TestMeteTuristiche {

	@Test
	public void testdestinazioneConsigliata() 
	{
		UndirectedGraph g = new UndirectedGraph("4;0 1 3;1 2 1;0 2 7;0 3 6");
		int [] interesse = {5,2,7,3};
		MeteTuristiche mt = new MeteTuristiche(g, interesse);
	/*	assertEquals(mt.destinazioneConsigliata(0,0,8),2);
		assertEquals(mt.destinazioneConsigliata(0,0,3),0);
		assertEquals(mt.destinazioneConsigliata(0,6,8),2);
		assertEquals(mt.destinazioneConsigliata(0,1,5),2);
		assertEquals(mt.destinazioneConsigliata(0,1,2),-1);
		assertEquals(mt.destinazioneConsigliata(-1,1,5),-2);
		assertEquals(mt.destinazioneConsigliata(6,3,4),-2);
		assertEquals(mt.destinazioneConsigliata(0,4,3),-2);*/
		assertEquals(mt.destinazioneConsigliata(0,3,3),1);

	}

}
