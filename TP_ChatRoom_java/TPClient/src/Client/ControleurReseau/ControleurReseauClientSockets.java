package Client.ControleurReseau;

import java.net.InetAddress;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;

import Common.Message;
import Protocole.NoeudReseauClient;
import Protocole.OnMessageReceived;




public class ControleurReseauClientSockets implements IControleurReseauClient {
	private Controleur controleur;
	private NoeudReseauClient noeudClient;
	private int port = 2000;
	
	
	public ControleurReseauClientSockets(Controleur controleur)
	{
		this.controleur = controleur;

	}

	private void initNoeud(InetAddress ip)
	{
		// On instancie le noeud
		noeudClient = new NoeudReseauClient(ip, port);
		
		// On definit le call back de reception de message
		noeudClient.OnMessageReceived(new OnMessageReceived(){

			@Override
			public void todo(InetAddress Sender, HashMap<String, Object> message) {
				// Lorsqu'on recoi un message, on le consid�re dans l'automate
				controleur.considererEvent(message);
			}
			
		});
		
		// On lance la lecture de message sur ce noeud
		noeudClient.lireMessage();
	}
	
	@Override
	public void connecterServeur(String nom, InetAddress adressIP) {
		System.out.println("Connexion � "+controleur.getIpServeur()+"...");	
		
		// On instancie le noeudClient
		initNoeud(adressIP);
		
		// On cr�e le message
		HashMap<String, Object> msg = new HashMap<String, Object>();
		
		msg.put("Event", "ConnecterServeur");
		msg.put("nom", nom);
		
		// on envoie le message
		noeudClient.envoyerMessage(msg);
	}
	
	

	public void connecterChat(int chatid)
	{	
		// On construit le message
		HashMap<String,Object> event2 = new HashMap<String,Object> ();
		event2.put("Event", "ConnecterChat");
		event2.put("chatID", chatid);
		
		// on envoie le message
		noeudClient.envoyerMessage(event2);		
		System.out.println("connexion to "+chatid);
		
	}

	@Override
	public void envoyerMessageChat(String contenu, int chatid) {
		
	// On construit le message
		HashMap<String,Object> event2 = new HashMap<String,Object> ();
		event2.put("Event", "EnvoyerMessageChat");
		event2.put("chatID", chatid);
		event2.put("contenu", contenu);
		
	// on envoie le message
		noeudClient.envoyerMessage(event2);
	}

	@Override
	public void deconnecterChat(int chatid) {
	
	// On construit le message
		HashMap<String,Object> event2 = new HashMap<String,Object> ();
		event2.put("Event", "DeconnecterChat");
		event2.put("chatID", chatid);
			
	// on envoie le message
		noeudClient.envoyerMessage(event2);
	}

	@Override
	public void ajouterChat(String nomChat) {
		
		// On construit le message
		HashMap<String,Object> event2 = new HashMap<String,Object> ();
		event2.put("Event", "AjouterChat");
		event2.put("chatNom", nomChat);
			
		// on envoie le message
		noeudClient.envoyerMessage(event2);
	}

	@Override
	public void envoyerMessagePrive(int userID, String text) {
		
	// On construit le message
		HashMap<String,Object> event2 = new HashMap<String,Object> ();
		event2.put("Event", "EnvoyerMessagePrivee");
		event2.put("userID", userID);
		event2.put("contenu", text);
		
	// on envoie le message
		noeudClient.envoyerMessage(event2);
	}
	
}