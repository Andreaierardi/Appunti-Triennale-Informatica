/*Query 1:

Contare il numero di lingue in cui le release contenute nel database sono scritte ( il risultato deve contenere soltanto il numero delle lingue, rinominato “numero_lingue”).


- Versione 1*/

SELECT COUNT (DISTINCT(release.language)) AS Numero_Lingue
FROM release
/*
Per la realizzazione della query ci siamo serviti della tabella release che contiene un attributo language che contiene gli identificatori univoci delle lingue (foreign key), questo riferimento ammette valori nulli
In language troviamo un ID che non può essere nullo ed è una sequenza di valori incrementali (identificatore surrogato) questo ID è una foreign key in release, questo riferimento ammette valori nulli.
Per contare il numero di lingue si è reso necessario trovare tutte le occorrenze degli ID delle lingue nei record poi scartando i doppioni con la DISTINCT è stato utilizzato l’operatore COUNT per contare le occorrenze e poi è stato rinominato il campo.
E’ importante notare che nonostante la supposizione che ogni release abbia una lingua associata, alcune release risultano non associate ad alcuna lingua. Per lo più in language esistono alcune “false lingue” come [multiple languages].


Query per controllare il risultato:*/

SELECT DISTINCT release.language
FROM  release 
/*
In questo modo vediamo quali sono gli identificatori delle lingue presenti nelle release ( sono 6 + null)
 	 	
Query 2:

Elencare gli artisti che hanno cantato canzoni in italiano (il risultato deve contenere il nome dell’artista e il nome della lingua).


- Versione 1*/

SELECT distinct artist.name , language.name
FROM language
JOIN release ON release.language = language.id
JOIN artist_credit ON artist_credit.id = release.artist_credit
JOIN artist_credit_name ON artist_credit.id = artist_credit_name.artist_credit
JOIN artist ON artist_credit_name.artist_credit= artist.id
WHERE language.name = 'Italian'




/*

Le tabelle che vengono usate in questa query sono artist, artist_credit,artist_credit_name, language e release.
Partendo dalla tabella language, si effettuano due JOIN.
Il primo su release, mettendo come condizione il fatto che release.language (FK di release) sia uguale a language.id ( il riferimento a language di release ammette valori NULL).
La seconda su artist_credit, e ha come condizione che artist_credit.id sia uguale a release.artist_credit (FK di release).
Il terzo e il quarto mettono in relazione l’artista con l’artista accreditato a tale release.
La condizione del WHERE è che il campo language.name sia uguale a Italian.
Per trovare gli artisti che cantano in Italiano abbiamo controllato nella tabella language l'id corrispondente alla lingua 'Italian’, nel nostro caso otterremo 0 perchè non esistono release in lingua italiana.
E’ stato supposto che il riferimento ad artist_credit non fosse nullo e questo è stato confermato dalla stessa query, inoltre è stata utilizzata la keyword DISTINCT per non avere risultati doppi.

Query per controllare il risultato:*/

SELECT distinct artist.name , language.name
FROM language
JOIN release ON release.language = language.id
JOIN artist_credit ON artist_credit.id = release.artist_credit
JOIN artist_credit_name ON artist_credit.id = artist_credit_name.artist_credit
JOIN artist ON artist_credit_name.artist_credit= artist.id
/*
Utilizzata per verificare se esistono release in lingua italiana
*/

SELECT distinct artist.name , language.name
FROM language
JOIN release ON release.language = language.id
JOIN artist_credit ON artist_credit.id = release.artist_credit
JOIN artist_credit_name ON artist_credit.id = artist_credit_name.artist_credit
JOIN artist ON artist_credit_name.artist_credit= artist.id
WHERE language.name = 'Spanish'

/*
Utilizzando una lingua diversa da Italian la query restituisce dei risultati.


Query 3: 

Elencare le release di cui non si conosce la lingua (il risultato deve contenere soltanto il nome della release).
Abbiamo esaminato la tabella riguardante le release e abbiamo individuato l’identificatore della lingua nella tabella delle release. 




- Versione 1*/

SELECT  release.name
FROM release
WHERE release.language IS NULL

/*Per la realizzazione della query ci siamo serviti della tabella release che contiene un attributo name  che specifica il nome della lingua. In particolare viene richiesto di elencare le release in cui non si conosce la lingua. Quindi se non si conosce la lingua il valore è impostato a NULL. In questo caso non vengono utilizzate chiavi primarie, però viene utilizzata la chiave esterna language. Per la semplicità della query non si è reso necessario spezzarla in sottoquery più semplici. Si presume che la chiave esterna language possa assumere valori nulli.

Query per controllare il risultato:*/

SELECT * 
FROM release;
/*
oppure più specificatamente*/

SELECT release.name, release.language
FROM release
/*
Dopodichè si è verificato che effettivamente quelle release avessero effettivamente il campo lingua a NULL.
*/

/*
Query 4:
Elencare le release che nel nome hanno la parola “love”, in qualsiasi posizione (quindi anche in prima posizione; il risultato deve contenere soltanto il nome della release).

- Versione 1*/

SELECT release.name
FROM release
WHERE lower(name) LIKE LOWER('%love%')
/*
Per la realizzazione della query viene presa in considerazione solo la tabella “release” con l’attributo “name”.
Viene supposto che i titoli delle release possano contenere caratteri minuscoli e maiuscoli nella parola “love”, per questo motivo al fine di ovviare il problema viene posto trasformato tutto il titolo in minuscolo.
Non è stato necessario in questo caso affrontare sottoproblemi più semplici.

Query per controllare il risultato:*/

SELECT COUNT(release.name)
FROM release
WHERE lower(name) LIKE LOWER('%love%')

