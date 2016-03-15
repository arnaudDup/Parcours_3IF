package Protocole;


import java.io.BufferedReader;
import java.io.EOFException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.HashMap;
import java.util.Map.Entry;

import Serveur.ControleurServeur.GestionnaireID;

public class NoeudReseauServeur {
	
	ServerSocket serveurSocket;
	boolean isClient;
	String IP;
	int port;	
	boolean statusServeur;
	private OnClientConnect callBackConnect;
	private OnMessageReceived callBackMessageReception;
	private OnClientDisconnect callBackDisconnect;
	
	// mapping de l'utilisateur, du socket utilis√© et de son ID
	HashMap<Integer ,Socket> sockets;
	HashMap<Integer, LectureMessageThread> threadsLectureMessage;
	HashMap<Socket,ObjectOutputStream> fluxSorties; // mapping necÈssaire ‡ l'Ècriture sur le flux d'un socket envoi de message)
	
	
	public NoeudReseauServeur(int port)
	{
		// Instanciation du serveur socket
		try {
			serveurSocket = new ServerSocket(port);
			System.out.println("Demarrage du serveur sur "+serveurSocket.getInetAddress());
		} catch (IOException e) {e.printStackTrace();}
		
		this.port = port;
		
		fluxSorties = new HashMap<Socket,ObjectOutputStream>();
		sockets = new HashMap<Integer,Socket>();
		threadsLectureMessage = new HashMap<Integer,LectureMessageThread>();
		
	}
	
	public void OnClientConnect(OnClientConnect callBackConnect)
	{
		this.callBackConnect = callBackConnect;
	}
	
	public void OnMessageReceived(OnMessageReceived callBackConnect)
	{
		this.callBackMessageReception = callBackConnect;
	}
	
	public void lancerServeur()
	{
		new Thread(new Runnable(){

			@Override
			public void run() {
				statusServeur = true;
				// Tant que le serveur est en marche on attends une connexion
				while(statusServeur)
				{
					attendreConnexion();
				}
			}
			
		}).start();
	}
	
	public void arreterServeur() throws IOException
	{
		// On arrete le thread d'attente de connexion
		statusServeur = false;
		
		// On deconnecte tous les sockets connect√©s
		for(Entry<Integer, Socket> entry : sockets.entrySet()) {
			// on envoi un message
			deconnexionSocket(entry.getValue());
		}	
		
		// je ferme le socket d'√©coute.
		serveurSocket.close();
		
		
	}
	
	public void deconnexionSocket(Integer UserID) throws IOException
	{
		deconnexionSocket(sockets.get(UserID));
	}
	
	public void deconnexionSocket(Socket socketAFermer) throws IOException
	{
		InetAddress ip = socketAFermer.getInetAddress();
		
		// On ferme les flux du socket
		socketAFermer.getInputStream().close();
		socketAFermer.getOutputStream().close();
		socketAFermer.close();
		sockets.remove(ip);
		
		// On arrete le thread de lecture 		
		threadsLectureMessage.get(ip).stopLecture();		
		threadsLectureMessage.remove(ip);
		
		System.out.println("Deconnexion de "+ip);
	}
	
	private void attendreConnexion()
	{
		Socket clientSocket = new Socket();
		//On attend une connexion
		try {
				
				clientSocket = serveurSocket.accept();
		} catch (IOException e) {
			
			e.printStackTrace();
		} // Accept appel bloquant
		
		// Lorsqu'on a une connexion, on ajoute le socket dans notre dictionnaire de socket
		int userID = ajouterSocket(clientSocket);
		
		// on appelle le callback de connexion
		if(callBackConnect!= null) callBackConnect.todo(userID);
	}
	
	/**
	 * Cette mÈthode permet d'ajouter un socket client a l'hashMap de clients.
	 * Elle dÈmarre Ègalement le thread de lecture des messages et ajoute le flux de sortie
	 * ‡ l'hashMap de flux de sortie.
	 * @param clientSocket
	 * @return elle retourne l'ID de l'user ajoutÈ
	 */
	
	private int ajouterSocket(Socket clientSocket) {		
		Integer userID= GestionnaireID.getUserId();
				
		System.out.println("Ajout de "+userID + " IP: "+clientSocket.getInetAddress());
		
		// On ajoute le flux de sortie a l'hashmap de flux de sortie
		try {
			fluxSorties.put(clientSocket, new ObjectOutputStream(clientSocket.getOutputStream()));
		} catch (IOException e) {e.printStackTrace();}		

		System.out.println(userID+"->"+clientSocket.getLocalPort());
		// On ajoute notre socket dans le dictionnaire de socket
		sockets.put(userID, clientSocket);
		
		// On cr√©e un thread de leture de message sur ce socket
		LectureMessageThread lecteurMessages = new LectureMessageThread(clientSocket,this,userID);
		
		// On ajoute ce thread dans notre dictionnaire de thread de lecture
		threadsLectureMessage.put(userID, lecteurMessages);
		
		// On d√©marre le thread de lecture
		lecteurMessages.start();
		
		return userID;
	}
	

	
	public void envoyerMessage(final HashMap msg, final int userID)
	{
		new Thread(new Runnable(){
		@Override
		public void run() {

				// On rÈcupËre l'utilisateur
				Socket s = sockets.get(userID);
				if(s == null) {
					System.out.println("Destinataire introuvable !");
					return;
				}
				
				if(envoyerMessage(s,msg))
					System.out.println("S : Message envoyÈ !");
				else
					System.out.println("Erreur d'envoi");
			}
		}).start();
		
	}
	
