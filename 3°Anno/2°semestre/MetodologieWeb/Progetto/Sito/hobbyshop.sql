-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Creato il: Lug 25, 2019 alle 12:46
-- Versione del server: 10.1.40-MariaDB
-- Versione PHP: 7.3.5

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `hobbyshop`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `album`
--

CREATE TABLE `album` (
  `id` int(11) NOT NULL,
  `titolo` varchar(50) NOT NULL,
  `artista` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `album`
--

INSERT INTO `album` (`id`, `titolo`, `artista`) VALUES
(1, 'Help!', 1),
(2, 'Vide Noir', 2),
(3, 'The Rise and Fall Of Ziggy Stardust', 3);

-- --------------------------------------------------------

--
-- Struttura della tabella `artista`
--

CREATE TABLE `artista` (
  `id` int(11) NOT NULL,
  `nome` varchar(45) NOT NULL,
  `data_nascita` varchar(45) DEFAULT NULL,
  `luogo_nascita` varchar(45) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `artista`
--

INSERT INTO `artista` (`id`, `nome`, `data_nascita`, `luogo_nascita`) VALUES
(1, 'The Beatles', '16/08/1960', 'Inghilterra'),
(2, 'Lord Huron', '12/12/1998', 'Stati Uniti'),
(3, 'David Bowie', '14/03/1962', 'Inghilterra');

-- --------------------------------------------------------

--
-- Struttura della tabella `attore`
--

CREATE TABLE `attore` (
  `id` int(11) NOT NULL,
  `nome` varchar(15) NOT NULL,
  `cognome` varchar(15) NOT NULL,
  `sesso` char(1) NOT NULL,
  `data_nascita` varchar(45) DEFAULT NULL,
  `luogo_nascita` varchar(45) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `attore`
--

INSERT INTO `attore` (`id`, `nome`, `cognome`, `sesso`, `data_nascita`, `luogo_nascita`) VALUES
(1, 'Sam', 'Worthington', 'M', '02/08/1976', 'Inghilterra'),
(2, 'Zoe', 'Saldana', 'F', '19/06/1978', 'Stati Uniti'),
(3, 'Stephen', 'Lang', 'M', '11/07/1952', 'Stati Uniti'),
(4, 'Michelle ', 'Rodriguez', 'F', '12/07/1978', 'Stati Uniti');

-- --------------------------------------------------------

--
-- Struttura della tabella `autore`
--

CREATE TABLE `autore` (
  `id` int(11) NOT NULL,
  `nome` varchar(15) NOT NULL,
  `cognome` varchar(15) NOT NULL,
  `sesso` varchar(1) NOT NULL,
  `data_nascita` varchar(45) DEFAULT NULL,
  `luogo_nascita` varchar(45) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `autore`
--

INSERT INTO `autore` (`id`, `nome`, `cognome`, `sesso`, `data_nascita`, `luogo_nascita`) VALUES
(1, 'George R. R.', 'Martin', 'M', '20/09/1948', 'Stati Uniti'),
(2, 'J. K.', 'Rowling', 'F', '18/07/1965', 'Inghilterra'),
(3, 'Guido', 'Tonelli', 'M', '18/06/1961', 'Italia');

-- --------------------------------------------------------

--
-- Struttura della tabella `canzone`
--

CREATE TABLE `canzone` (
  `id` int(11) NOT NULL,
  `titolo` varchar(50) NOT NULL,
  `album` int(11) NOT NULL,
  `durata` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `canzone`
--

INSERT INTO `canzone` (`id`, `titolo`, `album`, `durata`) VALUES
(1, 'Help!', 1, '00:02:18'),
(2, 'You\'ve Got to Hide Your Love Away', 1, '00:02:08'),
(3, 'The Night Before', 1, '00:02:33'),
(4, 'I Need You', 1, '00:02:28'),
(5, 'Another Girl', 1, '00:02:05');

-- --------------------------------------------------------

--
-- Struttura della tabella `carrello`
--

CREATE TABLE `carrello` (
  `id` int(11) NOT NULL,
  `utente` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `carrello`
--

INSERT INTO `carrello` (`id`, `utente`) VALUES
(0, 0),
(1, 1),
(2, 2);

-- --------------------------------------------------------

--
-- Struttura della tabella `carta`
--

CREATE TABLE `carta` (
  `id` int(11) NOT NULL,
  `nome_intestatario` varchar(15) NOT NULL,
  `cognome_intestatario` varchar(15) NOT NULL,
  `numero` varchar(30) NOT NULL,
  `codice` int(3) NOT NULL,
  `scadenza` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `carta`
--

INSERT INTO `carta` (`id`, `nome_intestatario`, `cognome_intestatario`, `numero`, `codice`, `scadenza`) VALUES
(0, 'Daniele', 'Ierardi', '0987098712341234', 323, '18/05/2021'),
(0, 'Marco', 'Pati', '1234567887654321', 123, '18/09/2021'),
(0, 'Marco', 'Pati', '1234567898765432', 321, '18/08/2019'),
(0, 'Marco', 'Pati', '3456345634563456', 321, '17/09/2020'),
(0, 'Marco', 'Pati', '4567456745674567', 334, '27/02/2018'),
(1, 'Andrea', 'Ierardi', '1234123412341234', 987, '10/02/2021'),
(2, 'Eugenio', 'Rizzi', '6789678967896789', 123, '28/07/2022');

-- --------------------------------------------------------

--
-- Struttura della tabella `categoria`
--

CREATE TABLE `categoria` (
  `id` int(11) NOT NULL,
  `nome` varchar(15) NOT NULL,
  `immagine` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `categoria`
--

INSERT INTO `categoria` (`id`, `nome`, `immagine`) VALUES
(1, 'film', 'film.jpg'),
(2, 'musica', 'musica.jpg'),
(3, 'videogiochi', 'videogiochi.jpg'),
(4, 'libri', 'libri.jpg');

-- --------------------------------------------------------

--
-- Struttura della tabella `cont_carrello`
--

CREATE TABLE `cont_carrello` (
  `carrello` int(11) NOT NULL,
  `prodotto` int(11) NOT NULL,
  `quantita` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `cont_carrello`
--

INSERT INTO `cont_carrello` (`carrello`, `prodotto`, `quantita`) VALUES
(1, 1, 4);

-- --------------------------------------------------------

--
-- Struttura della tabella `cont_ordine`
--

CREATE TABLE `cont_ordine` (
  `id` int(11) NOT NULL,
  `ordine` int(11) NOT NULL,
  `prodotto` int(11) NOT NULL,
  `quantita` int(11) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `cont_ordine`
--

INSERT INTO `cont_ordine` (`id`, `ordine`, `prodotto`, `quantita`, `timestamp`) VALUES
(1, 1, 1, 1, '2019-06-15 06:19:00'),
(2, 1, 3, 2, '2019-06-15 06:19:00'),
(26, 1, 1, 1, '2019-07-24 15:03:33'),
(27, 1, 1, 2, '2019-07-24 15:25:19'),
(28, 1, 1, 2, '2019-07-24 15:26:50'),
(29, 1, 3, 3, '2019-07-24 15:26:53'),
(30, 1, 4, 2, '2019-07-24 15:26:56'),
(31, 1, 1, 2, '2019-07-24 15:27:09'),
(32, 1, 3, 2, '2019-07-24 15:28:57'),
(33, 1, 3, 2, '2019-07-24 15:29:10'),
(34, 1, 1, 2, '2019-07-24 15:29:40'),
(35, 1, 1, 1, '2019-07-24 15:31:06'),
(36, 1, 3, 1, '2019-07-24 15:31:06'),
(37, 1, 4, 1, '2019-07-24 15:31:06'),
(38, 1, 1, 1, '2019-07-24 15:31:50'),
(39, 1, 3, 1, '2019-07-24 15:31:50'),
(40, 1, 4, 1, '2019-07-24 15:31:50'),
(41, 1, 1, 1, '2019-07-24 15:32:38'),
(42, 1, 3, 1, '2019-07-24 15:32:38'),
(43, 1, 4, 1, '2019-07-24 15:32:38'),
(44, 1, 1, 1, '2019-07-24 15:33:06'),
(45, 1, 3, 1, '2019-07-24 15:33:06'),
(46, 1, 4, 1, '2019-07-24 15:33:06'),
(47, 1, 1, 1, '2019-07-24 15:35:26'),
(48, 1, 3, 1, '2019-07-24 15:35:26'),
(49, 1, 4, 1, '2019-07-24 15:35:26'),
(50, 1, 1, 2, '2019-07-24 15:39:24'),
(51, 1, 3, 1, '2019-07-24 15:41:12'),
(52, 1, 4, 1, '2019-07-24 15:41:13'),
(53, 1, 1, 1, '2019-07-24 15:43:24'),
(54, 1, 3, 1, '2019-07-24 15:43:24'),
(55, 1, 1, 1, '2019-07-24 15:59:30'),
(56, 1, 1, 1, '2019-07-24 15:59:59'),
(57, 1, 1, 1, '2019-07-24 16:00:45'),
(58, 1, 1, 1, '2019-07-24 16:03:22'),
(59, 1, 3, 2, '2019-07-24 16:03:22'),
(60, 1, 1, 1, '2019-07-24 16:03:39'),
(61, 1, 3, 1, '2019-07-24 16:03:39'),
(62, 1, 1, 1, '2019-07-24 16:04:17'),
(63, 1, 4, 8, '2019-07-24 16:04:17'),
(64, 1, 1, 1, '2019-07-24 16:04:51'),
(65, 1, 3, 1, '2019-07-24 16:05:43'),
(66, 1, 1, 1, '2019-07-24 16:10:16'),
(67, 1, 4, 1, '2019-07-24 16:10:44'),
(68, 1, 4, 2, '2019-07-24 20:53:15'),
(69, 1, 1, 4, '2019-07-24 20:53:32'),
(70, 0, 4, 1, '2019-07-25 09:37:20');

-- --------------------------------------------------------

--
-- Struttura della tabella `editore`
--

CREATE TABLE `editore` (
  `id` int(11) NOT NULL,
  `nome` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `editore`
--

INSERT INTO `editore` (`id`, `nome`) VALUES
(1, 'Mondadori'),
(2, 'Salani '),
(3, 'Feltrinelli');

-- --------------------------------------------------------

--
-- Struttura della tabella `film`
--

CREATE TABLE `film` (
  `id` int(11) NOT NULL,
  `titolo` varchar(45) NOT NULL,
  `regista` varchar(45) DEFAULT NULL,
  `genere` varchar(45) DEFAULT NULL,
  `dvd` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `film`
--

INSERT INTO `film` (`id`, `titolo`, `regista`, `genere`, `dvd`) VALUES
(1, 'Avatar', '1', 'Fantascienza', '1'),
(2, 'I Sogni Segreti di Walter Mitty DVD', '2', 'Avventura', '3'),
(3, 'Il Nome della rosa DVD', '3', 'Thriller', '4');

-- --------------------------------------------------------

--
-- Struttura della tabella `indirizzo`
--

CREATE TABLE `indirizzo` (
  `id` int(11) NOT NULL,
  `via` varchar(30) NOT NULL,
  `civico` int(11) NOT NULL,
  `citta` varchar(15) NOT NULL,
  `provincia` char(2) NOT NULL,
  `stato` varchar(15) NOT NULL,
  `cap` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `indirizzo`
--

INSERT INTO `indirizzo` (`id`, `via`, `civico`, `citta`, `provincia`, `stato`, `cap`) VALUES
(0, 'Viale Carlo Marx', 14, 'Voghera', 'PV', 'Italia', 27058),
(1, 'Viale Carlo Marx', 14, 'Voghera', 'PV', 'Italia', 27058),
(2, 'Via Emilia', 18, 'Tortona', 'AL', 'Italia', 15057);

-- --------------------------------------------------------

--
-- Struttura della tabella `ordine`
--

CREATE TABLE `ordine` (
  `id` int(11) NOT NULL,
  `utente` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `ordine`
--

INSERT INTO `ordine` (`id`, `utente`) VALUES
(0, 0),
(1, 1),
(2, 2);

-- --------------------------------------------------------

--
-- Struttura della tabella `prenotazione`
--

CREATE TABLE `prenotazione` (
  `id` int(11) NOT NULL,
  `prodotto` int(11) NOT NULL,
  `utente` int(11) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `prenotazione`
--

INSERT INTO `prenotazione` (`id`, `prodotto`, `utente`, `timestamp`) VALUES
(2, 3, 1, '0000-00-00 00:00:00');

-- --------------------------------------------------------

--
-- Struttura della tabella `prodotto`
--

CREATE TABLE `prodotto` (
  `id` int(11) NOT NULL,
  `nome` varchar(50) NOT NULL,
  `categoria` int(11) NOT NULL,
  `foto` varchar(30) NOT NULL,
  `descrizione` mediumtext NOT NULL,
  `costo` double NOT NULL,
  `costo_spedizione` double NOT NULL,
  `giacenza` int(11) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `prodotto`
--

INSERT INTO `prodotto` (`id`, `nome`, `categoria`, `foto`, `descrizione`, `costo`, `costo_spedizione`, `giacenza`, `timestamp`) VALUES
(1, 'Avatar - DVD', 1, 'avatar.jpg', 'Avatar e\' un film di genere fantascienza, avventura, azione, thriller del 2009, diretto da James Cameron, con Sam Worthington e Sigourney Weaver. Uscita al cinema il 15 gennaio 2010. Durata 166 minuti. Distribuito da 20th Century Fox.', 9.99, 2, 4, '2019-06-15 13:03:00'),
(2, 'Help! - CD', 2, 'help.jpg', 'Help! e\' il quinto album del gruppo musicale britannico The Beatles, pubblicato nel 1965 e prodotto da George Martin. L\'album comprende quattordici brani dei quali i primi sette contenuti nella prima faccia del disco costituiscono la colonna sonora dell\'omonimo film; contiene Yesterday, una delle canzoni piu\' note dei Beatles, composta e cantata dal solo Paul McCartney nonostante come consuetudine venga attribuita al duo Lennon-McCartney.', 28.99, 2.5, 3, '2019-07-25 09:42:34'),
(3, 'Sekiro - DVD', 3, 'sekiro.jpg', 'In Sekiro: Shadows Die Twice vestirai i panni di un \"lupo senza un braccio\", un guerriero sfregiato e caduto in disgrazia, salvato a un passo dalla morte. Il tuo destino e\' legato a un giovane di nobili origini, discendente di un\'antica stirpe: per proteggerlo affronterai numerosi nemici, tra cui lo spietato clan Ashina. Niente ti fermera\' nella pericolosa missione per riscattare il tuo onore e liberare il giovane signore, nemmeno la morte stessa.', 61.99, 0, 1, '2019-07-22 07:55:00'),
(4, 'Il trono di spade: un gioco di troni', 4, 'giocodeltrono1.jpg', 'In una terra fuori dal mondo, dove le estati e gli inverni possono durare intere generazioni, sta per esplodere un immane conflitto. Sul Trono di Spade, nel Sud caldo e opulento, siede Robert Baratheon. L\'ha conquistato dopo una guerra sanguinosa, togliendolo all\'ultimo, folle re della dinastia Targaryen, i signori dei draghi. Ma il suo potere e\' ora minacciato: all\'estremo Nord, la Barriera - una muraglia eretta per difendere il regno da animali primordiali e, soprattutto, dagli Estranei - sembra vacillare. Si dice che gli Estranei siano scomparsi da secoli. Ma se e\' vero, chi sono allora quegli esseri con gli occhi cosi\' azzurri e gelidi, nascosti tra le ombre delle foreste, che rubano la vita, o il senno, a chi ha la mala sorte di incontrarli? La fine della lunga estate e\' vicina, l\'inverno sta arrivando: solo un nuovo prodigio potra\' squarciare le tenebre. Intrighi e rivalita\', guerre e omicidi, amori e tradimenti, si intrecciano nel primo volume della saga delle \"Cronache del ghiaccio e del fuoco\". ', 14.02, 3.99, 1, '2019-07-25 09:35:02'),
(5, 'I Sogni Segreti di Walter Mitty', 1, 'walter.jpg', 'Walter Mitty lavora da una vita per Life, è l\'archivista dei negativi e quindi del tesoro fotografico della rivista. Quando arriva la notizia della chiusura della versione cartacea a favore di quella online (notizia data da un team di biechi ed ignoranti rottamatori incaricati di operare la transizione) si pone il problema della copertina dell\'ultimo numero', 20, 3, 6, '2019-07-25 08:24:23'),
(6, 'Il Nome della Rosa DVD', 1, 'rosa.jpg', 'Il nome della rosa è un romanzo scritto da Umberto Eco ed edito per la prima volta da Bompiani nel 1980.\r\n\r\nGià autore di numerosi saggi, il semiologo decise di scrivere il suo primo romanzo, cimentandosi nel genere del giallo storico e in particolare del giallo deduttivo. ', 15, 2, 6, '2019-07-25 08:24:25'),
(7, 'Vide Noir', 2, 'nightwemet.jpg', 'Dopo essere stato scelto come uno dei brani della colonna sonora della serie televisiva Tredici, la canzone è entrata in alcune classifiche ufficiali di diversi paesi. Inoltre, è stato certificato il 26 giugno 2017 disco d\'oro e il 15 febbraio successivo disco di platino dalla Recording Industry Association of America per la vendita di oltre un milione di copie', 20, 8, 2, '2019-07-25 08:29:08'),
(8, 'The Rise and Fall Of Ziggy Stardust', 2, 'david.jpg', 'The Rise and Fall of Ziggy Stardust and the Spiders from Mars, spesso indicato come Ziggy Stardust, è il quinto album in studio dell\'artista inglese David Bowie', 30, 2, 1, '2019-07-25 08:33:29'),
(9, 'Crash Bandicoot DVD', 3, 'crash.jpg', 'Crash Bandicoot è un franchise appartenente ai generi platform, avventura dinamica, simulatore di guida e party. I primi videogiochi della serie uscirono per PlayStation ', 5, 2, 6, '2019-07-25 08:44:05'),
(10, 'Spyro', 3, 'spyro.jpg', 'Spyro the Dragon è una serie di videogiochi a piattaforme. In un primo periodo (1998-2000), la serie fu sviluppata da Insomniac Games per i primi tre capitoli sulla console Sony PlayStation e coprodotta da Sony e da Universal Interactive Studios (successivamente acquisita da Vivendi, a sua volta acquisita nel 2007 da Activision)', 7, 2, 8, '2019-07-25 08:44:05'),
(11, 'Harry Potter e la pietra filosofale', 4, 'harry.jpg', 'Harry Potter e la pietra filosofale (titolo originale in inglese: Harry Potter and the Philosopher\'s Stone) è il primo romanzo della saga high fantasy Harry Potter, scritta da J. K. Rowling e ambientata principalmente nell\'immaginario Mondo magico durante gli anni novanta del XX secolo.', 25, 3, 2, '2019-07-25 08:58:43'),
(12, 'Genesi', 4, 'genesi.jpg', 'Forse avevano davvero ragione i Greci, che in principio era il caos. Molte osservazioni della fisica moderna sembrerebbero confermarlo. Ma cos\'è successo nei primi istanti di vita dell\'universo? Davvero la scienza del XII secolo fa ritornare d\'attualità il racconto di Esiodo, che racchiude l\'origine del tutto in un verso splendido e fulminante: \"All\'inizio e per primo venne a essere il caos\"? ', 17, 2, 0, '2019-07-25 09:09:20');

-- --------------------------------------------------------

--
-- Struttura della tabella `recensione`
--

CREATE TABLE `recensione` (
  `id` int(11) NOT NULL,
  `prodotto` int(11) NOT NULL,
  `utente` int(11) NOT NULL,
  `valore` int(4) DEFAULT NULL,
  `descrizione` mediumtext NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `recensione`
--

INSERT INTO `recensione` (`id`, `prodotto`, `utente`, `valore`, `descrizione`, `timestamp`) VALUES
(0, 1, 0, 2, 'Avatar non Ã¨ per Cameron una storia che rilegge criticamente il falso mito del colonialismo, non Ã¨ una critica piÃ¹ o meno sottile alla brutale belligeranza degli Stati Uniti dal Vietnam fino allâ€™Afghanistan, non Ã¨ il contraddittorio racconto della necessitÃ  quasi luddista di un ritorno alle origini e alla Natura, ma appare (altrettanto contraddittoriamente?) come la traduzione filmica dello scontro tra una cultura ancora maggioritariamente postindustriale e le nuove, diverse culture digitali della rete e le', '2019-07-25 02:30:15'),
(1, 1, 1, 2, 'Ad oggi ancora insuperato (a mio parere) a livello tecnico, questa edizione si presenta come una buona edizione: bella la steelbook, presente sia in 3D sia in 2D Blu-Ray e anche il DVD. 4 stelle invece che 5 per l\'audio italiano: prima o poi arriveremo anche noi ad avere sempre il massimo anche in questo campo, purtroppo non in questo caso dove solo il formato inglese presenta il DTS HD, il nostro sembra l\'audio di un semplice DVD, forse dovuto al fatto che i blu-ray sono su di uno stesso supporto. Magari facendo due Blu-ray (uno per il 3D e uno per il 2D) si poteva rimediare, un po \"braccette\" quelli della FOX. Comunque il film fa il suo dovere: intrattiene, e lo fa con una qualita\' visiva difficilmente riscontrabile in altri film', '2019-07-25 02:26:17'),
(2, 1, 2, 4, 'Film capolavoro firmato James Cameron, bella la trama, ottimi interpreti, e per gli amanti della tecnica del cinema non puo\' non essere materia di studio.', '2019-07-25 02:25:29'),
(3, 2, 1, 4, 'La Storia della Musica Pop (e non solo) si scrive con la B di Beatles. I Fab Four hanno ancora parecchio da dire a dispetto degli anni passati e di tutti i generi musicali che si sono avvicendati nel tempo, e lo scrive uno che ama praticamente tutta la Musica. Se Lennon e Mc Cartney non avessero composto Help io probabilmente sarei cresciuto in maniera diversa...Assolutamente imperdibile!', '2019-07-24 19:55:05');

-- --------------------------------------------------------

--
-- Struttura della tabella `regista`
--

CREATE TABLE `regista` (
  `id` int(11) NOT NULL,
  `nome` varchar(15) NOT NULL,
  `cognome` varchar(15) NOT NULL,
  `data_nascita` varchar(45) DEFAULT NULL,
  `luogo_nascita` varchar(45) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `regista`
--

INSERT INTO `regista` (`id`, `nome`, `cognome`, `data_nascita`, `luogo_nascita`) VALUES
(1, 'James', 'Cameron', '16/09/1954', 'Canada'),
(2, 'Ben', 'Stiller', '18/06/1975', 'Stati Uniti'),
(3, 'Jean', 'Annaud', '18/06/1956', 'Francia');

-- --------------------------------------------------------

--
-- Struttura della tabella `ruoli`
--

CREATE TABLE `ruoli` (
  `attore` int(11) NOT NULL,
  `film` int(11) NOT NULL,
  `ruolo` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `ruoli`
--

INSERT INTO `ruoli` (`attore`, `film`, `ruolo`) VALUES
(1, 1, 'Jake Sully'),
(2, 1, 'Neytiri'),
(3, 1, 'col. Miles Quar'),
(4, 1, 'Trudy Chacon');

-- --------------------------------------------------------

--
-- Struttura della tabella `sotto_categoria`
--

CREATE TABLE `sotto_categoria` (
  `id_composto` int(11) NOT NULL,
  `id_componente` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Struttura della tabella `supporto_audio`
--

CREATE TABLE `supporto_audio` (
  `id` int(11) NOT NULL,
  `titolo` varchar(30) NOT NULL,
  `tipo` varchar(30) NOT NULL,
  `album` int(11) NOT NULL,
  `artista` int(11) NOT NULL,
  `prodotto` int(11) DEFAULT NULL,
  `genere` varchar(45) DEFAULT NULL,
  `anno_uscita` varchar(45) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `supporto_audio`
--

INSERT INTO `supporto_audio` (`id`, `titolo`, `tipo`, `album`, `artista`, `prodotto`, `genere`, `anno_uscita`) VALUES
(1, 'Help!', 'CD', 1, 1, 2, 'Rock', '1965'),
(2, 'Vide Noir', 'CD', 2, 2, 7, 'Indie', '2018'),
(3, 'The Rise and Fall Of Ziggy Sta', 'Vinile', 3, 3, 8, 'Rock', '1972');

-- --------------------------------------------------------

--
-- Struttura della tabella `supporto_cartaceo`
--

CREATE TABLE `supporto_cartaceo` (
  `id` int(11) NOT NULL,
  `tipo` varchar(45) DEFAULT NULL,
  `titolo` varchar(50) NOT NULL,
  `genere` varchar(30) NOT NULL,
  `autore` int(11) NOT NULL,
  `editore` int(11) NOT NULL,
  `ISBN` int(11) NOT NULL,
  `pagine` int(11) NOT NULL,
  `anno_uscita` int(11) NOT NULL,
  `prodotto` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `supporto_cartaceo`
--

INSERT INTO `supporto_cartaceo` (`id`, `tipo`, `titolo`, `genere`, `autore`, `editore`, `ISBN`, `pagine`, `anno_uscita`, `prodotto`) VALUES
(1, 'libro', 'Il trono di spade: un gioco di troni', 'Romanzo', 1, 1, 2147483647, 829, 1996, 4),
(2, 'libro', 'Harry Potter e la pietra filosofale', 'Fantasy', 2, 2, 214748399, 900, 1997, 11),
(3, 'libro', 'Genesi', 'Religione', 3, 3, 994748364, 300, 2017, 12);

-- --------------------------------------------------------

--
-- Struttura della tabella `supporto_video`
--

CREATE TABLE `supporto_video` (
  `id` int(11) NOT NULL,
  `anno_uscita` int(11) NOT NULL,
  `prodotto` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `supporto_video`
--

INSERT INTO `supporto_video` (`id`, `anno_uscita`, `prodotto`) VALUES
(1, 2009, 1),
(2, 2019, 3),
(3, 1998, 6),
(4, 2014, 5),
(5, 1998, 9),
(6, 1999, 10);

-- --------------------------------------------------------

--
-- Struttura della tabella `sviluppatore`
--

CREATE TABLE `sviluppatore` (
  `id` int(11) NOT NULL,
  `nome` varchar(45) NOT NULL,
  `sede` varchar(45) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `sviluppatore`
--

INSERT INTO `sviluppatore` (`id`, `nome`, `sede`) VALUES
(1, 'From Software', 'Giappone'),
(2, 'Naughty Dog', 'Stati Uniti'),
(3, 'Activison', 'Stati Uniti');

-- --------------------------------------------------------

--
-- Struttura della tabella `utente`
--

CREATE TABLE `utente` (
  `id` int(11) NOT NULL,
  `email` varchar(30) NOT NULL,
  `password` varchar(15) NOT NULL,
  `nome` varchar(15) NOT NULL,
  `cognome` varchar(15) NOT NULL,
  `data_nascita` varchar(15) NOT NULL,
  `indirizzo` int(11) NOT NULL,
  `carta` int(11) NOT NULL,
  `telefono` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `utente`
--

INSERT INTO `utente` (`id`, `email`, `password`, `nome`, `cognome`, `data_nascita`, `indirizzo`, `carta`, `telefono`) VALUES
(0, 'ierardidaniele@gmail.com', 'danielei', 'Daniele', 'Ierardi', '18/05/1995', 1, 0, '3490030746'),
(1, 'andreierardi@gmail.com', 'password', 'Andrea', 'Ierardi', '02/01/1997', 1, 1, '3490030746'),
(2, 'marcorizzi@gmail.com', 'rizzimarcolino', 'Marco', 'Rizzi', '18/06/1996', 2, 2, '3333333331');

-- --------------------------------------------------------

--
-- Struttura della tabella `videogioco`
--

CREATE TABLE `videogioco` (
  `id` int(11) NOT NULL,
  `titolo` varchar(45) NOT NULL,
  `dvd` int(11) NOT NULL,
  `sviluppatore` int(11) DEFAULT NULL,
  `genere` varchar(45) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dump dei dati per la tabella `videogioco`
--

INSERT INTO `videogioco` (`id`, `titolo`, `dvd`, `sviluppatore`, `genere`) VALUES
(1, 'Sekiro', 2, 1, 'Avventura'),
(2, 'Crash Bandicoot', 5, 2, 'Platform'),
(3, 'Spyro', 6, 3, 'Azione');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `album`
--
ALTER TABLE `album`
  ADD PRIMARY KEY (`id`,`titolo`);

--
-- Indici per le tabelle `artista`
--
ALTER TABLE `artista`
  ADD PRIMARY KEY (`id`,`nome`);

--
-- Indici per le tabelle `attore`
--
ALTER TABLE `attore`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `autore`
--
ALTER TABLE `autore`
  ADD PRIMARY KEY (`id`,`nome`,`cognome`);

--
-- Indici per le tabelle `canzone`
--
ALTER TABLE `canzone`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `carrello`
--
ALTER TABLE `carrello`
  ADD PRIMARY KEY (`id`,`utente`);

--
-- Indici per le tabelle `carta`
--
ALTER TABLE `carta`
  ADD PRIMARY KEY (`id`,`numero`);

--
-- Indici per le tabelle `categoria`
--
ALTER TABLE `categoria`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `cont_carrello`
--
ALTER TABLE `cont_carrello`
  ADD PRIMARY KEY (`carrello`,`prodotto`);

--
-- Indici per le tabelle `cont_ordine`
--
ALTER TABLE `cont_ordine`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `editore`
--
ALTER TABLE `editore`
  ADD PRIMARY KEY (`id`,`nome`);

--
-- Indici per le tabelle `film`
--
ALTER TABLE `film`
  ADD PRIMARY KEY (`id`,`dvd`,`titolo`);

--
-- Indici per le tabelle `indirizzo`
--
ALTER TABLE `indirizzo`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `ordine`
--
ALTER TABLE `ordine`
  ADD PRIMARY KEY (`id`,`utente`);

--
-- Indici per le tabelle `prenotazione`
--
ALTER TABLE `prenotazione`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `prodotto`
--
ALTER TABLE `prodotto`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `recensione`
--
ALTER TABLE `recensione`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `regista`
--
ALTER TABLE `regista`
  ADD PRIMARY KEY (`id`,`nome`,`cognome`);

--
-- Indici per le tabelle `ruoli`
--
ALTER TABLE `ruoli`
  ADD PRIMARY KEY (`film`,`attore`);

--
-- Indici per le tabelle `sotto_categoria`
--
ALTER TABLE `sotto_categoria`
  ADD PRIMARY KEY (`id_componente`,`id_composto`);

--
-- Indici per le tabelle `supporto_audio`
--
ALTER TABLE `supporto_audio`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `supporto_cartaceo`
--
ALTER TABLE `supporto_cartaceo`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `supporto_video`
--
ALTER TABLE `supporto_video`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `sviluppatore`
--
ALTER TABLE `sviluppatore`
  ADD PRIMARY KEY (`id`,`nome`);

--
-- Indici per le tabelle `utente`
--
ALTER TABLE `utente`
  ADD PRIMARY KEY (`id`),
  ADD KEY `indirizzo_utente` (`indirizzo`),
  ADD KEY `carta_utente` (`carta`);

--
-- Indici per le tabelle `videogioco`
--
ALTER TABLE `videogioco`
  ADD PRIMARY KEY (`id`,`titolo`,`dvd`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `album`
--
ALTER TABLE `album`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `artista`
--
ALTER TABLE `artista`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `attore`
--
ALTER TABLE `attore`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT per la tabella `autore`
--
ALTER TABLE `autore`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `canzone`
--
ALTER TABLE `canzone`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT per la tabella `categoria`
--
ALTER TABLE `categoria`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT per la tabella `cont_ordine`
--
ALTER TABLE `cont_ordine`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=71;

--
-- AUTO_INCREMENT per la tabella `editore`
--
ALTER TABLE `editore`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `film`
--
ALTER TABLE `film`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `prenotazione`
--
ALTER TABLE `prenotazione`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT per la tabella `prodotto`
--
ALTER TABLE `prodotto`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT per la tabella `regista`
--
ALTER TABLE `regista`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `supporto_audio`
--
ALTER TABLE `supporto_audio`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `supporto_cartaceo`
--
ALTER TABLE `supporto_cartaceo`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `supporto_video`
--
ALTER TABLE `supporto_video`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT per la tabella `sviluppatore`
--
ALTER TABLE `sviluppatore`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT per la tabella `videogioco`
--
ALTER TABLE `videogioco`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Limiti per le tabelle scaricate
--

--
-- Limiti per la tabella `utente`
--
ALTER TABLE `utente`
  ADD CONSTRAINT `carta_utente` FOREIGN KEY (`carta`) REFERENCES `carta` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `indirizzo_utente` FOREIGN KEY (`indirizzo`) REFERENCES `indirizzo` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