/*
Vengono contate le occorrenze della parola love all’interno del titolo

Query 5:

Elencare tutti gli pseudonimi di Prince con il loro tipo, se disponibile (il risultato deve contenere lo pseudonimo dell'artista, il nome (cioè Prince) ed il tipo di pseudonimo).

- Versione 1*/

	SELECT artist.name, artist_alias.name, artist_alias.type AS tipo_pseudo
	FROM artist
	JOIN artist_alias ON artist.id = artist_alias.artist
	LEFT JOIN artist_alias_type ON artist_alias_type.id=artist_alias.type
	WHERE artist.name = 'Prince'
/*
Le tabelle prese in considerazione sono artist, artist_alias e artist_alias_type. Partendo dalla tabella artist, viene fatto il primo JOIN su artist_alias, legato ad artist tramite la FK artist_alias.artist.
Il secondo LEFT JOIN è tra artist_alias e artist_alias_type (PK artist_alias_type.id) è importante che questo sia un left join poichè se per una riga della tabella di sinistra non ci sono righe della tabella di destra per cui la clausola è vera , nel risultato i valori corrispondenti agli attributi della tabella di destra avranno valore nullo. 
La condizione del WHERE è che il campo name di artist sia uguale a ‘Prince’. Viene restituito il nome dell’artista, l’alias e di che tipo è lo pseudonimo.
È stato supposto che un artista posso anche non avere alias anche se non è il nostro caso e inoltre si assume che alcuni alias possono assumere valore nullo.
Sono state prese in considerazioni query parziali, che escludevano dall'interrogazioni alcune condizioni (abbiamo escluso il tipo dell'alias e il nome dell'artista) così si è potuto verificare quali fossero i tipi di alias e contare gli elementi presenti nella tabella.


Query per controllare il risultato:
*/
	SELECT artist.name, artist_alias.name, artist_alias.type AS tipo_pseudo
	FROM artist
	JOIN artist_alias ON artist.id = artist_alias.artist
	LEFT JOIN artist_alias_type ON artist_alias_type.id=artist_alias.type
/*
Tramite questa query andrò a contare manualmente quante occorrenze di alias trovo riguardanti l’artista Prince


Query 6:
Elencare le release di gruppi inglesi ancora in attività (il risultato deve contenere il nome del gruppo e il nome della release e essere ordinato per nome del gruppo e nome della release)

-Versione 1 
*/
SELECT DISTINCT artist.name, release.name
FROM artist
JOIN artist_credit_name ON artist.id= artist_credit_name.artist
JOIN artist_credit ON artist_credit_name.artist = artist_credit.id
JOIN release ON artist_credit.id = release.artist_credit
JOIN area ON artist.area = area.id 
JOIN artist_type ON artist_type.id =artist.type
WHERE artist_type.name= 'Group' AND area.name = 'United Kingdom'  AND artist.end_date_year IS NULL
ORDER BY artist.name ASC, release.name ASC


/*
Nella realizzazione di questa query vengono prese in considerazione le tabelle release, artist_credit, artist_credit_name,artist,artist_type e area.
L’ID dell’artista in questo caso è la primary key che viene messa in join con artist_credit_name.artist (Foreign key).
L’attributo area (FK) della tabella “artist” può assumere valori NULL
Il tipo di artista (FK) non contiene valori NULL 
VIene fatto:
un JOIN su artist_credit_name per collegare artist alla release tramite la sua primary key alla FK di artist_credit_name
un JOIN su su artist_credit per collegare artist_credit_name ad artist_credit tramite la PK di artist_credit e la FK di artist_credit_name
un JOIN su area e artist per conoscere il nome dell’area dato l’identificatore della FK
un JOIN su release per collegare la tabella ad artist_credit tramite FK
un JOIN su artist_type per sapere se l’artista è un gruppo.
L’attributo name della tabella area contiene, oltre ai nomi delle aree geografiche anche delle “false-aree” come ad esempio [at sea] oppure [world wide].
Possiamo vedere questa query suddivisa in 3 sottoproblemi principali:

Le join fra le tabelle per collegare tutti i record
Le condizioni definite nella WHERE come ad esempio l’area geografica = “united kingdom” e che artist.end_date_year sia nullo ( ovvero sia ancora in attività)
Ordinare i risultati con la ORDER BY ( ascendente nel nostro caso) 



Query per controllare il risultato:

*/
 
   
   SELECT artist.name
   FROM artist
   JOIN area ON artist.area = area.id
   WHERE area.name = 'United Kingdom';
/*
   Query per controllare la provenienza degli artisti
*/

      
   SELECT name
   FROM artist
   WHERE artist.end_date_year IS NULL;
/*
Query per controllare che l’artista sia ancora in attività
*/

   SELECT artist.name
   FROM artist
   JOIN artist_type ON artist_type.id = artist.type
   WHERE artist_type.name = 'Group';
/*
Query per controllare gli artisti che sono gruppi



NB:
Quando viene eseguita la query si può notare che esistono nomi di release duplicati, questo succede perché ci sono diverse release con lo stesso nome, infatti queste hanno tutte ID differente


Query 7:
Trovare le release in cui il nome dell’artista è diverso dal nome accreditato nella release (il risultato deve contenere il nome della release, il nome dell’artista accreditato (cioè artist_credit.name) e il nome dell’artista (cioè artist.name)) 


-Versione 1

*/

  SELECT release.name, artist_credit.name, artist.name
  FROM artist_credit_name
  JOIN artist ON artist_credit_name.artist = artist.id
  JOIN artist_credit ON artist_credit_name.artist_credit = artist_credit.id
  JOIN release ON release.artist_credit = artist_credit.id
  WHERE artist_credit.name <> artist.name;
