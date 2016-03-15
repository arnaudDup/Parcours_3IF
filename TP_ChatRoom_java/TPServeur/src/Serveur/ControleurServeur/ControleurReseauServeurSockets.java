package Serveur.ControleurServeur;

import java.net.InetAddress;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;

import Serveur.ControleurServeur.ControleurSe;
import Serveur.ManageServeur.Chat;
import Serveur.ManageServeur.Utilisateur;
import Common.Message;
import Protocole.NoeudReseauServeur;
import Protocole.OnClientDisconnect;
import Protocole.OnMessageReceived;

public class ControleurReseauServeurSockets{
	ControleurSe controleur; 
	NoeudReseauServeur serveurSocket;

	public ControleurReseauServeurSockets (final ControleurSe controleur)
	{
		this.controleur = controleur;
		
		// On crï¿½e un Socket Serveur
		serveurSocket = new NoeudReseauServeur(2000);
		
		//Initialisation du callback de reception
		// Dans ce cas, lorsque l'on va recevoir un message, on appelle la methode TraiterMessage du Controleur
		serveurSocket.OnMessageReceived(new OnMessageReceived(){
			@Override
			public void todo(int Sender, HashMap<String, Object> message) {
				TraiterMessage(Sender, message);
			}			
		});
		
		// Initialisation du callback de deconnexion d'un utilisateur
		serveurSocket.OnDisconnect(new OnClientDisconnect(){
			@Override
			public void todo(int Sender) {
				
				// On enleve l'utilisateur du modele
				controleur.getModele().deconnecterUtilisateurServeur(Sender);
				
				// On enleve l'utilisateur du serveur
				serveurSocket.enleverSocket(Sender);
				controleur.log("Deconnexion de "+Sender);
			}			
		});
		// On demarre le serveur
		serveurSocket.lancerServeur();
	}


	public void TraiterMessage(int sender, HashMap<String, Object> message)
	{
		if(message == null)
		{
			System.out.println("Erreur lors de la reception du message. (HashMap null)");
			return;
		}
		
		String event = (String) message.get("Event");
		
		switch(event)
		{
			case "ConnecterServeur":
				ConnecterServeur(sender, message);
			break;
			
			case "ConnecterChat":
				ConnecterChat(sender, message);
			break;
			
			case "EnvoyerMessageChat":
				EnvoyerMessageChat(sender, message);
			break;
			
			case "DeconnecterChat":
				DeconnecterChat(sender, message);
			break;
			
			case "AjouterChat":
				AjouterChat(sender, message);
			break;
			
			case "EnvoyerMessagePrivee":
				EnvoyerMessagePrivee(sender, message);
			break;
		}		
	}
	
	private void EnvoyerMessagePrivee(int sender,HashMap<String, Object> message) {
		// On récupère les informations du message recu
		int userID = (Integer) message.get("userID");
		System.out.println("mp to :"+userID);
		String contenu = (String) message.get("contenu");
		String nom = controleur.getUserByID(sender).getNom();		
		Message m = new Message(contenu,nom);
		
		// On crée le message a envoyer au destinnataire
		HashMap<String, Object> msg = new HashMap<String, Object>();
		msg.put("Event", "ReceptionMessagePrivee");
		msg.put("userID",  sender);
		msg.put("message", m);
		
		// On envoie le message		
		serveurSocket.envoyerMessage(msg, userID);		
	}


	private void AjouterChat(int sender, HashMap<String, Object> message) {
		// On recupï¿½re le nom du chat
		String nom = (String) message.get("chatNom");
		
		// On l'ajoute a la liste de chat actuelle
		Chat c = controleur.getModele().ajouterChat(nom);
		
		controleur.log("Ajout du chat : "+nom);
		
		
		// On notifie tout les utilisateurs du nouveau chat		
			// On crï¿½e le message a envoyer
		HashMap<String, Object> msg = new HashMap<String, Object>();
		msg.put("Event", "NouveauChat");
		msg.put("chatID",  c.getIDChat());
		msg.put("chatNom", c.getnomChat());
		
			// On parcours la liste des utilisateur pour leur envoyer un message
		
		Iterator<Integer> i = controleur.getModele().getListeUtilisateurs().keySet().iterator();
		
		while(i.hasNext())
		{
			serveurSocket.envoyerMessage(msg, i.next());
		}
	}

