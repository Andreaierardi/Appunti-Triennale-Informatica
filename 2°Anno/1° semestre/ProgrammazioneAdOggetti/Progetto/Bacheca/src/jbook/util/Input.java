package jbook.util;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Vector;

/** 
    Una semplice classe per leggere stringhe e numeri 
    dallo standard input.
*/

public class Input{
    
    private static BufferedReader reader = 
	new BufferedReader(new InputStreamReader(System.in));
    
    /**
       Legge una linea di input. Nell'improbabile caso di una
       IOException, il programma termina. 
       @return restituisce la linea di input che l'utente ha battuto.
    */
    public static String readString(){  
	String inputLine = "";
	try{  
	    inputLine = reader.readLine();
	}
	catch(IOException e){  
	    System.out.println(e);
	    System.exit(1);
	}
	return inputLine;
    }
    
    public static String readString(String msg){ 
	System.out.print(msg); 
	String inputLine = readString();
	return inputLine;
    }
    
    /**
       Legge una linea di input e la converte in un byte.
       Eventuali spazi bianchi prima e dopo l'intero vengono ignorati.
       @return l'intero dato in input dall'utente
    */
    public static byte readByte(){  
	String inputString = readString();
	inputString = inputString.trim();
	byte n = Byte.parseByte(inputString);
	return n;
    }
   
    public static byte readByte(String msg){  
	System.out.print(msg); 
	byte n = readByte();
	return n;
    }
   
    /**
       Legge una linea di input e la converte in uno short.
       Eventuali spazi bianchi prima e dopo l'intero vengono ignorati.
       @return l'intero dato in input dall'utente
    */
    public static short readShort(){  
	String inputString = readString();
	inputString = inputString.trim();
	short n = Short.parseShort(inputString);
	return n;
    }
   
    public static short readShort(String msg){  
	System.out.print(msg); 
	short n = readShort();
	return n;
    }
   
    /**
       Legge una linea di input e la converte in un int.
       Eventuali spazi bianchi prima e dopo l'intero vengono ignorati.
       @return l'intero dato in input dall'utente
    */
    public static int readInt(){  
	String inputString = readString();
	inputString = inputString.trim();
	int n = Integer.parseInt(inputString);
	return n;
    }
   
    public static int readInt(String msg){  
	System.out.print(msg); 
	int n = readInt();
	return n;
    }
   
    /**
       Legge una linea di input e la converte in un long.
       Eventuali spazi bianchi prima e dopo l'intero vengono ignorati.
       @return l'intero dato in input dall'utente
    */
    public static long readLong(){  
	String inputString = readString();
	inputString = inputString.trim();
	long n = Long.parseLong(inputString);
	return n;
    }
   
    public static long readLong(String msg){  
	System.out.print(msg); 
	long n = readLong();
	return n;
    }
   
    /**
       Legge una linea di input e la converte in un numero
       in virgola mobile a precisione singola.  Eventuali spazi bianchi prima e
       dopo il numero vengono ignorati.
       @return il numero dato in input dall'utente 
    */
    public static float readFloat(){  
	String inputString = readString();
	inputString = inputString.trim();
	float x = Float.parseFloat(inputString);
	return x;
    }

    public static float readFloat(String msg){  
	System.out.print(msg); 
	float x = readFloat();
	return x;
    }


    /**
       Legge una linea di input e la converte in un numero
       in virgola mobile a precisione doppia.  Eventuali spazi bianchi prima e
       dopo il numero vengono ignorati.
       @return il numero dato in input dall'utente 
    */
    public static double readDouble(){  
	String inputString = readString();
	inputString = inputString.trim();
	double x = Double.parseDouble(inputString);
	return x;
    }

    public static double readDouble(String msg){  
	System.out.print(msg); 
	double x = readDouble();
	return x;
    }


    /**
       Legge una linea di input e ne estrae il primo carattere.  
       @return il primo carattere della riga data in input dall'utente 
    */
    public static char readChar(){  
	String inputString = readString();
	char c = inputString.charAt(0);
	return c;
    }

    public static char readChar(String msg){  
	System.out.print(msg); 
	char c = readChar();
	return c;
    }

    /**
       Legge una linea di input e restituisce true se la stringa
       e' equals a "true" a meno di maiuscole e minuscole, false altrimenti.  
       @return il booeano dato in input dall'utente 
    */
    public static boolean readBool(){  
	String inputString = readString();
	inputString = inputString.trim();
	boolean b = Boolean.parseBoolean(inputString);
	return b;
    }

    public static boolean readBool(String msg){  
	System.out.print(msg); 
	boolean b = readBool();
	return b;
    }


    /**
       Legge una sequenza di stringhe conclusa dalla stringa vuota e
       restituisce la sequenza in un nuovo array di stringhe.
       @return l'array delle stringhe date in input dal'utente
    */
    public static String[] readSeq(){ 
	String[] seq = readSeq("");
	return seq;
    }

    public static String[] readSeq(String prompt){ 
	Vector<String> seqTemp = new Vector<String>(); 
	System.out.print(prompt);
	String inputString = readString();
	while (inputString.length()>0) {
	    seqTemp.add(inputString);
	    System.out.print(prompt);
	    inputString = readString();
	}
	String[] seq = new String[seqTemp.size()];
	return seqTemp.toArray(seq);
    }

    public static String[] readSeq(String msg, String prompt){ 
	System.out.println(msg); 
	String[] seq = readSeq(prompt);
	return seq;
    }

}
