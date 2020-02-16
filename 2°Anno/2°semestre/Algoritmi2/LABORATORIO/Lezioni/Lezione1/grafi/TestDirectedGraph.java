/********************************************************************************
 * @author Lavinia Egidi
 * UPO, Informatica, corso di Algoritmi 2
 * Classe di test per grafi orientati
 **********************************************************************************/package it.uniupo.algo2.grafi;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.util.Iterator;

import org.junit.Before;
import org.junit.FixMethodOrder;
import org.junit.Test;
/********************************************************************************
 * ORDINE DI ESECUZIONE DEI TEST
 * attenzione! i test dovrebbero essere indipendenti dall'ordine di esecuzione
 * Qui l'ordine ha scopo didattico (guidarvi nell'implementazione) e l'idea e'
 * che progredendo nel lavoro di implementazione, i test uno dopo l'altro, in ordine alfabetico,
 * hanno successo. 
 **********************************************************************************/
import org.junit.runners.MethodSorters;

import it.uniupo.libPrimoLab.Edge;
import it.uniupo.libPrimoLab.GraphInterfaceEs;
@FixMethodOrder(MethodSorters.NAME_ASCENDING)  

public class TestDirectedGraph {
    GraphInterfaceEs gtest;
    
    @Before
    public void setUp() {
        gtest = new DirectedGraph(5);
    }
    
    @Test
    public void test000Create() {  //il costruttore non ha errori di runtime
        assertNotNull(gtest);
    }
    
    @Test
    public void test010Order() {    //testa il metodo getOrder()
        assertEquals("il grafo ha 5 nodi, il risultato deve essere:", 5, gtest.getOrder());
    }
    
    @Test
    public void test015EdgeNum() {  //primo test per il metodo getEdgeNum(), grafo senza archi
    	assertEquals("il grafo non ha archi, il risultato deve essere:", 0,gtest.getEdgeNum());
    }
    
    @Test
    public void test017AddEdgeNum() {  //l'aggiunta di un arco deve incrementare correttamente il numero di archi
        gtest = new DirectedGraph(5);
        gtest.addEdge(2,3);
        assertEquals("il grafo ha un arco, il risultato deve essere:",1,gtest.getEdgeNum());
    }
    
    @Test
    public void test020HasEdge(){   //testa il metodo hasEdge(int,int)
        gtest = new DirectedGraph(5);
        gtest.addEdge(2,3);
        gtest.addEdge(2,1);
        assertTrue("L'arco (2,1) e' nel grafo, invece non risulta", gtest.hasEdge(2,1));
    }
    
   @Test
   public void test022HasNotEdge(){    //il grafo e' orientato: se (i,j) e' un arco, non lo e' necessariamente anche (j,i)
       gtest = new DirectedGraph(5);
       gtest.addEdge(2,3);
       gtest.addEdge(2,1);
       assertTrue("L'arco (3,2) non e' nel grafo, invece risulta che ci sia", !gtest.hasEdge(3,2));
   }
   
   
    
    @Test
    public void test030AdjListSize() { //verifica che i vicini di un nodo restituiti da getNeighbors siano il numero giusto
        gtest = new DirectedGraph(5);
        gtest.addEdge(2,3);
        gtest.addEdge(2,1);
        gtest.addEdge(2,4);
        gtest.addEdge(1,3);
        Iterator<Integer> it = gtest.getNeighbors(2).iterator();
        assertTrue("2 ha almeno un vicino", it.hasNext());
        it.next();
        assertTrue("2 ha almeno due vicini", it.hasNext());
        it.next();
        assertTrue("2 ha almeno tre vicini", it.hasNext());
        it.next();
        assertTrue("2 non ha quattro vicini", !it.hasNext());
    }
    
    @Test
    public void test034AdjListCont() { //verifica che getNeighbors restituisca i nodi giusti
        gtest = new DirectedGraph(5);
        gtest.addEdge(4,3);
        gtest.addEdge(4,2);
        gtest.addEdge(1,3);
        Iterator<Integer> it = gtest.getNeighbors(4).iterator();
        StringBuilder buf = new StringBuilder();
        while (it.hasNext()){
            buf.append(Integer.toString(it.next()));
            buf.append(" ");
        }
        String res1 = "3 2 ";
        String res2 = "2 3 ";
        String real = new String(buf);
        assertTrue("i vicini di 4 sono 2 e 3, ma getAdj da' un risultato diverso", real.equals(res1) || real.equals(res2) );
    }
    
    @Test
    public void test036AdjListSize2() { //altra verifica su getNeighbors: se (i,j) e' un arco, ma non (j,i), i non e' vicino di j 
        gtest = new DirectedGraph(5);
        gtest.addEdge(2,3);
        gtest.addEdge(2,1);
        gtest.addEdge(1,3);
        Iterator<Integer> it = gtest.getNeighbors(1).iterator();
        assertTrue("1 ha almeno un vicino", it.hasNext());
        it.next();
        assertTrue("1 non ha due vicini", !it.hasNext());
    }
    