	public void DeconnecterChat(int sender, HashMap<String, Object> message)
	{
		// On recupï¿½re l'ID du chat ou le client veut se connecter
		int chatID = new Integer(""+message.get("chatID"));
		
		// On rï¿½cupï¿½re l'utilisateur depuis son IP
		Utilisateur user = controleur.getUserByID(sender);
		
		// On rï¿½cupï¿½re le chat
		Chat chat = controleur.getModele().getChats().get(chatID);
		
		// On dï¿½sinscrit l'utilisateur a ce chat
		chat.enleverUtilisateur(user);
		
		controleur.log("Deconnexion de "+user.getNom());
		
		// On notifie du changement du nb utilisateur
		
		
		// Crï¿½ation du message a envoyer aux utilisateurs
		// Creation du message a envoyer aux utilisateurs
		HashMap<String,Object> event2 = new HashMap<String,Object>();		
		event2.put("Event", "DecoCoUser");	
		event2.put("nbUsers", chat.getlisteUtilissateur().size());
		event2.put("chatID", chatID);
		event2.put("userID", controleur.getUserByID(sender).getID());
		event2.put("connexion", false);	
		
		// Envoi du messages aux utilisateurs abonnï¿½s au chat
		Iterator<Utilisateur> i = controleur.getModele().getChats().get(chatID).getlisteUtilissateur().iterator();
		
		while(i.hasNext())
		{
			Utilisateur courant = i.next();
			
			// On envoi le message		
			serveurSocket.envoyerMessage(event2, courant.getIDClient());
		}
		
	}
	
	public void ConnecterServeur(int sender, HashMap<String, Object> message)
	{
		controleur.getModele().ajouterUtilisateur((String) message.get("nom"), sender);
		
		// On retourne a l'utilisateur un message de connexion ï¿½tablie
		HashMap<String,Object> event = new HashMap<String,Object>();		
		event.put("Event", "ConnexionEtablie");	
		
		// On lui donne ï¿½galement la liste des chats actuels
			// -- Cette liste sera reprresente pas un HashMap associant l'ID du chat et son nom
		HashMap<Integer,String> ChatReference = new HashMap<Integer,String>();

		System.out.println("Recupï¿½reation des chats");
		for(int i=0; i< controleur.getModele().getChats().size() ; i++) 
        {
			// On rï¿½cupï¿½re l'ID du chat
			int id = controleur.getModele().getChats().get(i).getIDChat();
			
			// On rï¿½cupï¿½re le nom du chat
			String nomDuChat =  controleur.getModele().getChats().get(i).getnomChat();
			
			// On l'ajoute a la map
			ChatReference.put(id,nomDuChat);
			System.out.println(id+" "+nomDuChat);
        }
		
		// On ajoute cette liste dans le message a envoyer
		event.put("Chats", ChatReference);	
	
		// On envoi le message		
		serveurSocket.envoyerMessage(event, sender);

		// on affiche la connexion de l'utilisateur dans la fenÃ©tre graphque Ã  l'aide du controleur.
		// afin d'avoir une vue d'ensemble sur les utilisateurs de notre rÃ©seau.
		controleur.log("nouvelle connexion  "+ (String) message.get("nom")+"("+sender+")");
	}

