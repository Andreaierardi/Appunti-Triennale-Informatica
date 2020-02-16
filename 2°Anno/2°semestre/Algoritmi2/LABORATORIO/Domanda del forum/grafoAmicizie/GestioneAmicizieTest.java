package grafoAmicizie;


import static org.junit.Assert.*;

import org.junit.Test;

public class GestioneAmicizieTest {

		 
	public void Crea()
	{
		GestioneAmicizie.crea("luca",0);
		GestioneAmicizie.crea("andrea",1);
		GestioneAmicizie.crea("giovanni",2);
		GestioneAmicizie.crea("ferra",3);
		GestioneAmicizie.crea("marco",4);
	}

	@Test
	public void TestAggiungi()
	{	
		Crea();
		GestioneAmicizie.addFriendship("andrea", "ferra");
		assertTrue(GestioneAmicizie.hasEdge(1, 3));
		assertFalse(GestioneAmicizie.hasEdge(0, 3));

		System.out.println(GestioneAmicizie.getFriends("giovanni").toString());
		
	}

	
	
}