    @Test
    public void test040GetEdges() {  //verifica il numero di archi restituiti dal metodo getIncidentEdges(int)
        gtest = new DirectedGraph(5);
        gtest.addEdge(2,3);
        gtest.addEdge(4,1);
        gtest.addEdge(3,4);
        gtest.addEdge(2,4);  
        int cnt = 0;
        for (Iterator<Edge> iterator = gtest.getIncidentEdges(4).iterator(); iterator.hasNext();iterator.next()) {
            ++cnt;
        }
        assertEquals("4 ha 1 vicino",1, cnt);       
    }
    
    @Test
    public void test042GetEdges2() { //verifica che getIncidentEdges restituisca gli archi corretti
        gtest = new DirectedGraph(5);
        gtest.addEdge(2,3);
        gtest.addEdge(2,1);
        gtest.addEdge(0,4);
        gtest.addEdge(4,2);
        int[] edges = new int[5];
        for(int i = 0; i < 5; ++i){
            edges[i]=-1;
        }
        for (Edge e: gtest.getIncidentEdges(2)) {
            edges[e.getHead()] = 1;
        }
        assertTrue("3 e' adiacente a 2", edges[3] == 1); 
        assertTrue("4 non e' adiacente a 2", edges[4] == -1); 
    }
    


    @Test
    public void test060GetEdgesWithTail() { //verifica che le Edge restituite da getIncidentEdges abbiano la "tail" giusta
        gtest = new DirectedGraph(4);
        gtest.addEdge(0,1);
        gtest.addEdge(1,2);
        gtest.addEdge(0,2);
        Iterator<Edge> nei = gtest.getIncidentEdges(0).iterator();
        assertTrue("0 ha due archi incidenti, la cui tail e' sempre 0",(nei.next().getTail() == 0) && (nei.next().getTail() == 0 ));
    }
    
    /***************************************************************************
    * grafi con archi pesati
    *****************************************************************************/
    
   @Test
   public void test070AddWithWeight() {  //verifica che il peso di un arco sia gestito correttamente da addEdge e getEdges
       gtest = new DirectedGraph(5);
       gtest.addEdge(1,2,2);
       gtest.addEdge(2,1,7);
       Edge e = gtest.getIncidentEdges(2).iterator().next();
       assertEquals("Il peso dell'arco (2,1) deve essere: ", 7, e.getWeight());
   }
   
   @Test
   public void test080GetEdgesWithTail() { //verifica che le Edge restituite da getIncidentEdges abbiano la "tail" giusta
       gtest = new DirectedGraph(4);
       gtest.addEdge(0,1,1);
       gtest.addEdge(1,2,3);
       gtest.addEdge(0,2,1);
       Iterator<Edge> nei = gtest.getIncidentEdges(0).iterator();
       assertTrue("0 ha due archi incidenti, la cui tail e' sempre 0",(nei.next().getTail() == 0) && (nei.next().getTail() == 0 ));
   }
  
   
   /***************************************************************************
    * Test per un eventuale altro metodo
    *  public void removeEdge(int tail, int head); //delete edge (tail,head)    
    ****************************************************************************/

   @Test
   public void test050Remove1() { //verifica che il metodo removeEdge(int i,int j) elimini l'arco (i,j)
       gtest = new DirectedGraph(5);
       gtest.addEdge(1,3);
       gtest.addEdge(2,1);
       gtest.addEdge(0,4);
       ((DirectedGraph) gtest).removeEdge(1,3);
       boolean found = false;
       for (Edge e:  gtest.getIncidentEdges(1)) {
           if (e.getHead() == 3) {
               found = true;
           }
       }
       assertTrue("3 non e' piu' adiacente a 1", !found);
   }
   
   @Test
   public void test052Remove2() { //verifica che il metodo removeEdge(int i,int j) NON elimini l'arco (j,i)
       gtest = new DirectedGraph(5);
       gtest.addEdge(1,3);
       gtest.addEdge(2,1);
       gtest.addEdge(0,4);
       ((DirectedGraph) gtest).removeEdge(3,1);
       boolean found = false;
       for (Edge e:  gtest.getIncidentEdges(1)) {
           if (e.getHead() == 3) {
               found = true;
           }
       }
       assertTrue("3 e' adiacente a 1", found);
   }  

   @Test
   public void test054RemoveCount() { //verifica che il metodo removeEdge(i,j) non aggiorni il numero degli archi
   									//se non toglie archi
       gtest = new DirectedGraph(5);
       gtest.addEdge(1,3);
       gtest.addEdge(2,1);
       gtest.addEdge(0,4);
       ((DirectedGraph) gtest).removeEdge(1,3);
       assertEquals("Il grafo ha 2 archi dopo la cancellazione:", 2, gtest.getEdgeNum());
   }  
   
   @Test
   public void test056RemoveNothingCount() { //verifica che il metodo removeEdge(i,j) non aggiorni il numero degli archi
   									//se non toglie archi
       gtest = new DirectedGraph(5);
       gtest.addEdge(1,3);
       gtest.addEdge(2,1);
       gtest.addEdge(0,4);
       ((DirectedGraph) gtest).removeEdge(3,1);
       assertEquals("Il grafo ha 3 archi dopo la cancellazione", 3, gtest.getEdgeNum());
   }  

}
