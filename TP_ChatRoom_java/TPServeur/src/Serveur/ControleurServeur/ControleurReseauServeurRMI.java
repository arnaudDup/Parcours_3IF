package Serveur.ControleurServeur;


import java.net.InetAddress;
import java.rmi.RemoteException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map.Entry;

import Common.Message;
import Protocole.IControleurReseauClientRMI;
import Protocole.IControleurReseauRMI;
import Serveur.ManageServeur.Chat;
import Serveur.ManageServeur.Utilisateur;

/**
 * Classe permettant de gerer les communications entre le serveur et les client connectés.
 * La Classe s'appuie sur les protocoles RMI afin de faire fonctionner le programme
 * 
 * <p> La classe gére la connexion et deconnexion du serveur d'un client, ainsi que la connexion et la deconnexion aux différents
 *  Chat qui compose Serveur. <p>
 *  <p> Il est aussi possible par l'intermediaire de la classe de gérer les créations de Chat. <p>
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */

public class ControleurReseauServeurRMI implements IControleurReseauRMI{
	ControleurSe controleur;
	static final Message messageParDefaut = new Message ("bienvenue", "admin");
	
	// lien entre les utilisateurs et leurs stubs permettant le passage par référence. 
	HashMap<Utilisateur,IControleurReseauClientRMI> LienAvecLesClient; 
 
	/**
	 * Instancie un nouvel objet de la classe.
	 * @param controleur
	 */
	public ControleurReseauServeurRMI (ControleurSe controleur) 
	{
		this.controleur = controleur;
		LienAvecLesClient = new HashMap<Utilisateur,IControleurReseauClientRMI>();
	}
	
	
	@Override
	public void Accept(String nom, InetAddress adresseIP, IControleurReseauClientRMI Client) throws RemoteException {

		// ID de l'user
		int UserID = GestionnaireID.getUserId();
		
		// on crée l'utilisateur et on l'ajoute à notre liste d'utilisateur connecté. 
		Utilisateur nouveauConnecte = this.controleur.getModele().ajouterUtilisateur(nom, UserID);
		
		
		// on ajoute le nouvel utilisateur à notre lien utilisateur  et client 
		this.LienAvecLesClient.put(nouveauConnecte,  Client);
		
		HashMap<String,Object> event = new HashMap<String,Object>();		
		event.put("Event", "ConnexionEtablie");	
		
		// On lui donne �galement la liste des chats actuels
			// -- Cette liste sera repr�sent�e pas un HashMap associant l'ID du chat et son nom
		HashMap<Integer,String> ChatReference = new HashMap<Integer,String>();

		System.out.println("Recup�reation des chats");
		for(int i=0; i< controleur.getModele().getChats().size() ; i++) 
        {
			// On r�cup�re l'ID du chat
			int id = controleur.getModele().getChats().get(i).getIDChat();
			
			// On r�cup�re le nom du chat
			String nomDuChat =  controleur.getModele().getChats().get(i).getnomChat();
			System.out.println("(id)"+ id +"+(nom chat)"+ nomDuChat);
			
			// On l'ajoute a la map
			ChatReference.put(id,nomDuChat);
			System.out.println(id+" "+nomDuChat);
        }
		
		// On ajoute cette liste dans le message a envoyer
		event.put("Chats", ChatReference);	
		Client.traiterEvenement(event);

		// on affiche la connexion de l'utilisateur dans la fenétre graphque à l'aide du controleur.
		// afin d'avoir une vue d'ensemble sur les utilisateurs de notre réseau.
		controleur.log("nouvelle connexion  "+ nouveauConnecte.getNom() );
		
	}
	