/*
Le tabelle prese in considerazione sono artist la cui PK è ID,artist_credit la cui PK è ID,artist_credit_name la cui (PK,FK) è ID ( la FK si riferisce a ID di artist_credit) e release che ha come FK artist_credit. E’ stato assunto inizialmente e poi successivamente controllato, che non i valori selezionati non possano essere nulli.

Query per controllare il risultato:



-Versione 2
*/
  SELECT release.name, artist_credit.name, artist.name
  FROM artist_credit_name
  JOIN artist ON artist_credit_name.artist = artist.id
  JOIN artist_credit ON artist_credit_name.artist_credit = artist_credit.id
  JOIN release ON release.artist_credit = artist_credit.id

  EXCEPT 
  
  SELECT release.name, artist_credit.name, artist.name
  FROM artist_credit_name
  JOIN artist ON artist_credit_name.artist = artist.id
  JOIN artist_credit ON artist_credit_name.artist_credit = artist_credit.id
  JOIN release ON release.artist_credit = artist_credit.id
  WHERE artist_credit.name = artist.name;
 /*
In questo caso è analoga alla precedente ma non vengono ripetuti i doppioni e si usa l’operatore insiemistico EXCEPT



Query 8:
Trovare gli artisti con meno di tre release (il risultato deve contenere il nome dell’artista ed il numero di release).

- Versione 1
*/
SELECT artist.name, COUNT(release.id) 
FROM release
RIGHT JOIN artist_credit ON artist_credit.id = release.artist_credit
JOIN artist_credit_name ON artist_credit_name.artist_credit =  artist_credit.id
JOIN artist ON artist.id = artist_credit_name.artist
GROUP BY artist.name HAVING COUNT(release.id)<3 
ORDER BY COUNT(release.id) DESC;




/* Le tabelle prese in considerazione sono release, artist_credit , artist_credit_name e artist. 
Le chiavi primarie utilizzate sono id nella tabella release, id nella tabella artist_credit , artist_credit nella tabella artist_credit_name e id nella tabella artist. L’unica chiave esterna utilizzata è artist_credit della tabella artist_credit_name. 
Attraverso una RIGHT JOIN si cerca di introdurre anche le release con id NULL in modo da poter essere contate. 
Nota: viene assunto che artist_credit.name non assuma valori nulli, per questo viene poi introdutta una query di controllo

Query per controllare il risultato:*/

   SELECT artist_credit.name, count(release)
   FROM release
   RIGHT JOIN artist_credit ON release.artist_credit = artist_credit.id
   JOIN artist_credit_name ON artist_credit.id = artist_credit_name.artist_credit
   JOIN artist ON artist.id = artist_credit_name.artist_credit
   GROUP BY artist_credit.name
ORDER BY COUNT(release) ASC
/*
Ovviamente riferendosi alla query precedente si è potuto notare(ordinandoli in ordine crescente) effettivamente quali fossero gli artisti con meno di 3 release



*/
   SELECT * FROM
   artist_credit
   WHERE artist_credit.name IS null;
/*   
query di controllo per verificare se esiste un record della tabella artist_credit il cui attributo artist_credit.name sia nullo. 



Query 9:

- Versione 1

Trovare la registrazione più lunga di una artista donna (il risultato deve contenere il nome della registrazione, la sua durata in minuti e il nome della artista; tenere conto che le durate sono memorizzate in millesimi di secondo) (scrivere due versioni della query con e senza operatore aggregato MAX).
Le tabelle prese in considerazione per questa query sono artist, artist_credit_name, artist_credit, recording. Partendo dalla tabella artist, come prima cosa abbiamo fatto una serie di JOIN che uniscono artist con recording (passando obbligatoriamente per le tabelle artist_credit_name e artist_credit). Artist e artist_credit_name son legati tramite gli attributi artist.id (PK di artist) e artist_credit_name.artist_credit ( PK e FK di 	artist_credit_name). Artist_credit_name e artist_credit son legati tramite gli attributi artist_credit_name.artist (FK di artist_credit_name) e artist_credit.id (PK di artist_credit). Artist_credit e recording son legati dagli attributi artist_credit.id(PK di artist_credit) e recording.artist_credit(FK di recording). Finita questa serie di JOIN nel where abbiamo inserito il ritorno del MAX di recording.lenght, MAX trovato tramite la medesima serie di 	JOIN ma al contrario cioè partendo da recording per terminare in artist, la condizione WHERE del calcolo del MAX contiene artist.gender = 2 che sta a significare artista donna siamo andati a controllare nella tabella gender i name incrociando i risultati con il campo artist_gender abbiamo preferito inserire l'intero 2 piuttosto che eseguire una ulteriore join e inserire gender.name='Female' questo per snellire un po' la query. recording.length è diviso  60000 per permetterci di restituire il risultato in minuti dato che nel database esso è salvato in millisecondi. Per controllare la correttezza del risultato abbiamo controllato che nella tabella release non ci fossero altre release più lunghe di quella restituita dalla nostra query. In caso ci fossero state, ci siamo accertati del fatto che queste release più lunghe non appartengano ad artisti donne. 
*/
	SELECT artist.name, recording.name, (recording.length/60000)
	FROM artist
           JOIN artist_credit_name ON artist_credit_name.artist=artist.id
	JOIN artist_credit ON artist_credit_name.artist_credit=artist_credit.id
	JOIN recording on artist_credit.id=recording.artist_credit
	WHERE recording.length=(SELECT MAX(recording.length)
	FROM recording 
        	JOIN artist_credit ON artist_credit.id=recording.artist_credit
        	JOIN artist_credit_name ON artist_credit_name.artist_credit=artist_credit.id
        	JOIN artist ON artist_credit_name.artist=artist.id
	WHERE artist.gender=2)

