CREATE SCHEMA "AirBnb";

SET search_path TO "AirBnb";

CREATE TABLE Utente
(
	Email VARCHAR(64) UNIQUE PRIMARY KEY,
	Nome_Utente VARCHAR(32) NOT NULL ,
	Nome VARCHAR(32) NOT NULL,
	Cognome VARCHAR(32) NOT NULL,
	Numero_Telefono BIGINT,
	Data_Nascita DATE NOT NULL,
	Indirizzo VARCHAR(32) NOT NULL,
	Foto INT DEFAULT 1,
	Lingua INT DEFAULT 1
  
);

CREATE TABLE Proprietario
(
	Email_Proprietario VARCHAR(64)  UNIQUE PRIMARY KEY DEFAULT 'Membro',
	FOREIGN KEY(Email_Proprietario) REFERENCES Utente(Email)
	ON UPDATE CASCADE
	ON DELETE SET DEFAULT,
	Tasso_Risposta INT DEFAULT 0,
	Impegno INT DEFAULT 0,
	SuperHost BOOLEAN DEFAULT FALSE,
	Esperienza INT  DEFAULT 0
	
);

CREATE TABLE Sistemazione
(
	IdSistemazione INT UNIQUE PRIMARY KEY,
	Email_P VARCHAR(64) DEFAULT 'Membro',
	FOREIGN KEY(Email_P)  REFERENCES Proprietario(Email_Proprietario)
	ON UPDATE CASCADE
	ON DELETE SET DEFAULT,
	Indirizzo VARCHAR(64) NOT NULL,
	Numero_Letti INT NOT NULL DEFAULT 1,
	Tipi_Letto VARCHAR(64) DEFAULT 'Mezza Piazza',
	Posti_Letto INT NOT NULL DEFAULT 1 ,
	Camere_Da_Letto INT DEFAULT 0 ,
	Numero_Bagni INT NOT NULL DEFAULT 1,
	Termini_Cancellazione INT NOT NULL,
	Descrizione TEXT NOT NULL,
	Numero_Di_Recensioni INT DEFAULT 0,
	Servizi  VARCHAR(256) DEFAULT 'Non ci sono servizi aggiuntivi',
	Tipo BOOLEAN NOT NULL --FALSE e' una stanza singola, TRUE d' un appartamento
);


CREATE TABLE Prezzo
(
	Sistemazione INT NOT NULL PRIMARY KEY,
	FOREIGN KEY(Sistemazione) 
	REFERENCES Sistemazione(IdSistemazione)
        ON UPDATE CASCADE
        ON DELETE CASCADE,
	PrezzoSoggiorno FLOAT NOT NULL,
	SpesePulizia FLOAT DEFAULT 0 ,
	Cauzione FLOAT DEFAULT 0,
	OspitiExtra FLOAT DEFAULT 0
);

CREATE TABLE Prenotazione
(
	NumeroPrenotazione  SERIAL UNIQUE NOT NULL PRIMARY KEY ,
	UtentePrenotante VARCHAR(64)DEFAULT 'Membro' ,
	FOREIGN KEY(UtentePrenotante) REFERENCES Utente(Email)
	ON UPDATE CASCADE
	ON DELETE SET DEFAULT,
	SistemazionePrenotata INT,
	FOREIGN KEY(SistemazionePrenotata) REFERENCES Sistemazione(IdSistemazione)
        ON UPDATE CASCADE
        ON DELETE NO ACTION,
	DataInizio DATE NOT NULL,
	CheckIn TIME(1) DEFAULT '13:00:00',
	DataFine DATE NOT NULL,
	CheckOut TIME(1) DEFAULT '10:00:00',
	CHECK(DataFine>=DataInizio),
	Cancellazione BOOLEAN DEFAULT FALSE -- TRUE nel caso in cui la cancellazione sia stata cancellata

);

CREATE TABLE Recensione
(
	IdRecensione  SERIAL UNIQUE NOT NULL PRIMARY KEY ,
	Risposta VARCHAR(64),
	Descrizione TEXT,
	NumeroStelle INT DEFAULT 0
	CHECK(NumeroStelle>0 AND NumeroStelle<=5)
);

CREATE TABLE Recensione_Cliente
(
	IdRecensione INT  NOT NULL PRIMARY KEY,
	FOREIGN KEY(IdRecensione) REFERENCES Recensione(IdRecensione)
	ON UPDATE CASCADE
	ON DELETE CASCADE,
	ClienteRecensito VARCHAR(64) NOT NULL DEFAULT 'Membro',
	FOREIGN KEY(ClienteRecensito) REFERENCES Utente(Email)
	ON UPDATE CASCADE
	ON DELETE SET DEFAULT,
	HostRecensore VARCHAR(64) NOT NULL DEFAULT 'Membro',
	FOREIGN KEY(HostRecensore) REFERENCES Proprietario(Email_Proprietario)
	ON UPDATE CASCADE
	ON DELETE SET DEFAULT 
);


CREATE TABLE Recensione_Sistemazione
(
	IdRecensione INT  NOT NULL PRIMARY KEY,
	FOREIGN KEY(IdRecensione) REFERENCES Recensione(IdRecensione)
	ON UPDATE CASCADE
	ON DELETE CASCADE,
	SistemazioneRecensita INT NOT NULL,
	FOREIGN KEY(SistemazioneRecensita) REFERENCES Sistemazione(IdSistemazione)
	ON UPDATE CASCADE
	ON DELETE CASCADE,
	ClienteRecensore VARCHAR(64) NOT NULL DEFAULT 'Membro',
	FOREIGN KEY(ClienteRecensore) REFERENCES Utente(Email)
	ON UPDATE CASCADE
	ON DELETE SET DEFAULT,
	Risposta VARCHAR(64),
	Privata BOOLEAN DEFAULT FALSE --FALSE è pubblica TRUE se è privata
);

