package Protocole;

import java.io.BufferedReader;
import java.io.EOFException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketException;
import java.util.HashMap;

public class NoeudReseauClient {
    Socket clientSocket;
    InetAddress IP;
	int port;
	private ObjectInputStream  socIn;             	// Buffer entree en mode "bytes"
	private ObjectOutputStream socOut;            	// Buffer sortie en mode "bytes"
	boolean statusLecture; 							// statut d'arret du thread
	private OnMessageReceived callBackMessageReception; // Listener de reception de message
	
	// Constructeur pour le client
	public NoeudReseauClient (InetAddress addressIp, int port)
	{
		// Création du socket et initialisation du flux
		try {
			clientSocket = new Socket(addressIp,port);
			initialisationFlux();
		} catch (Exception e) {e.printStackTrace();	}
			
		this.IP = clientSocket.getInetAddress();
		this.statusLecture = false;	
	}
	

	private void initialisationFlux() throws Exception
	{
		this.socOut = new ObjectOutputStream(clientSocket.getOutputStream()); 
	}
	
	public boolean envoyerMessageAsync (Object msg) {
      // Controler la validite du flux de sortie
      //
      if (socOut == null) return false;
      
      // Transferer le message dans le flux de sortie
      //
      try {socOut.writeObject(msg);}
   	  catch(Exception e){return false;}
   	  
      System.out.println("C : Message envoy�");
   	  return true;
   }  
	
	public boolean envoyerMessage (final Object msg) {
		
		  new Thread(new Runnable(){

			@Override
			public void run() {
				// TODO Auto-generated method stub
				envoyerMessageAsync (msg);
			}
			  
		  }).start();
		  
		  return true;
	   }  
	
	public void deconnexionClient()
	{
		// à voir avec le protocole de deconnexion et les map qu'on va utiliser 
		// Si hash map avec la connexion.
		
		
	}
	
	private void arreterLectureMessage()
	{
		statusLecture = false;
	}
	
	public void lireMessage()
	{
		statusLecture = true;
		// Thread de lecture du flux d'entrée
		// Thread possible "à la volée" car aucun attribut dans la construction du Thread.
		new Thread(new Runnable(){

			@Override
			public void run() {
				
				
				// Initialisation du flux d'entr�e
				try {
					socIn  = new ObjectInputStream(clientSocket.getInputStream());
				} catch (IOException e1) {e1.printStackTrace();	} 
				
				
				while(statusLecture) // Tant que le thread de lecture est actif
				{
					System.out.println("C :En attente de message");
					
					attendreMessage();
					
				}
				System.out.println("Fin thread lecture.");
			}
			
			
			
			public void attendreMessage()
			{
				Object msg = null;
				
				while(statusLecture)
				{
					System.out.println(".");
					try {
				            msg= socIn.readObject();
				      	    if (msg != null) break; // Quand on a un message, on sort de la boucle
				      	 }
				      	 
				      	 // Traiter le cas ou l'autre extremite de la socket disparait
				      	 // sans coordination prealable au niveau applicatif (OSI - 7).
				      	 //
				      	 // Ce cas se produit quand l'objet "socket" distant est detruit
				      	 // (mort du thread distant par exemple)
				      	 //                     
				      	 catch (SocketException e)
				         {
				      		 System.out.println("Object distant d�truit");
				      		 statusLecture = false; // On arrete le thread de lecture
				      		 return;
				         }
				      	 
				      	 catch (Exception e){
				      		 
				      		 System.out.println("Erreur Reception !\n"+e.getMessage()+"\n ["+e.getClass().getName()+"]");
				      		 statusLecture = false;
				      		 return;
				      	 }
				      	 
				      	 // Temporiser pour attendre le message suivant
						
				      	try {
							Thread.sleep(100);
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
			      }
				System.out.println("C : Message recu");
						
				// On notifie le listener d'une reception
				callBackMessageReception.todo(null, (HashMap) msg);			
			}	
			
		}).start();
		
	}


	public void OnMessageReceived(OnMessageReceived callBackMessageReception) {
		this.callBackMessageReception = callBackMessageReception;
		
	}

}