/*
- Versione2
La seconda versione di questa mantiene gran parte della prima che trovo inutile andare a commentare la sostanziale differenza sta	nell'utilizzo di ALL invece che l'operatore aggregato MAX e la variazione dei due WHERE essi non sono più singoli ma contengono due dichiarazioni l'uno il più interno controlla che il sesso dell'artista sia corretto e che la lunghezza non sia nulla mentre il secondo WHERE quello più esterno controlla sempre che il sesso sia giusto e che la lunghezza sia >= di tutte le lunghezze estratte nella subquery.*/
 	SELECT artist.name, recording.name, (recording.length/60000)
	FROM artist
	JOIN artist_credit_name ON artist_credit_name.artist=artist.id
	JOIN artist_credit ON artist_credit_name.artist_credit=artist_credit.id
	JOIN recording ON artist_credit.id=recording.artist_credit
	WHERE artist.gender=2 AND recording.length>=ALL(SELECT recording.length 
							 FROM recording
        			                         JOIN artist_credit ON artist_credit.id=recording.artist_credit
       				 	                 JOIN artist_credit_name ON artist_credit_name.artist_credit=artist_credit.id
        	                 			 JOIN artist ON artist_credit_name.artist=artist.id
                             				 WHERE length is not null AND artist.gender=2)

/*
Query 10 

- Versione 1
Elencare le lingue a cui non corrisponde nessuna release (il risultato deve contenere il nome della lingua, il numero di release in quella lingua e essere ordinato per Lingua) (scrivere due versioni della query). Le tabelle prese in considerazione sono language e release. Nella prima parte della query (prima dell'EXCEPT) selezioniamo tutte le lingue e le release in quelle lingue. Nella seconda parte, facciamo la stessa selezione nella subquery, al di fuori facciamo una JOIN sulla tabella language in modo che release.language = language.id. Al risultato della prima parte sottraiamo il risultato della seconda parte. In questo modo otteniamo tutte le lingue a cui non corrisponde nessuna release. Non usiamo nessun operatore insiemistico. Per verificare, abbiamo guardato che in release.language non fosse l'id delle lingue restituite nel risultato.*/

	SELECT  language.name, (
  		SELECT count(release.id) NRelease
       		FROM release
       		WHERE release.language=language.id)
	FROM language
	EXCEPT
   	SELECT language.name , (
        	SELECT count(release.id) NRelease
        	FROM release
        	WHERE release.language=language.id)
	FROM release
	JOIN language ON release.language = language.id
        ORDER by name ASC




/*
- Versione 2
Per la seconda versione, abbiamo utilizzato il WHERE NOT EXISTS, la struttura è la medesima.*/  

	SELECT language.name, (
      	  	SELECT count(release.id) NRelease
      	  	FROM release
      	  	WHERE release.language=language.id)
	FROM language
	WHERE NOT EXISTS(
		SELECT release.language
		FROM release
		WHERE release.language = language.id)
        ORDER by name ASC

/*
Query 11:
Ricavare la seconda registrazione per lunghezza di un artista uomo (il risultato deve comprendere l’artista accreditato, il nome della registrazione e la sua lunghezza) (scrivere due versioni della query; almeno una delle due versioni non deve utilizzare le viste).


- Versione 1	

Ricavare la seconda registrazione per lunghezza (il risultato deve comprendere l'artista accreditato, il 	nome della registrazione e la sua lunghezza) (scrivere due versioni della query). Per questa query siamo abbiamo iniziato facendo una serie di JOIN partendo da artist per arrivare in recording (passando tra artist_credit_name e artist_credit) 
la prima JOIN è stata quella tra artist e artist_credit_name sugli attributi artist.id (PK di artist) e artist_credit_name.artist (FK di artist_credit_name) 
la seconda JOIN è stata quella con artist_credit tramite gli attributi artist_credit_name.artist_credit(PK e FK di artist_credit_name) e artist_credit.id(PK di artist_credit), 
l'ultima JOIN è stata quella su recording tramite gli attributi recording.artist_credit(FK di recording) e artist_credit.id(PK di artist_credit). 
Nel WHERE siamo riusciti ad estratte la seconda lunghezza massima selezionando la lunghezza massima < della lunghezza massima questo è stato possibile grazie allo svolgimentento delle query 
partendo dall'interno l'ultima select MAX , quella più interna, è la prima che seleziona quindi selezione il reale massimo la seconda è costretta a selezionare il massimo escludendo il primo dato che deve essere minore 
quindi ci ritorna esattamente ciò che volevamo cioè il secondo massimo. recording.length è diviso 60000 per portare la lunghezza in minuti. Per verificarne la correttezza, abbiamo usato questa query */

SELECT artist.name, recording.name, (recording.length/60000)
	FROM artist
           JOIN artist_credit_name ON artist_credit_name.artist=artist.id
	JOIN artist_credit ON artist_credit_name.artist_credit=artist_credit.id
	JOIN recording on artist_credit.id=recording.artist_credit
	WHERE recording.length=(SELECT MAX(recording.length)FROM recording 
        	                JOIN artist_credit ON artist_credit.id=recording.artist_credit
        	                JOIN artist_credit_name ON artist_credit_name.artist_credit=artist_credit.id
        	                JOIN artist ON artist_credit_name.artist=artist.id
				WHERE length < (SELECT MAX(recording.length)
					FROM recording) AND  artist.gender=1)



/*- Versione 2
La seconda versione di questa query è stata possibile grazie agli operatori insiemistici in questo caso abbiamo usato EXCEPT. Nel WHERE abbiamo le condizioni che la lunghezza non sia nulla e che il recording.length sia il massimo dei recording.length ma preso da un insieme dove è stato escluso proprio con la EXCEPT il valore massimo quindi ciò che ci verra restituito è il secondo massimo per lunghezza.*/
SELECT artist_credit.name,
       recording.name,
       recording.length
