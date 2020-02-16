/********************************************************************************
 * @author Lavinia Egidi
 * UPO, Informatica, corso di Algoritmi 2
 * Classe di test per grafi non orientati
 **********************************************************************************/
package it.uniupo.algo2.grafi;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.util.Iterator;

import org.junit.Before;
import org.junit.Test;

import it.uniupo.libPrimoLab.Edge;
import it.uniupo.libPrimoLab.GraphInterfaceEs;

/********************************************************************************
 * ORDINE DI ESECUZIONE DEI TEST
 * attenzione! i test dovrebbero essere indipendenti dall'ordine di esecuzione
 * Qui l'ordine ha scopo didattico (guidarvi nell'implementazione) e l'idea e'
 * che progredendo nel lavoro di implementazione, i test uno dopo l'altro, in ordine alfabetico,
 * hanno successo. Per forzare l'ordine alfabetico, scommentate l'annotazione
 * qui sotto. Alla fine, dovreste ricommentare l'annotazione e verificare che
 * i test abbiano comunque successo anche se eseguiti in ordine diverso (comunque
 * non e'  detta che vengano eseguiti in ordine diverso.
 * L'annotazione @FixMethodOrder funziona solo da JUnit 4.11 in avanti.
 **********************************************************************************/
//@FixMethodOrder(MethodSorters.NAME_ASCENDING)  

public class TestUndirectedGraph {
    GraphInterfaceEs gtest;
    
    @Before
    public void setUp() {
        gtest = new UndirectedGraph(5);
    }
    
    @Test
    public void test000Create() { //il costruttore non da' errori a run time
        assertNotNull(gtest);
    }
    
    @Test
    public void test005Order() {  //testa il metodo getOrder()
        assertTrue("il grafo ha 5 nodi", gtest.getOrder() == 5 );
    }
    
    @Test
    public void test010EdgeNum() { //primo test per il metodo getEdgeNum(), se il grafo e' vuoto
        assertTrue("il grafo non ha archi", gtest.getEdgeNum() == 0);
    }
    
    @Test
    public void test011AddEdgeNum() {  //l'aggiunta di un arco deve incrementare correttamente il numero di archi
        gtest = new UndirectedGraph(5);
        gtest.addEdge(2,3);
        assertTrue("il grafo adesso ha un arco",gtest.getEdgeNum() == 1);
    }
    
   @Test
   public void test020HasEdge(){ //testa il metodo hasEdge(int,int)
       gtest = new UndirectedGraph(5);
       gtest.addEdge(2,3);
       gtest.addEdge(2,1);
       assertTrue("2 e' adiacente a 3", gtest.hasEdge(2,3));
   }
   
   @Test
   public void test022HasEdge2(){  //il grafo non e' orientato: se (i,j) e' un arco, lo e' anche (j,i)
       gtest = new UndirectedGraph(5);
       gtest.addEdge(2,3);
       gtest.addEdge(2,1);
       assertTrue("2 e' un vicino di 1", gtest.hasEdge(1,2));
   }
   
   @Test
   public void test024HasEdge3(){ //verifica che il metodo hasEdge restituisca false quando appropriato
       gtest = new UndirectedGraph(5);
       gtest.addEdge(2,3);
       gtest.addEdge(3,1);
       assertTrue("2 non e' un vicino di 1", !gtest.hasEdge(1,2));
   }
   
