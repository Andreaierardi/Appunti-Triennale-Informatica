//<Andrea, Ierardi, 20018785>

// global variables
let nearby =[];
let CellaVuota = null;
let ShuffleFlag = 0;
// constant
let NUMCELL = 16;


init();

/* INIT
Funzione di init per l'inizializzazione del div relativo al messaggio di vittoria,
inizializzazione dei background di ogni casella
*/
function init()
{

    //Set della scritta di vittoria e del pulsante NEW GAME
    let node = document.createElement("DIV");
    node.id = "wins";

    let text = document.createElement("DIV");
    text.id = "victory";

    text.innerHTML = "<p> YOU WIN!!</p>";
    text.style.color = "#FFFFFF";
    text.style.fontFamily = "Arial";
    text.style.fontSize = "35px";
    text.style.fontWeight ="bold";
    text.style.margin = "auto";
    text.style.marginBottom = "10px";
    text.style.marginTop = "10px";
    text.style.textAlign = "center";
    text.style.width = "200px";
    text.style.fontSize = "50 px";
    text.style.border = "1px groove blue";
    text.style.background = "darkturquoise";

    let ng = document.createElement("BUTTON");
    ng.id = "newgame";
    ng.innerHTML= "NEW GAME";

    node.appendChild(text);
    node.appendChild(ng);
    document.getElementById("controls").appendChild(node);

    //Nascondo il nodo creato che mostra la vittoria
    hide(node);

    //Creo un array in cui salvo i valori del background per ogni cella
    let posizioni = [];
    for(let i= 0; i<4; i++)
    {
        for(let j= 0; j<4; j++)
        {
            posizioni.push(j*(-100)+"px "+i*(-100)+"px");
        }
    }

    //Setto i valori del background di ogni cella
    for(let i= 0; i<NUMCELL; i++)
    {
        let x  = document.getElementById("c"+(i+1));
        x.style.backgroundPosition = posizioni[i];
    }
    document.getElementById("c16").innerHTML="";


}

/* hide(x)
Funzione che rende non visibile il messaggio di vittoria oppure shuffle quando viene richiesto il NEWGAME
*/
function hide(x)
{
    x.style.display = "none";
}

/* show(x)
Idem per hide, in questo caso mostra il contenuto.
*/
function show(x)
{
    x.style.display = "inline";
}

/* start()
Il cuore del programma: ad ogni move (che avviene in activateEvents),
ricerca i vicini della cella vuota e, in caso non sia in modalità "shuffle",
attiva gli eventi sulle caselle e controlla se si è in uno 'state' di vittoria
*/

function start()
{

   nearby = nearbyCell();
   //Se sono in modalità shuffle, allora non attivo eventi e non controllo la soluzione
   if(!ShuffleFlag)
   {
       activateEvents();
       if(checksolution())
           wins();

   }
}

/* wins()
Se siamo in condizione di vittoria (checksolution()), allora fa apparire il
messaggio di vittoria, nasconde il pulsante di shuffle, rimuove tutti gli eventi
(in modo che non si possano spostare pedine) e mostra il pulsante NEW GAME.
Click su NEW GAME ripristina lo stato iniziale del programma
*/
function wins()
{

    let shufflebutton = document.getElementById("shufflebutton");
    hide(shufflebutton);

    let wins = document.getElementById("wins");
    show(wins);

    removeAllEvents();

    let newgame =  document.getElementById("newgame");

    newgame.onclick = function()
    {
        hide(wins);
        show(shufflebutton);
    }

}

/* activateEvents()
Attiva tutti gli eventi per le caselle vicine alla casella vuota:
Colore dei bordi evidenziato di rosso in mouseover
Colore dei bordi nero in mouseout
Esegue una mossa in caso venga cliccata la casella
*/
function activateEvents()
{
    for(let i = 0 ; i< nearby.length; i++)
    {

          let x = document.getElementById('c'+nearby[i]);
          x.onmouseover= function() { highlightCell(x); };
          x.onmouseout = function() { resetCell(x) };
          x.onclick = function() { mouve(x); }
    }
}

/* removeAllEvents()
Rimuove tuti gli eventi di click e colore per i vicini della casella vuota
(questo avviene dopo una mossa o in caso di vittoria)
*/
function removeAllEvents()
{
    for(let i = 0 ; i< nearby.length; i++)
    {
        let x = document.getElementById('c'+nearby[i]);
        x.onmouseover= function() { };
        x.onmouseout = function() { };
        x.onclick = function(){};
    }
}

/* mouve(elem)
Viene eseguita la mossa per elem.
Vengono scambiati tutti i valori delle caselle
per effettuare l'effettivo spostamento da elem a casella vuota
*/
function mouve(elem)
{
    //Vengono resettati tutti gli eventi
    removeAllEvents()

    //Scambio dei valori delle celle
    let cell = elem;
    let empty = emptyCell();

    let tmp = {style: cell.style.cssText, innetHTML: cell.innerHTML};

    cell.style.cssText = empty.style.cssText;
    cell.innerHTML = empty.innerHTML;

    empty.style.cssText = tmp.style;
    empty.innerHTML = tmp.innetHTML;

    //Reset dei colori dopo lo scambio
    resetCell(cell);
    resetCell(empty);

    //Aggiornato il valore della cella vuota
    CellaVuota = cell;

    //Rieseguo il ciclo di start() per effettuare nuove mosse o
    //controllare se si è in una condizione di vittoria
    start();
}