FROM artist
JOIN gender ON artist.gender = gender.id
JOIN artist_credit_name ON artist.id = artist_credit_name.artist
JOIN artist_credit ON artist_credit_name.artist_credit = artist_credit.id
JOIN recording ON artist_credit.id = recording.artist_credit
WHERE recording.length IS NOT NULL AND gender.name = 'Male'
  AND recording.length =
    ( SELECT MAX(LENGTH)
     FROM
       ( SELECT recording.name AS recording,
                recording.length 
        FROM artist
        JOIN gender ON artist.gender = gender.id
        JOIN artist_credit_name ON artist.id = artist_credit_name.artist
        JOIN artist_credit ON artist_credit_name.artist_credit = artist_credit.id
        JOIN recording ON artist_credit.id = recording.artist_credit
        WHERE gender.name = 'Male'
        EXCEPT SELECT recording.name ,
                      recording.length
        FROM artist
        JOIN gender ON artist.gender = gender.id
        JOIN artist_credit_name ON artist.id = artist_credit_name.artist
        JOIN artist_credit ON artist_credit_name.artist_credit = artist_credit.id
        JOIN recording ON artist_credit.id = recording.artist_credit
        WHERE gender.name = 'Male'
          AND recording.length IN
            ( SELECT MAX(recording.length)
             FROM artist
             JOIN gender ON artist.gender = gender.id
             JOIN artist_credit_name ON artist.id = artist_credit_name.artist
             JOIN artist_credit ON artist_credit_name.artist_credit = artist_credit.id
             JOIN recording ON artist_credit.id = recording.artist_credit
             WHERE gender.name = 'Male' ) ) AS second );


/*Query di controllo:*/
		
	SELECT * from recording 
	WHERE length IS NOT NULL
	order by length desc 
/*
che restituisce le tuple della tabella release in ordine discendente in base alla release.length. Dopo di che abbiamo cercato la seconda registrazione, e ci siamo assicurati che l'artista corrisponda esattamente all'artista restituito dalla nostra query. */


/*
Query 12:

- Versione 1

Per ogni Stato esistente riportare la lunghezza totale delle registrazioni di artisti di quello Stato (il risultato deve comprendere il nome dello Stato e la lunghezza totale in minuti delle registrazioni (0 se lo Stato non ha registrazioni). (scrivere 	due versioni della query). 
Per risolvere la query abbiamo preso in considerazione le tabelle recording, artis_credit, artist_credit_name, artist e area. Partendo da recording, abbiamo fatto una prima JOIN su artist_credit,
dato che recording.artist_credit (FK di recording) e artist_credit.id (PK di artist_credit) sono collegati; artist_credit e artist_credit_name sono legate dagli attributi artist_credit_name.artist_credit e artist_credit.id (PK di artist_credit);
a sua volta artist_credit_name e artist sono legate dagli attributi artist.id e artist_credit_name.artist_credit (PK e FK di artist_credit_name); abbiamo poi deciso di fare un RIGHT JOIN tra artist e area, in modo da non perdere informazioni che potrebbero compromettere il risultato finale. La condizione del WHERE è che area.type deve essere uguale ad 1, ovvero lo Stato. Per poter ritornare un elenco di Stati con le rispettive lunghezze delle registrazioni, si è fatta una sum sull’attributo length di recording, a sua volta diviso per 60000 per ritornare la lunghezza in minuti. Abbiamo poi usato l’istruzione coalesce per poter ritornare il valore 0 al posto di NULL (casella vuota) per alcune somme di certi Stati. Il GROUP BY è stato usato per raggruppare ogni ennupla con lo stesso Stato.
*/
	SELECT area.name AS nome_area, coalesce((sum(length)/60000),0) AS lunghezza
	FROM recording
           JOIN artist_credit ON recording.artist_credit=artist_credit.id
	JOIN artist_credit_name ON artist_credit_name.artist_credit = artist_credit.id
	JOIN artist ON artist.id = artist_credit_name.artist
	RIGHT JOIN area ON artist.area = area.id 
	WHERE area.type = 1
        GROUP by area.name
/*
- Versione 2

La seconda versione della query abbiamo pensato di risolverla con una vista. L’elenco di istruzioni è il medesimo, ma vengono aggiunte un paio per la creazione e cancellazione della vista, ovvero CREATE VIEW e DROP VIEW.*/

	CREATE VIEW query12 as
	SELECT area.name, coalesce((sum(length)/60000),0)
	FROM recording
 	JOIN artist_credit ON recording.artist_credit=artist_credit.id
	JOIN artist_credit_name ON artist_credit_name.artist_credit = artist_credit.id
	JOIN artist ON artist.id = artist_credit_name.artist
	RIGHT JOIN area ON artist.area = area.id 
	WHERE area.type = 1
    	GROUP by area.name;
    
	SELECT * from query12;

	--DROP VIEW query10;


/* Query di controllo: */


		SELECT area.name
		FROM area
		WHERE area.type = 1

/* restituisce tutti gli stati che hanno type = 1, cioè Country. La query restituisce 40 tuple, come quelle restituite dalla nostra query. I paesi, sono i medesimi. */

/*

Query 13:
Ricavare gli artisti britannici che hanno pubblicato almeno 10 release (il risultato deve contenere il
nome dell’artista, il nome dello stato (cioè United Kingdom) e il numero di release) (scrivere due
versioni della query; almeno una delle due versioni non deve utilizzare le viste).*/

/* Per la realizzazione di questa query vengono prese in considerazione le tabelle release,artist, area e artist_credit.
Viene fatto un join tra artist e artist credit tramite artist.id (PK) e release.artist_credit(FK)
Un join tra area e artist che ci serve per ricavare il nome dell'area associata all'ID dell'area sulla FK di artist.
L'unica condizione è che l'area sia l'inghilterra, viene inoltre raggruppato l'output della query controllando solo gli artisti con almeno 10 release.

*/