    @Test
    public void test030AdjListSize() {  //verifica che i vicini di un nodo restituiti da getNeighbors siano il numero giusto
        gtest = new UndirectedGraph(5);
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
    public void test032AdjListCont() { //verifica che getNeighbors restituisca i nodi giusti
        gtest = new UndirectedGraph(5);
        gtest.addEdge(4,3);
        gtest.addEdge(4,2);
        gtest.addEdge(1,3);
        Iterator<Integer> it = gtest.getNeighbors(4).iterator();
        StringBuilder buf = new StringBuilder();
        while (it.hasNext()){
            buf.append(Integer.toString(it.next()));
            buf.append(" ");
        }
        String real = new String(buf);
        assertTrue("i vicini di 4 sono 2 e 3", real.equals("3 2 ") || real.equals("2 3 ") );
    }
    
    @Test
    public void test034AdjListSize2() { //altra verifica su getNeighbors: se (i,j) e' un arco, i e' vicino di j 
        gtest = new UndirectedGraph(5);
        gtest.addEdge(2,3);
        gtest.addEdge(2,1);
        gtest.addEdge(1,3);
        Iterator<Integer> it = gtest.getNeighbors(1).iterator();
        assertTrue("1 ha almeno un vicino", it.hasNext());
        it.next();
        assertTrue("1 ha almeno due vicini", it.hasNext());
        it.next();
        assertTrue("1 non ha tre vicini", !it.hasNext());
    }
    
    @Test
    public void test040GetEdges() {  //verifica il numero di nodi restituiti dal metodo getIncidentEdges(int)
        gtest = new UndirectedGraph(5);
        gtest.addEdge(2,3);
        gtest.addEdge(4,1);
        gtest.addEdge(3,4);
        gtest.addEdge(2,4);  
        int cnt = 0;
        for (Iterator<Edge> iterator = gtest.getIncidentEdges(4).iterator(); iterator.hasNext(); iterator.next()) {
            ++cnt;
        }
        assertTrue("4 ha tre vicini", cnt == 3);       
    }
    
    @Test
    public void test042GetEdges2() {  //verifica che getIncidentEdges restituisca gli archi corretti
        gtest = new UndirectedGraph(5);
        gtest.addEdge(2,3);
        gtest.addEdge(2,1);
        gtest.addEdge(0,4);
        gtest.addEdge(2,4);
        int[] edges = new int[5];
        for(int i = 0; i < 5; ++i){
            edges[i]=-1;
        }
        for (Edge e: gtest.getIncidentEdges(2)) {
            edges[e.getHead()] = 1;
        }
        assertTrue("3 e' un vicino di 2", edges[3] == 1); 
        assertTrue("0 non e' adiacente a 2", edges[0] == -1); 
    }
    

    
    
    @Test
    public void test060GetEdgesAndTail() { //verifica che gli archi restituiti da getIncidentEdges abbiano la "tail" corretta
        gtest = new UndirectedGraph(4);
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
    public void test070AddWithWeight() {   //verifica che il peso di un arco sia gestito correttamente da addEdge e getIncidentEdges
        gtest = new UndirectedGraph(5);
        gtest.addEdge(1,3,2);
        gtest.addEdge(2,1,-4);
        Edge e = gtest.getIncidentEdges(2).iterator().next();
        assertTrue("Il peso dell'arco (2,1) e' -4", e.getWeight() == -4);
    }

    @Test
    public void test080GetEdgesWithTail() { //verifica che gli archi restituiti da getIncidentEdges abbiano la "tail" corretta
        gtest = new UndirectedGraph(4);
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
  public void test050Remove() {  //verifica che il metodo removeEdge(int i,int j) elimini l'arco (i,j)
      gtest = new UndirectedGraph(5);
      gtest.addEdge(1,3);
      gtest.addEdge(2,1);
      gtest.addEdge(0,4);
      ((UndirectedGraph) gtest).removeEdge(1,3);
      boolean notFound = true;
      for (Edge e:  gtest.getIncidentEdges(1)) {
          notFound = (e.getHead() != 3);
      }
      assertTrue("3 non e' adiacente a 1", notFound);
  } 
  @Test
  public void test054RemoveCount() {  //verifica che removeEdge(int,int) aggiorni correttamente il numero di archi
  									//quando l'arco da cancellare esiste
      gtest = new UndirectedGraph(5);
      gtest.addEdge(1,3);
      gtest.addEdge(2,1);
      gtest.addEdge(0,4);
      ((UndirectedGraph) gtest).removeEdge(1,3);
      assertTrue("Il grafo ha solo 2 archi.", gtest.getEdgeNum() == 2 );
  }
  
  
  @Test
  public void test056RemoveNothingCount() {  //verifica che removeEdge(int,int) aggiorni correttamente il numero di archi
  										//quando l'arco da cancellare non esiste
      gtest = new UndirectedGraph(5);
      gtest.addEdge(1,3);
      gtest.addEdge(2,1);
      gtest.addEdge(0,4);
      ((UndirectedGraph) gtest).removeEdge(1,4);
      assertTrue("Il grafo ha 3 archi.", gtest.getEdgeNum() == 3 );
  }
  
}
