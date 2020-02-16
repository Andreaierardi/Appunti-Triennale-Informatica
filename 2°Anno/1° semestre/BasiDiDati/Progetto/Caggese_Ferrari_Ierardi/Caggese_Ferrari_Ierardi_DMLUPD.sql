SET search_path TO "AirBnb";



/*MODIFICA NUMERO UTENTE */

UPDATE utente
SET  numero_Telefono = 23408254 
WHERE nome_Utente = 'AF';


/*MODIFICA TASSO RISPOSTA PROPRIETARIO*/

UPDATE Proprietario
SET  Tasso_Risposta = 80
WHERE Email_Proprietario = 'andrea@ierardi.it';

/*MODIFICA NUMERO LETTI SISTEMAZIONE*/

UPDATE sistemazione
SET  numero_Letti = 6 
WHERE idSistemazione = 2;

/*MODIFICA SISTEMAZIONE DIVENTA APPARTAMENTO*/

UPDATE sistemazione
SET  Tipo = true
WHERE idSistemazione = 3;


/*MODIFICA PREZZO  SPESE PULIZIA*/

UPDATE prezzo
SET  SpesePulizia = 120
WHERE sistemazione = 3;

/*MODIFICA/CANCELLA PRENOTAZIONE*/

UPDATE Prenotazione
SET  Cancellazione= true
WHERE NumeroPrenotazione = 2;

/*MODIFICA  DATA INIZIO PRENOTAZIONE*/

UPDATE Prenotazione
SET  CheckIn= '16:00:00'
WHERE NumeroPrenotazione = 4;

/*MODIFICA DESCRIZIONE RECENSIONE*/

UPDATE Recensione
SET  NumeroStelle = 3
WHERE IdRecensione = 2;


/*INSERISCE  NUOVO UTENTE */

INSERT INTO Utente(Email,Nome_Utente,Nome,Cognome,Numero_Telefono,Data_Nascita,Indirizzo, Foto,Lingua) 
VALUES('paolo@ferrari.it','PF','Paolo','Ferrari', 4508456, '11-09-1997','via blu 23',2, 2);

/* ELIMINA UTENTE 
Quando un utente viene eliminato i suoi dati personali vengono cancellati ma le recensioni che ha scritto 
vengono mantenute nel DB ma compaiono come scritte da 'Membro'*/
DELETE 
FROM utente 
WHERE Email = 'edoardo@ierardi.it';