	@Override
	public void Deconnect(IControleurReseauClientRMI Client)
			throws RemoteException {
		
		Utilisateur utilisateurADeconnecter = null; 
		// on récupére l'utilisateur de la HashMAP qui fait le lien entre les utilisateurs et leur stub.
		for(Entry<Utilisateur, IControleurReseauClientRMI> entry : LienAvecLesClient.entrySet()) {
			Utilisateur cle = entry.getKey();
			IControleurReseauClientRMI valeur = entry.getValue();
			
			if (valeur.equals(Client))
			{
				utilisateurADeconnecter = cle;
				LienAvecLesClient.remove(utilisateurADeconnecter);
			}
		}
		
		// on parcours la liste des utilisateurs du modelServeur pour le déconnecter. 
		for(int i = 0; i < this.controleur.getModele().getListeUtilisateurs().size(); i++) 
        {
			if (this.controleur.getModele().getListeUtilisateurs().get(i).equals(utilisateurADeconnecter));
			{
				// on déconnecte l'utilisateur et on affcihe dans la vue. 
				this.controleur.getModele().getListeUtilisateurs().remove(i);
				controleur.log("deconnexion du lutilisateur: " + utilisateurADeconnecter.getID());	
			}
        }
		
	}

		
	@Override
	public void AccederAuChat(int chatID, IControleurReseauClientRMI Client) throws RemoteException {
		
		Utilisateur utilisateurAConnecter = null; 
		Chat ChatAtraiter = null;
		
		// on récupére l'utilisateur de la HashMAP qui fait le lien entre les deux
		for(Entry<Utilisateur, IControleurReseauClientRMI> entry : LienAvecLesClient.entrySet()) {
			Utilisateur cle = entry.getKey();
			IControleurReseauClientRMI valeur = entry.getValue();
			
			if (valeur.equals(Client))
			{
				utilisateurAConnecter = cle;
			}
		}
		
		// NOus récupérons le Chat à traiter dans la liste des différents chat du serveur
		for(int i=0; i< this.controleur.getModele().getChats().size() ; i++) 
        {
			int id = this.controleur.getModele().getChats().get(i).getIDChat();
			if (id == chatID)
			{	
				ChatAtraiter = this.controleur.getModele().getChats().get(i);
				break;
			}
			
        }
		// nous vérifions que l'utilisateur n'appartient deja au chat
		Iterator<Utilisateur> iter = ChatAtraiter.getlisteUtilissateur().iterator();
		while(iter.hasNext())
		{
			Utilisateur courant = iter.next();	
			if (utilisateurAConnecter == courant)
			{
				System.out.println("j'ai reussit a compare");
				HashMap<String, Object> event = new HashMap<String, Object>();
				event.put("chatID", ChatAtraiter.getIDChat());
				event.put("Event", "UtilisateurDejaConnecte");
				LienAvecLesClient.get(utilisateurAConnecter).traiterEvenement(event);
				return;
				
			}
		}
		
		
		System.out.println("je passe ici");
		LinkedList<Message> messages = controleur.getModele().getChats().get(chatID).getMessages();
		
		// on ajoute l'utilisateur à la liste des différents chat
		ChatAtraiter.ajouterUtilisateur(utilisateurAConnecter);
		
		// on crer l'evenement puis on le fait traiter. 
		HashMap<String, Object> event = new HashMap<String, Object>();
		event.put("Messages", ChatAtraiter.getMessages());
		event.put("Event", "ConnexionChatAcceptee");
		event.put("chatID", chatID);
		event.put("nbUsers", ChatAtraiter.getlisteUtilissateur().size());
		event.put("messages", messages);
		Client.traiterEvenement(event);
		
		// affichage du client dans la fenetre de log
		controleur.log("Connexion au chat : "+ChatAtraiter.getnomChat() +"de l'Ulisateur"+ utilisateurAConnecter.getNom());
		
		// On notifie les utilisateurs du nouveau nombre de users
		// Cr�ation du message a envoyer aux utilisateurs
		// afin de mettre à jour leur interface graphique.
		HashMap<String,Object> event2 = new HashMap<String,Object>();		
		event2.put("Event", "MAJNBUser");	
		event2.put("nbUsers", ChatAtraiter.getlisteUtilissateur().size());
		event2.put("chatID", chatID);
		
		// Envoi du messages aux utilisateurs abonn�s au chat
		Iterator<Utilisateur> i = ChatAtraiter.getlisteUtilissateur().iterator();
		
		while(i.hasNext())
		{
			Utilisateur courant = i.next();	
			LienAvecLesClient.get(courant).traiterEvenement(event2);
		}


	}



	@Override
	public void CreationChat(String NomDuChat, IControleurReseauClientRMI Client) throws RemoteException {
	
		Utilisateur utilisateurAConnecter= null; 
		Chat ChatAtraiter = null;
		
		// on récupére l'utilisateur de la HashMAP qui fait le lien entre les deux
		for(Entry<Utilisateur, IControleurReseauClientRMI> entry : LienAvecLesClient.entrySet()) {
			Utilisateur cle = entry.getKey();
			IControleurReseauClientRMI valeur = entry.getValue();
			
			if (valeur.equals(Client))
			{
				utilisateurAConnecter = cle;
			}
		}
		
		// On l'ajoute a la liste de chat actuelle
		Chat c = controleur.getModele().ajouterChat(NomDuChat);
		
		controleur.log("Ajout du chat : "+NomDuChat);
		
		
		// On notifie tout les utilisateurs du nouveau chat		
		// On cr�e le message a envoyer
		HashMap<String, Object> msg = new HashMap<String, Object>();
		msg.put("Event", "NouveauChat");
		msg.put("chatID",  c.getIDChat());
		msg.put("chatNom", c.getnomChat());
		
		// On parcours la liste des utilisateur pour leur envoyer un message
		Iterator<Utilisateur> i = LienAvecLesClient.keySet().iterator();
		
		while(i.hasNext())
		{
			LienAvecLesClient.get(i.next()).traiterEvenement(msg);
		}
		
	}