SELECT DISTINCT (artist.name), area.name, COUNT(*)
FROM release
JOIN artist ON artist.id=release.artist_credit
JOIN area ON area.id=artist.area
WHERE area.name='United Kingdom'
GROUP BY artist.name,area.name HAVING COUNT(*)>=10

--VERSIONE 2

CREATE VIEW test AS(
SELECT DISTINCT (artist.name) AS nome, area.name AS area , COUNT(*) AS conta
FROM release
JOIN artist ON artist.id=release.artist_credit
JOIN area ON area.id=artist.area
GROUP BY artist.name,area.name HAVING COUNT(*)>=10);

SELECT test.nome, test.area, test.conta
FROM test
WHERE test.area='United Kingdom'


/*Query di controllo: */

SELECT DISTINCT (artist.name), area.name, COUNT(*)
FROM release
JOIN artist ON artist.id=release.artist_credit
JOIN area ON area.id=artist.area
WHERE area.name='United Kingdom'
GROUP BY artist.name,area.name

/*

In questo modo ottengo tutti gli artisti inglesi, e verifico manualmente quali verificano la condizione di avere almeno 10 release pubblicate.


/*
Query 14:
Considerando il numero medio di tracce tra le release pubblicate su CD, ricavare gli artisti che hanno
pubblicato esclusivamente release con più tracce della media (il risultato deve contenere il nome
dell’artista e il numero di release ed essere ordinato per numero di release discendente) (scriver e due
versioni della query; almeno una delle due versioni non deve utilizzare le viste).

/* Vengono prese in considerazione le tabelle: artist,artist_credit,artist_credit_name,release,medium e medium_format.
Artist viene messo in join con artist_credit_name tramite artist.id(PK) e artist_credit_name.artist(FK
Artist_credit viene messo in join con artist_credit_name tramite artist_credit.id(PK) e artist_credit_name.artist_credit (PK,FK).
Release viene messo in join con artist_credit tramite release.artist_credit(FK) e artist_credit.Id (PK).
Medium viene messo in join con release tramite medium.release(FK) e release.id(PK)
medium_format viene messo in join con medium tramite medium.format (FK) e medium_format.ID (PK).
Per la prima versione viene utilizzato come sottoproblema una sottoquery che serve per ricavare la media tra tutte le tracce.
All'interno del WHERE viene specificata una sottoquery che va a ricercare gli artisti che hanno almeno una traccia che non è maggiore della media. 
In questo modo possiamo, tramite il "NOT IT"  garantire l'esclusività degli artisti che hanno solo release con più tracce della media.
Per filtrare i formati che usano CD è stata inserita una condizione nel where che va a fare il controllo tramite il nome sulla tabella medium_format. 
Viene poi raggruppato tutto per il nome dell'artista e ordinato in ordine decrescente sempre in base al nome dell'artista.

VERSIONE 1 senza viste
*/



SELECT art.name, Count(rel.id) AS n_cd
FROM artist art
JOIN artist_credit_name acn ON acn.artist = art.id
JOIN artist_credit ac ON ac.id = acn.artist_credit
JOIN release rel ON rel.artist_credit = ac.id
JOIN medium md ON md.release = rel.id
JOIN medium_format md_f ON md.format = md_f.id
WHERE md_f.name='CD'
  AND md.track_count >
    (SELECT AVG(track_count)
     FROM medium)
     AND art.name not in (

SELECT art.name
FROM artist art
JOIN artist_credit_name acn ON acn.artist = art.id
JOIN artist_credit ac ON ac.id = acn.artist_credit
JOIN release rel ON rel.artist_credit = ac.id
JOIN medium md ON md.release = rel.id
JOIN medium_format md_f ON md.format = md_f.id
WHERE md_f.name='CD'
  AND md.track_count <
    (SELECT AVG(track_count)
     FROM medium)
GROUP BY art.name
ORDER BY art.name DESC

     )
GROUP BY art.name
ORDER BY art.name DESC


--- versione  2 con utilizzo di viste

CREATE VIEW artists_with_release_over_median AS(

SELECT art.name, Count(rel.id) AS n_cd
FROM artist art
JOIN artist_credit_name acn ON acn.artist = art.id
JOIN artist_credit ac ON ac.id = acn.artist_credit
JOIN release rel ON rel.artist_credit = ac.id
JOIN medium md ON md.release = rel.id
JOIN medium_format md_f ON md.format = md_f.id
WHERE md_f.name='CD'
  AND md.track_count >
    (SELECT AVG(track_count)
     FROM medium)
     GROUP BY art.name
ORDER BY art.name DESC
);

CREATE VIEW artists_with_release_under_median AS(

SELECT art.name, Count(rel.id) AS n_cd
FROM artist art
JOIN artist_credit_name acn ON acn.artist = art.id
JOIN artist_credit ac ON ac.id = acn.artist_credit
JOIN release rel ON rel.artist_credit = ac.id
JOIN medium md ON md.release = rel.id
JOIN medium_format md_f ON md.format = md_f.id
WHERE md_f.name='CD'
  AND md.track_count <
    (SELECT AVG(track_count)
     FROM medium)
     GROUP BY art.name
ORDER BY art.name DESC
);

select * from artists_with_release_over_median where name not in (select name from artists_with_release_under_median);

/* In questo caso vengono utilizzate 2 viste, una per trovare gli artisti con release che hanno un numero di tracce sopra la media, una per trovare quelli che hanno un numero di tracce sotto la media
Infine viene preso il risultato della prima vista e messo in disgiunzione con quello della seconda vista, in questo modo, come detto precedentemente, viene garantita l'esclusività.
*/

/* Query di controllo:*/


