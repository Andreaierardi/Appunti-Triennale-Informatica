SET search_path TO "AirBnb";

INSERT INTO Utente(Email,Nome_Utente,Nome,Cognome,Numero_Telefono,Data_Nascita,Indirizzo, Foto,Lingua) 
VALUES('simone@caggese.it','SC','Simone','Caggese', 3391751234, '14-02-1997','via rossi 54',1, 3);
INSERT INTO Utente(Email,Nome_Utente,Nome,Cognome,Numero_Telefono,Data_Nascita,Indirizzo, Foto,Lingua) 
VALUES('andrea@ferrari.it','AF','Andrea','Ferrari', 987654321, '18-09-1997','via blu 54',2, 2);
INSERT INTO Utente(Email,Nome_Utente,Nome,Cognome,Numero_Telefono,Data_Nascita,Indirizzo, Foto,Lingua) 
VALUES('andrea@ierardi.it','AI','Andrea','Ierardi', 123456789, '05-01-1997','via verdi 28',3, 1);
INSERT INTO Utente(Email,Nome_Utente,Nome,Cognome,Numero_Telefono,Data_Nascita,Indirizzo, Foto,Lingua) 
VALUES('marco@rossi.it','MR','Marco','Rossi', 33917598765, '10-10-1998','via bergamo 20',4, 3);
INSERT INTO Utente(Email,Nome_Utente,Nome,Cognome,Numero_Telefono,Data_Nascita,Indirizzo, Foto,Lingua) 
VALUES('Membro','Membro','Membro','Membro', 0, '01-01-1990','Membro',1, 1);
INSERT INTO Utente(Email,Nome_Utente,Nome,Cognome,Numero_Telefono,Data_Nascita,Indirizzo, Foto,Lingua) 
VALUES('andrea@rossi.it','AR','Andrea','Rossi', 903485, '01-01-1997','via ambrogio 54',5, 3);
INSERT INTO Utente(Email,Nome_Utente,Nome,Cognome,Numero_Telefono,Data_Nascita,Indirizzo, Foto,Lingua) 
VALUES('edoardo@ierardi.it','EI','Edoardo','Ierardi', 3391751010, '25-01-1997','via sensounico 28',6, 4);

INSERT INTO Proprietario(Email_Proprietario,Tasso_Risposta,Impegno,SuperHost,Esperienza)
VALUES ('marco@rossi.it',33,4,false,10);
INSERT INTO Proprietario(Email_Proprietario,Tasso_Risposta,Impegno)
VALUES ('andrea@ierardi.it',12,5);
INSERT INTO Proprietario(Email_Proprietario,Tasso_Risposta,Impegno,SuperHost,Esperienza)
VALUES ('andrea@ferrari.it',100,100,true,100);
INSERT INTO Proprietario(Email_Proprietario,Tasso_Risposta,Impegno,SuperHost,Esperienza)
VALUES ('edoardo@ierardi.it',20,20,false,20);
INSERT INTO Proprietario(Email_Proprietario,Tasso_Risposta,Impegno,SuperHost,Esperienza)
VALUES ('simone@caggese.it',20,20,false,20);



INSERT INTO Sistemazione(IdSistemazione,Email_P,Indirizzo,Numero_Letti,Tipi_Letto,Posti_Letto,Camere_Da_Letto,Numero_Bagni,Termini_Cancellazione,Descrizione,Numero_Di_Recensioni,Servizi,Tipo)
VALUES (1,'simone@caggese.it','piazza duomo 1',4,'Matrimoniali',8,4,2,1,'In centro',10,'Aria condizionata',true);
INSERT INTO Sistemazione(IdSistemazione,Email_P,Indirizzo,Numero_Letti,Tipi_Letto,Posti_Letto,Camere_Da_Letto,Numero_Bagni,Termini_Cancellazione,Descrizione,Numero_Di_Recensioni,Servizi,Tipo)
VALUES (2,'andrea@ferrari.it','via mare 1',2,'Singoli',4,2,1,1,'Vista mare',4,'Bella vista',true);
INSERT INTO Sistemazione(IdSistemazione,Email_P,Indirizzo,Numero_Letti,Tipi_Letto,Posti_Letto,Camere_Da_Letto,Numero_Bagni,Termini_Cancellazione,Descrizione,Numero_Di_Recensioni,Tipo)
VALUES (3,'andrea@ierardi.it','via stanza singola',2,'Singoli',1,1,0,1,'Fantastica stanza',1,false);
INSERT INTO Sistemazione(IdSistemazione,Email_P,Indirizzo,Numero_Letti,Tipi_Letto,Posti_Letto,Camere_Da_Letto,Numero_Bagni,Termini_Cancellazione,Descrizione,Tipo)
VALUES (4,'andrea@ierardi.it','via appartamento',3,'Singoli e matrimoniali',5,1,1,1,'Fantastico appartamento',true);
INSERT INTO Sistemazione(IdSistemazione,Email_P,Indirizzo,Numero_Letti,Tipi_Letto,Posti_Letto,Camere_Da_Letto,Numero_Bagni,Termini_Cancellazione,Descrizione,Numero_Di_Recensioni,Tipo)
VALUES (5,'andrea@ierardi.it','via bella',2,'Matrimoniali',1,1,1,1,'Stanza singola privata',1,false);