	public void ConnecterChat(int sender, HashMap<String, Object> message)
	{
		// On recupï¿½re l'ID du chat ou le client veut se connecter
		int chatID = new Integer(""+message.get("chatID"));
		
		// On rï¿½cupï¿½re l'utilisateur depuis son IP
		Utilisateur user = controleur.getUserByID(sender);
		
		// On rï¿½cupï¿½re le chat
		Chat chat = controleur.getModele().getChats().get(chatID);
		
		// nous vÃ©rifions que l'utilisateur n'appartient deja au chat
		Iterator<Utilisateur> iter = chat.getlisteUtilissateur().iterator();
		while(iter.hasNext())
		{
			Utilisateur courant = iter.next();	
			if (user == courant)
			{
				HashMap<String, Object> event = new HashMap<String, Object>();
				event.put("chatID", chat.getIDChat());
				event.put("Event", "UtilisateurDejaConnecte");
				
				// On envoie le message rï¿½ponse
				serveurSocket.envoyerMessage(event, sender);
				return;
				
			}
		}
		
		
		// On inscrit l'utilisateur a ce chat
		chat.ajouterUtilisateur(user);

		System.out.println("S : user ajoutï¿½ au chat : "+sender);
		
		// On lui envoi un message avec la liste des messages actuel du chat
		HashMap<String, Object> event = new HashMap<String, Object>();
		
		// On rï¿½cupï¿½re la liste actuelle de messages 
		LinkedList<Message> messages = controleur.getModele().getChats().get(chatID).getMessages();

		// Creation du hashmap de users ------------------------------------------------------------------
		HashMap<Integer,String> users = new HashMap<Integer, String>();
		
		Iterator<Utilisateur> j = controleur.getModele().getChats().get(chatID).getlisteUtilissateur().iterator();
		
		while(j.hasNext())
		{
			Utilisateur courant = j.next();
			
			System.out.println("id:"+courant.getID());
			// On rempli le hashmap
			users.put(courant.getID(), courant.getNom());	
		}
		
		// on construit le message reponse
		event.put("nbUsers", chat.getlisteUtilissateur().size());
		event.put("messages", messages);
		event.put("chatID", chatID);
		event.put("Event", "ConnexionChatAcceptee");
		event.put("users", users);
		
				
		// On envoie le message reponse
		serveurSocket.envoyerMessage(event, sender);
		
		// On notifie les utilisateurs du nouvel arrivant
		// Creation du message a envoyer aux utilisateurs
		HashMap<String,Object> event2 = new HashMap<String,Object>();		
		event2.put("Event", "DecoCoUser");	
		event2.put("nbUsers", chat.getlisteUtilissateur().size());
		event2.put("userNom", user.getNom());
		event2.put("userID", user.getID());
		event2.put("chatID", chatID);
		event2.put("connexion", true);	
		 
		// Envoi du messages aux utilisateurs abonnï¿½s au chat --------------------------------------------
		Iterator<Utilisateur> i = controleur.getModele().getChats().get(chatID).getlisteUtilissateur().iterator();
		
		while(i.hasNext())
		{
			Utilisateur courant = i.next();
			if (user != courant)
			{
				// On envoi le message		
				serveurSocket.envoyerMessage(event2, courant.getIDClient());
			}
		}
	}

	public void EnvoyerMessageChat(int sender, HashMap<String, Object> message)
	{
		// On rï¿½cupï¿½re le contenu du message
		String contenu = (String) message.get("contenu");
		
		// On rï¿½cupï¿½re l'ID du chat
		int chatID = (Integer) message.get("chatID");
				
		// On rï¿½cupï¿½re le nom d'utilisateur
		String nomUtilisateur = controleur.getUserByID(sender).getNom();
		
		// On crï¿½e le nouveau message puis on l'ajoute dans le chat
		Message nouveauMessage = new Message (contenu, nomUtilisateur);
		controleur.getModele().getChats().get(chatID).ajouterMessage(nouveauMessage);
		
		// On crï¿½e le nouveau message puis on l'ajoute dans le chat
		Message nouveauMessage2 = new Message (contenu, nomUtilisateur);
		
		controleur.log(nomUtilisateur+"("+chatID+"): "+contenu);
		// On notifie les utilisateur abonnï¿½es au chat
		
			// Crï¿½ation du message a envoyer aux utilisateurs 
		HashMap<String,Object> event = new HashMap<String,Object>();		
		event.put("Event", "MessageRecu");	
		event.put("message", nouveauMessage);
		event.put("chatID", chatID);
		
		// Crï¿½ation du message au sender
		nouveauMessage2.setSource(true);
		nouveauMessage2.setNom("you");
		HashMap<String,Object> event2 = new HashMap<String,Object>();		
		event2.put("Event", "MessageRecu");	
		event2.put("message", nouveauMessage2);
		event2.put("chatID", chatID);
		
		// Envoi du messages aux utilisateurs abonnï¿½s au chat
		Iterator<Utilisateur> i = controleur.getModele().getChats().get(chatID).getlisteUtilissateur().iterator();
		
		
		while(i.hasNext())
		{
			Utilisateur courant = i.next();
			
			if (courant.getID()==sender)
			{
				serveurSocket.envoyerMessage(event2, courant.getIDClient());
			}	
			else
				serveurSocket.envoyerMessage(event, courant.getIDClient());
		}
	}
	
}