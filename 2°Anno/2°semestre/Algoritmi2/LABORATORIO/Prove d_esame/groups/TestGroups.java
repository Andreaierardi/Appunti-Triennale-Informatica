package groups;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestGroups {

	@Test
	public void testInit() {
		
		Groups g = new Groups(3);
		assertNotNull(g);
	}

	@Test
	public void testoptimalRebookingCost()
	{
		int seats = 10;
		int gSizes[]= {5,8,3};
		int gCosts[]= {3,11,9};
		
		Groups g = new Groups(seats);
		assertEquals(g.optimalRebookingCost(gSizes, gCosts),11);
		
		seats= 10;
		int gSizes2[]= {5,8};
		//gCosts rimane invariato dall'esempio precedente
		g = new Groups(seats);
		assertEquals(g.optimalRebookingCost(gSizes2, gCosts),-1);
		
		seats=-4;
		//gSizes e gCosts non variano
		g = new Groups(seats);
		assertEquals(g.optimalRebookingCost(gSizes, gCosts),-1);
		
		seats=0;
		//gSizes e gCosts non variano
		g = new Groups(seats);
		assertEquals(g.optimalRebookingCost(gSizes, gCosts),23);
		
		seats=20;
		//gSizes e gCosts non variano
		g = new Groups(seats);
		assertEquals(g.optimalRebookingCost(gSizes, gCosts),0);


	}
}