SELECT art.name, md.track_count
FROM artist art
JOIN artist_credit_name acn ON acn.artist = art.id
JOIN artist_credit ac ON ac.id = acn.artist_credit
JOIN release rel ON rel.artist_credit = ac.id
JOIN medium md ON md.release = rel.id
JOIN medium_format md_f ON md.format = md_f.id
WHERE md_f.name='CD'
  AND md.track_count >
    (SELECT AVG(track_count)
     FROM medium)
     AND art.name not in (

SELECT art.name
FROM artist art
JOIN artist_credit_name acn ON acn.artist = art.id
JOIN artist_credit ac ON ac.id = acn.artist_credit
JOIN release rel ON rel.artist_credit = ac.id
JOIN medium md ON md.release = rel.id
JOIN medium_format md_f ON md.format = md_f.id
WHERE md_f.name='CD'
  AND md.track_count <
    (SELECT AVG(track_count)
     FROM medium)
GROUP BY art.name
ORDER BY art.name DESC

     )
GROUP BY art.name,md.track_count
ORDER BY art.name DESC

/*Grazie alla seguente query abbiamo effettivamente veficato che il numero delle track dei CD degli artisti è effettivamente maggiore della media*/

/*
Query 15:

Ricavare il primo artista morto dopo Louis Armstrong (il risultato deve contenere il nome dell’artista, la
sua data di nascita e la sua data di morte) (scrivere due versioni della query; almeno una delle due
versioni non deve utilizzare le viste).

In questa query viene presa in consideraziona unicamente la tabella artist.
Inizialmente viene assunto che nel database le date siano sempre specificate come giorno-mese-anno, in realtà con la query di controllo si può notare che questi valori possono essere NULL.
Nella prima versione viene messa una condizione che serve per andare a trovare l'anno di nascita minore, andando a filtrare i risultati basandoci su quelli di Louis Armstrong.
Viene quindi creata una sottoquery che va a cercare tutti gli aristi con l'anno immediatamente maggiore o uguale a quello di armstrong, poi il mese e il giorno dopodichè prende il minimo della tabella risultante.
*/

/* Versione pulita che utilizza le stringhe */

SELECT name,
       begin_date_year || '/' || begin_date_month || '/' || begin_date_day birth,
       end_date_year || '/' || end_date_month || '/' || end_date_day death
FROM artist
WHERE end_date_year || '/' || end_date_month || '/' || end_date_day =
    (SELECT MIN(end_date_year || '/' || end_date_month || '/' || end_date_day)
     FROM artist
     WHERE end_date_year || '/' || end_date_month || '/' || end_date_day >
         (SELECT end_date_year || '/' || end_date_month || '/' || end_date_day FROM artist WHERE name = 'Louis Armstrong'))

-- versione con le viste

CREATE VIEW end_arm AS
(SELECT end_date_year || '/' || end_date_month || '/' || end_date_day FROM artist WHERE name = 'Louis Armstrong');

SELECT name,
       begin_date_year || '/' || begin_date_month || '/' || begin_date_day birth,
       end_date_year || '/' || end_date_month || '/' || end_date_day death