	public void enleverSocket(int userID)
	{
		// On enleve le socket
		Socket s = sockets.get(userID);
		
		try {
			fermerFluxSocket(s);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			System.out.println("Erreur fermeture flux.\n"+e.getMessage()+"["+e.getClass().getName()+"]");
		}
		
		// On me supprime de la liste
		sockets.remove(userID);
		
	}
	
	public void fermerFluxSocket(Socket s) throws IOException
	{
		s.getInputStream().close();
		s.getOutputStream().close();
		s.close();
	}
	
	public boolean envoyerMessage(Socket s, Object msg)
	{	
		System.out.println("S : Envoi en cours... a "+s.getInetAddress());
		
		// On rÈcupËre le flux de sortie correspondant au socket
		ObjectOutputStream socOut = fluxSorties.get(s);

		
		  // Controler la validite du flux de sortie
	      //
	      if (socOut == null) return false;
	      
	      // Transferer le message dans le flux de sortie
	      //
	      // On fait une section critique car plusieurs thread peuvent ecrir sur sockout
    	    synchronized (socOut) {
  	
    	    	try {socOut.writeObject(msg);}
    	    	catch(Exception e){
    	    		System.out.println(e.getMessage()+"["+e.getClass().getName()+"]");
		   		  return false;
		   		  }
		   	  
		   	
    return true;
      	  }
  
	}
	
	public void envoyerMessageBroadCast(HashMap msg)
	{
		// On r√©cup√®re les clefs du hashmap
		// Iterator<InetAddress> keys = sockets.keySet().iterator();
		
		// Pour chaque socket de notre dictionnaire
		for(Entry<Integer, Socket> entry : sockets.entrySet()) {
			// on envoi un message
		   envoyerMessage(entry.getValue(), msg);
		}	

	}

	public OnMessageReceived getCallBackMessageReception() {
		return callBackMessageReception;
	}

	public OnClientDisconnect getCallBackDisconnect() {
		return callBackDisconnect;
	}

	public void OnDisconnect(OnClientDisconnect callBackDisconnect) {
		this.callBackDisconnect = callBackDisconnect;
	}

}

//Thread de lecture de message
class LectureMessageThread extends Thread
{
	private Socket socket;
	private BufferedReader bufferedReader;
	private boolean statusLecture;
	private NoeudReseauServeur hamecon;
	private InetAddress IPClient;
	private ObjectInputStream socIn;
	private int UserID;
	
	public void stopLecture()
	{
		statusLecture = false;
	}
	
	public LectureMessageThread(Socket socket, NoeudReseauServeur hamecon, int UserID)
	{
		this.socket = socket;
		this.statusLecture = true;
		this.hamecon = hamecon;
		this.IPClient = socket.getInetAddress();
		this.UserID = UserID;
	}
	
	private void arreterLecture()
	{
		this.statusLecture = false;
	}
	
	
	
	public void run()
	{
		System.out.println("S : Lecteur de message de  "+UserID+" IP:"+ IPClient);
		// On r√©cup√®re le flux d'entr√© de notre socket
		// Initialisat
		try {
			socIn  = new ObjectInputStream(socket.getInputStream());
		} catch (IOException e1) {e1.printStackTrace();	} 
		
		
		while(statusLecture) // Tant que le thread de lecture est actif
		{
			attendreMessage();			
		}
		System.out.println("Fin thread lecture de "+UserID+" IP:"+IPClient);
		
		// On notifie le listener d'une reception		
		if(hamecon.getCallBackDisconnect() != null)
			hamecon.getCallBackDisconnect().todo(UserID);

	}
	
	public void attendreMessage()
	{
		Object msg = null;
		
		while(statusLecture)
		{
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
		      		 System.out.println("Object distant dÈtruit");
		      		 // On arrete le thread
		      		 statusLecture = false;
		      		 return;
		         }
		      	 
		      	 catch (Exception e){
		      		 
		      		 System.out.println("Erreur Reception !\n"+e.getMessage()+"\n ["+e.getClass().getName()+"]");
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
		
		System.out.println("S : Message recu");
		
		// On notifie le listener d'une reception		
		if(hamecon.getCallBackMessageReception() != null)
			hamecon.getCallBackMessageReception().todo(UserID, (HashMap) msg);
	}	

}