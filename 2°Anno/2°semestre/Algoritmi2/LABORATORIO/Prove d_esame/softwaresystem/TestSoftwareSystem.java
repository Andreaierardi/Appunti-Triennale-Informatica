package softwaresystem;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.DirectedGraph;

public class TestSoftwareSystem {

	@Test
	public void testCiclo() {

		DirectedGraph g = new DirectedGraph("3;0 1;1 2;0 2");
		SoftwareSystem testSS= new SoftwareSystem(g);
		assertEquals(testSS.hasCycle(),false);
		DirectedGraph g2 = new DirectedGraph("5;3 2;3 4;4 2");
		SoftwareSystem testSS2= new SoftwareSystem(g2);
		assertEquals(testSS2.hasCycle(),false);

		DirectedGraph g3 = new DirectedGraph("3;0 1;1 2;2 0");
		SoftwareSystem testSS3= new SoftwareSystem(g3);
		assertEquals(testSS3.hasCycle(),true);
		DirectedGraph g4 = new DirectedGraph("5;0 1;2 1;2 0;2 3;3 4;4 2");
		SoftwareSystem testSS4= new SoftwareSystem(g4);
		assertEquals(testSS4.hasCycle(),true);
		DirectedGraph g5 = new DirectedGraph("6;0 1;0 5;1 3;2 5;2 0;3 0;3 2;4 1;4 3;");
		SoftwareSystem testSS5= new SoftwareSystem(g5);
		assertEquals(testSS5.hasCycle(),true);
	}
	@Test
	public void testDirCicle()
	{
		DirectedGraph g = new DirectedGraph("4;0 2;1 0;1 2;2 3;3 0");
		SoftwareSystem testSS= new SoftwareSystem(g);
		assertEquals(testSS.getDirCycle().size(),3);
	}
}