FROM artist
WHERE end_date_year || '/' || end_date_month || '/' || end_date_day =
    (SELECT MIN(end_date_year || '/' || end_date_month || '/' || end_date_day)
     FROM artist
     WHERE end_date_year || '/' || end_date_month || '/' || end_date_day >
         (SELECT * from end_arm);
		  
/* Query di controllo */ 
SELECT artist.name,artist.end_date_year,artist.end_date_month,artist.end_date_day
FROM artist
ORDER BY artist.end_date_year

/* si è utilizzata questa query per verificare manualmente il primo artista morto dopo Louis Armstrong*/

/*
Query 16:

- Versione 1

Elencare le coppie di artisti che non hanno mai collaborato tra di loro ma hanno collaborato con un medesimo terzo artista in una release o in una registrazione (il risultato deve comprendere i nomi delle coppie di artisti e essere ordinato per i loro nomi) (scrivere due versioni della query).
Creiamo due viste identiche, dove c'è nella prima colonna l'artista in comune e nella seconda colonna tutti gli artisti con cui ha collaborato, riga per riga. Per creare questa vista facciamo 4 Join con le tabelle artist_credit e artist_credit_name rinominate per aver la possibilità di richiamarle nella condizione del WHERE impostiamo la differenza delle stringhe contenute nelle colonne con l'operatore "<" successivamente prendiamo in considerazione con la clausola HAVING solo gli artisti che hanno almeno collaborato con altri artisti. Create queste due viste eseguiamo una JOIN tra di esse riutilizzando la condizione vista precedentemente nel WHERE successivamente restituiamo il risultato ordinato per nome.*/
	
	CREATE VIEW prova AS( 
	SELECT artist_credit_name1.name AS col1 , artist_credit_name2.name AS col2
	FROM artist_credit_name 
	JOIN artist_credit artist_credit1 ON artist_credit_name.artist_credit=artist_credit1.id
	JOIN artist_credit artist_credit2 ON artist_credit1.id=artist_credit2.id
	JOIN artist_credit_name artist_credit_name1 ON artist_credit1.id=artist_credit_name1.artist_credit
	JOIN artist_credit_name artist_credit_name2 ON artist_credit2.id=artist_credit_name2.artist_credit
	WHERE artist_credit_name1.artist<artist_credit_name2.artist
	GROUP by artist_credit_name1.name, artist_credit_name2.name
	HAVING count(artist_credit1.artist_count)>=2
	ORDER by artist_credit_name1.name, artist_credit_name2.name);

	CREATE VIEW prova2 AS( 
	SELECT artist_credit_name1.name AS col1 , artist_credit_name2.name AS col2
	FROM artist_credit_name 
	JOIN artist_credit artist_credit1 ON artist_credit_name.artist_credit=artist_credit1.id
	JOIN artist_credit artist_credit2 ON artist_credit1.id=artist_credit2.id
	JOIN artist_credit_name artist_credit_name1 ON artist_credit1.id=artist_credit_name1.artist_credit
	JOIN artist_credit_name artist_credit_name2 ON artist_credit2.id=artist_credit_name2.artist_credit
	WHERE artist_credit_name1.artist<artist_credit_name2.artist
	GROUP by artist_credit_name1.name, artist_credit_name2.name
	HAVING count(artist_credit1.artist_count)>=2
	ORDER by artist_credit_name1.name, artist_credit_name2.name);

	SELECT DISTINCT prova.col2 ,prova2.col2 
	FROM prova
	JOIN prova2 ON prova.col1=prova2.col1
	WHERE prova.col2<prova2.col2
	ORDER by prova.col2,prova2.col2 ASC

	--drop view prova;
	--drop view prova2;



-- Versione 2
 	CREATE VIEW test AS(
	SELECT artist_credit_name1.name AS col1 , artist_credit_name2.name AS col2
	FROM artist_credit_name 
	JOIN artist_credit artist_credit1 ON artist_credit_name.artist_credit=artist_credit1.id
	JOIN artist_credit artist_credit2 ON artist_credit1.id=artist_credit2.id
	JOIN artist_credit_name artist_credit_name1 ON artist_credit1.id=artist_credit_name1.artist_credi
	JOIN artist_credit_name artist_credit_name2 ON artist_credit2.id=artist_credit_name2.artist_credit
	WHERE artist_credit_name1.artist<>artist_credit_name2.artist
	GROUP by artist_credit_name1.name, artist_credit_name2.name
	ORDER by artist_credit_name1.name, artist_credit_name2.name);
	
	CREATE VIEW test1 AS(
	SELECT DISTINCT test.col1 ,test.col2 
	FROM test
	JOIN prova3 ON test.col1=prova3.name);

	CREATE VIEW test2 AS(
	SELECT DISTINCT test.col1 ,test.col2 
	FROM test
	JOIN prova3 ON test.col1=prova3.name);

	SELECT DISTINCT test1.col2 ,test2.col2
	FROM test1
	JOIN test2 ON test1.col1=test2.col1
	WHERE test1.col2<test2.col2
	ORDER by test1.col2,test2.col2 ASC

	--drop view test cascade







/*
Query 17:


Trovare il nome e la lunghezza della traccia più lunga appartenente a una release rilasciata in almeno due paesi (il risultato deve contenere il nome della traccia e la sua lunghezza in secondi) (scrivere due versioni della query). Per la realizzazione di questa query ci siamo serviti di una vista, dal nome t1. Questa tabella t1 restituisce al suo interno le release che sono state rilasciate in più di un paese. Abbiamo utilizzato la tabella release_country. Con un count e un having count(release)>1 restituiamo in una colonna un intero che corrisponde al numero dei paesi in cui è stata rilasciata una certa release. Nella seconda parte della query abbiamo utilizzato la tabella precedentemente creata t1 per fare le tre JOIN che ci conducono alla tabella track, dove troviamo la lunghezza della traccia che ci interessa. Dopo di che selezioniamo il massimo tra le lunghezze di queste tracce, 	 dividendolo per 1000 per ottenere il risultato in secondi. Per controllare la correttezza della query ci siamo serviti della seguente query:
	
-- Versione 1*/
	SELECT DISTINCT( release_country.release ),track.name,track.length/1000,
		count(release_country.release)
		FROM release_country
    		join release on release_country.release=release.id
    		join medium on medium.release=release.id
    		join track on track.medium=medium.id
		group by release_country.release,track.name,track.length
		having COUNT(release_country.release)>1
	
/*e abbiamo controllato che tra le tuple restituite il nostro risultato fosse effettivamente quello con la lunghezza maggiore.*/

	CREATE VIEW t1 as
			(SELECT DISTINCT( release ),
			count(release)
			FROM release_country
          			GROUP by release_country.release
			HAVING COUNT(release)>1);


	SELECT track.name,(track.length/1000)
	FROM t1
	JOIN release ON release.id=t1.release
	JOIN medium ON medium.release=release.id
	JOIN track ON track.medium=medium.id
	WHERE track.length=(SELECT MAX(track.length)
        	            FROM t1
			    JOIN release ON release.id=t1.release
			    JOIN medium ON medium.release=release.id
			    JOIN track ON track.medium=medium.id
                 	    WHERE t1.release=release.id)
	GROUP by track.name,track.length

	--drop view t1


-- Versione 2

/*Per la realizzazione della seconda versione, la seconda parte è identica alla prima versione. Abbiamo cambiato la prima parte, ovvero la query che ci genera la vista. Questa volta utilizziamo l'operatore insiemistico EXCEPT. Praticamente sottraiamo dall'insieme delle release, quelle che sono state rilasciate solamente in un paese (HAVING COUNT(release)<2). */

	CREATE VIEW  t1 as
			(SELECT DISTINCT( release ),
			count(release)
			FROM release_country
          		GROUP by release_country.release
			EXCEPT
            		SELECT DISTINCT( release ),
			count(release)
			FROM release_country
          		GROUP by release_country.release
            		HAVING COUNT(release)<2);


	SELECT track.name,(track.length/1000)
	FROM t1
	JOIN release ON release.id=t1.release
	JOIN medium ON medium.release=release.id
	JOIN track ON track.medium=medium.id
	WHERE track.length=(SELECT MAX(track.length)
        	        	FROM t1
				JOIN release ON release.id=t1.release
				JOIN medium ON medium.release=release.id
				JOIN track ON track.medium=medium.id
                 		WHERE t1.release=release.id)
	GROUP by track.name,track.length

	--drop view t1