INSERT INTO Prezzo(Sistemazione, PrezzoSoggiorno, SpesePulizia, Cauzione, OspitiExtra) 
VALUES(1, 35, 10,20, 30);
INSERT INTO Prezzo(Sistemazione, PrezzoSoggiorno, SpesePulizia, Cauzione, OspitiExtra) 
VALUES(2, 70, 40, 50, 60);
INSERT INTO Prezzo(Sistemazione, PrezzoSoggiorno, SpesePulizia, Cauzione, OspitiExtra) 
VALUES(3, 100, 10, 40, 70);
INSERT INTO Prezzo(Sistemazione, PrezzoSoggiorno, SpesePulizia, Cauzione, OspitiExtra)
VALUES(4, 150, 20, 50, 80);
INSERT INTO Prezzo(Sistemazione, PrezzoSoggiorno, SpesePulizia, Cauzione, OspitiExtra) 
VALUES(5, 150, 30, 60, 90);

INSERT INTO Prenotazione(NumeroPrenotazione,UtentePrenotante, SistemazionePrenotata, DataInizio, CheckIn, DataFine,CheckOut,Cancellazione) 
VALUES(1,'andrea@ferrari.it',1,'20-09-2018', '11:00:00','28-09-2018', '11:00:00',false );
INSERT INTO Prenotazione(NumeroPrenotazione,UtentePrenotante, SistemazionePrenotata, DataInizio, CheckIn, DataFine,CheckOut,Cancellazione) 
VALUES(2,'andrea@ferrari.it',2,'20-10-2018', '12:00:00','21-10-2018', '10:00:00',false );
INSERT INTO Prenotazione(NumeroPrenotazione,UtentePrenotante, SistemazionePrenotata, DataInizio, CheckIn, DataFine,CheckOut,Cancellazione) 
VALUES(3,'simone@caggese.it',3,'30-09-2018', '13:00:00','30-10-2018', '11:00:00',false );
INSERT INTO Prenotazione(NumeroPrenotazione,UtentePrenotante, SistemazionePrenotata, DataInizio, CheckIn, DataFine,CheckOut,Cancellazione) 
VALUES(4,'simone@caggese.it',4,'11-11-2019', '14:00:00','12-11-2019', '10:00:00',true);
INSERT INTO Prenotazione(NumeroPrenotazione,UtentePrenotante, SistemazionePrenotata, DataInizio, CheckIn, DataFine,CheckOut,Cancellazione) 
VALUES(5,'andrea@ierardi.it',5,'01-01-2020', '15:00:00','05-01-2020', '11:00:00',true);

INSERT INTO Recensione(IdRecensione, Descrizione,NumeroStelle) 
VALUES(1,'a', 4);
INSERT INTO Recensione(IdRecensione,Descrizione, NumeroStelle) 
VALUES(2, 'b',5);
INSERT INTO Recensione(IdRecensione, Descrizione,NumeroStelle) 
VALUES(3, 'c',2);
INSERT INTO Recensione(IdRecensione, Descrizione,NumeroStelle)  
VALUES(4,'d', 3);
INSERT INTO Recensione(IdRecensione, Descrizione,NumeroStelle) 
VALUES(5,'e',  1);
INSERT INTO Recensione(IdRecensione, Descrizione,NumeroStelle) 
VALUES(6,'f', 3);
INSERT INTO Recensione(IdRecensione,Descrizione, NumeroStelle) 
VALUES(7,'l' ,1);
INSERT INTO Recensione(IdRecensione,Descrizione, NumeroStelle) 
VALUES(8,'g', 4);
INSERT INTO Recensione(IdRecensione, Descrizione,NumeroStelle) 
VALUES(9,'h', 5);

INSERT INTO Recensione_Cliente(IdRecensione,ClienteRecensito,HostRecensore)
VALUES(1,'simone@caggese.it','andrea@ierardi.it');
INSERT INTO Recensione_Cliente(IdRecensione,ClienteRecensito,HostRecensore)
VALUES(2,'andrea@ierardi.it','edoardo@ierardi.it');
INSERT INTO Recensione_Cliente(IdRecensione,ClienteRecensito,HostRecensore)
VALUES(3,'simone@caggese.it','andrea@ierardi.it');

INSERT INTO Recensione_Sistemazione(IdRecensione,SistemazioneRecensita,ClienteRecensore,Risposta,Privata)
VALUES(7,1,'andrea@ierardi.it','bello',true);
INSERT INTO Recensione_Sistemazione(IdRecensione,SistemazioneRecensita,ClienteRecensore,Risposta,Privata)
VALUES(8,2,'edoardo@ierardi.it','ciao',false);
INSERT INTO Recensione_Sistemazione(IdRecensione,SistemazioneRecensita,ClienteRecensore)
VALUES(9,3,'andrea@ierardi.it');