	@Override
	public void DeconnecterAuChat(IControleurReseauClientRMI Client, int IDChat)
			throws RemoteException {

		Utilisateur utilisateurADeconnecter = null; 
		Chat ChatAtraiter = null;
		
		// on récupére l'utilisateur de la HashMAP qui fait le lien entre les deux
		for(Entry<Utilisateur, IControleurReseauClientRMI> entry : LienAvecLesClient.entrySet()) {
			Utilisateur cle = entry.getKey();
			IControleurReseauClientRMI valeur = entry.getValue();
			
			if (valeur.equals(Client))
			{
				utilisateurADeconnecter = cle;
				break;
			}
		}
		
		// Nous récupérons le Chat à traiter dans la liste des différents chat du serveur
		for(int i=0; i< this.controleur.getModele().getChats().size() ; i++) 
        {
			int id = this.controleur.getModele().getChats().get(i).getIDChat();
			System.out.println(id);
			if (id == IDChat)
			{	
				ChatAtraiter = this.controleur.getModele().getChats().get(i);
				break;
			}
			
        }
		// Nous supprimons l'utilisateur de la liste d'ecoute du chat. 
		// de cette manière il n'est plus abonné à la liste de message du chat
		ChatAtraiter.getlisteUtilissateur().remove(utilisateurADeconnecter);
		
		// On notifie les utilisateurs du nouveau nombre de users Cr�ation du message a envoyer aux utilisateurs
		// afin de mettre à jour leur interface graphique.
		HashMap<String,Object> event2 = new HashMap<String,Object>();		
		event2.put("Event", "MAJNBUser");	
		event2.put("nbUsers", ChatAtraiter.getlisteUtilissateur().size());
		event2.put("chatID", IDChat);
		
		// Envoi du messages aux utilisateurs abonn�s au chat
		Iterator<Utilisateur> i = ChatAtraiter.getlisteUtilissateur().iterator();
		
		while(i.hasNext())
		{
			Utilisateur courant = i.next();	
			LienAvecLesClient.get(courant).traiterEvenement(event2);
		}
		
	}



	@Override
	public void EnvoyerMessageChat(String MessageAEnvoyer,int ChatID,IControleurReseauClientRMI Client) throws RemoteException {
	
	
		Utilisateur utilisateur = null; 
		Chat ChatAtraiter = null;
		
		// on récupére l'utilisateur de la HashMAP qui fait le lien entre les deux
		for(Entry<Utilisateur, IControleurReseauClientRMI> entry : LienAvecLesClient.entrySet()) {
			Utilisateur cle = entry.getKey();
			IControleurReseauClientRMI valeur = entry.getValue();
			
			if (valeur.equals(Client))
			{
				utilisateur = cle;
				break;
			}
		}
		
		// NOus récupérons le Chat à traiter dans la liste des différents chat du serveur
		for(int i=0; i < this.controleur.getModele().getChats().size() ; i++) 
        {
			int id = this.controleur.getModele().getChats().get(i).getIDChat();
			System.out.println(id);
			if (id == ChatID)
			{	
				ChatAtraiter = this.controleur.getModele().getChats().get(i);
				break;
			}			
        }
		
		// Nous créons le message puis l'ajoutons a la liste des message
		Message nouveauMessage = new Message (MessageAEnvoyer,utilisateur.getNom());
		ChatAtraiter.ajouterMessage(nouveauMessage);
		
		// On parcours la liste des abonnées au Chat pour leur envoyer le Message
		HashMap<String,Object> event = new HashMap<String,Object>();		
		event.put("Event", "MessageRecu");	
		event.put("message", nouveauMessage);
		event.put("chatID", ChatAtraiter.getIDChat());
		
		// Envoi du messages aux utilisateurs abonn�s au chat
		Iterator<Utilisateur> i = ChatAtraiter.getlisteUtilissateur().iterator();
		
		// on boucle sur tous les clients pour leur envoyer le message. 
		while(i.hasNext())
		{
			Utilisateur courant = i.next();
			
			if (LienAvecLesClient.get(courant).equals(Client))
			{
				nouveauMessage.setSource(true);
				nouveauMessage.setNom("you");
			}
			
			System.out.println(nouveauMessage.getSource()); 
			LienAvecLesClient.get(courant).traiterEvenement(event);
			nouveauMessage.setSource(false);
			nouveauMessage.setNom(utilisateur.getNom());
		}
	}
}

