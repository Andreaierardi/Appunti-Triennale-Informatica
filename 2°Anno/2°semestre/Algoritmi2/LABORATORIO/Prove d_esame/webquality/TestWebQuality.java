 package webquality;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.*;

public class TestWebQuality {

	@Test
	public void testDepth() {
		DirectedGraph g = new DirectedGraph("7;0 1;0 3;1 4;2 5;3 6;3 2;4 3;5 0;5 1;");
		WebQuality wq = new WebQuality(g,0);
		assertEquals(wq.depth(4),2);
		assertEquals(wq.depth(0),3);

	}

}
