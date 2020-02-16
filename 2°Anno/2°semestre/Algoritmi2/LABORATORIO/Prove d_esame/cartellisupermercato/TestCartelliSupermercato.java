package cartellisupermercato;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.UndirectedGraph;

public class TestCartelliSupermercato {

	@Test
	public void test() {
		
		UndirectedGraph g = new UndirectedGraph("8;0 5 11;0 2 13;0 6 10;1 2 7;1 6 9;1 3 15;2 5 8;3 6 8;4 7 8");
		CartelliSupermercato cs= new CartelliSupermercato(g,5);
		assertEquals(cs.direzioneIndicata(6),0);
		assertEquals(cs.direzioneIndicata(3),6);
		assertEquals(cs.direzioneIndicata(5),-1);
		assertEquals(cs.direzioneIndicata(7),-2);
		assertEquals(cs.direzioneIndicata(2),5);

	}

}