/* highlightCell(x)
Colora di rosso i bordi e il numero nella cella
*/
function highlightCell(cella)
{
    cella.style.border = "5px solid red";
    cella.style.color = "red";
}
/* resetCell(cella)
Reset del colore della cella
*/
function resetCell(cella)
{
    cella.style.border= "5px solid black";
    cella.style.color= "black";
}

/* nearbyCell(x)
Funzione che ricerca i vicini della cella vuota.
In primo luogo, trova la cella vuota con la funzione emptyCell.
Se il valore di CellaVuota è già stato aggiornato, allora procede a ricavarne l'id.
Dal CellaVuota otteniene l'id dei vicini di riga e colonna e li aggiunge in un array list
*/
function nearbyCell()
{
    nearby = [];
    if(CellaVuota==null)
    {       //Rimuove il carattere "c" per ottenere solo il numero dell'id
       var id = parseInt(emptyCell().id.replace("c",""));
       CellaVuota = id;
    }
    else
    {
        var id = parseInt(CellaVuota.id.replace("c",""));
    }
    let list= new Array();

    //Ottiene colonna e riga della cella
    let row = getRow(id);
    let col = getCol(id);

    //Se ci si trova nella prima riga otterremo solo id di celle al di sotto
    if(row==1)
        list.push(id+4);
    //Se ci si trova nell'ultima riga si aggiungo solo id di celle al di sopra
    else if(row==4)
        list.push(id-4);
    //Altrimenti aggiungo celle sopra e sotto
    else
    {
        list.push(id-4);
        list.push(id+4);

    }
    //Se ci si trova nella prima colonna, aggiungo solo id a destra
    if(col==1)
        list.push(id+1);

    //Se ci si trova nell'ultima colonna, aggiungo solo id a sinistra
    else if(col==4)
        list.push(id-1);
    //Altrimenti aggiungo id a destra e sinistra
    else
    {
        list.push(id-1);
        list.push(id+1);
    }
    //Ritorno la lista dei vicini
    return list;


}
/* getRow(x)
Ottiene la riga dato l'id della cella
*/
function getRow(n)
{
    if(n<=4)
        return 1;
    else if(n>4 && n<=8)
        return 2;
    else if(n>8 && n<=12)
        return 3;
    else
        return 4;
}
/* getCol(x)
Ottiene la colonna dato l'id della cella
*/
function getCol(n)
{
    return (n-1)%4+1;
}


/* emptyCell()
Scorre tutte le celle e ritorna la cella vuota
*/
function emptyCell()
{
    for(let i = 1; i<= NUMCELL; i++)
    {
       let cell = document.getElementById("c"+i);
       if(cell.innerHTML == "")
           return cell;
    }

}


/* shuffle()
Funzione di mescolamento che tiene traccia degli spostamenti precedenti
*/
function shuffle() {

        //ShuffleFlag settato a 1, serve alla funzione di start() per poter svolgere le mosse senza controllare la soluzione e senza attivare gli eventi.
    ShuffleFlag=1;
    let i =0 ;
        //precCell tiene traccia della cella mossa precedentemente
    let precCell=document.getElementById("c1");

    while(i<30)
    {
        //Estraggo da nearby una posizione random per ottenere un elemento casuale
        nearby = nearbyCell();
        let n = nearby.length;
        let index = random(n);
        let elem = document.getElementById("c"+nearby[index]);

            //Controllo che il numero estratto non sia uguale al precedente
        if(precCell.innerHTML!= elem.innerHTML)
        {
            //precCell impostato ad empty poichè è il valore che avrà elem dopo lo spostamento
            precCell = emptyCell();
	   // console.log(elem.innerHTML); STAMPA DELLE MOSSE
            mouve(elem);

        }
            //Se riestraggo il numero, lo tolgo da nearby e ne estraggo un altro
        else
        {
            nearby.splice(index,1);
            index = random(nearby.length);
            elem = document.getElementById("c"+nearby[index]);
            precCell= emptyCell();
			   
	// console.log(elem.innerHTML); STAMPA DELLE MOSSE
            mouve(elem);
        }
        i++;
    }

    //Se con gli spostamenti casuali ottengo uno stato di vittoria, allora mescolo di nuovo
    if(checksolution())
        shuffle();

    //Resetto flag a 0 poichè ho finito il mescolamento e faccio partire start()
    ShuffleFlag=0;
    start();
}

/* random(n)
Ottiene un numero random da 0 a n
*/
function random(n)
{
    return Math.floor(Math.random()*n);
}


/* checksolution()
Scorre tutte le celle e se i numeri che trova sono in ordine da 1 a 15 ritorna true, altrimenti ferma prima il ciclo e ritorna false
*/
function checksolution()
{
    for(let i =1  ; i<NUMCELL; i++)
        {
            let x = document.getElementById("c"+i);
            if(x.innerHTML != i)
                return false;
        }
    return true;
}
