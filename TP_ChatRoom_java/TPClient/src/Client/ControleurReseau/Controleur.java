package Client.ControleurReseau;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.RemoteException;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;

import Client.Vue.*;
import Client.Automate.*;
import Client.ControleurReseau.ControleurReseauClientSockets;
import Client.ControleurReseau.IControleurReseauClient;
import Client.ControleurReseau.ControleurReseauClientRMI;
import Common.Message;

public class Controleur {
	private Vue vue;
	private IControleurReseauClient controleurReseau;
	private Automate automate;
	private String nom;
	private InetAddress IPServeur;
	private HashMap<Integer, VueMessagePrive> listeVueMessagePrive;
	
	public Controleur(boolean RMI)
	{
		if(RMI)
			try {
				controleurReseau = new ControleurReseauClientRMI(this) ;
			} catch (RemoteException e) {e.printStackTrace();}
		else
			controleurReseau = new ControleurReseauClientSockets(this);
		
		listeVueMessagePrive = new HashMap<Integer, VueMessagePrive>();
		initAutomate();
		vue = new Vue(this);
	}
	
	public void addVueMessagePrive(VueMessagePrive vue, int userID)
	{
		listeVueMessagePrive.put(userID, vue);
	}
	
	public void considererEvent(HashMap<String, Object> event)
	{
		if(event == null)
		{
			System.out.println("Evenement null");
			return;
		}
		
		String typeEvent = (String)event.get("Event");
		System.out.println("Consideration de :"+typeEvent);
		
		// Lorsque l'on recoi un message privé, on ne le traite pas dans l'automate
		if(typeEvent.equals("ReceptionMessagePrivee"))
		{
			int userID = (Integer)event.get("userID");

			Message msg = (Message)event.get("message");
			
			VueMessagePrive vue = null;
			if(listeVueMessagePrive.containsKey(userID))
			{
				 vue = listeVueMessagePrive.get(userID);				
			}
			
			else
			{				
				vue = VueMessagePrive.getInstance(userID, msg.getAuteur(),  this);
			}
				
			vue.setMessage(msg);
			vue.setVisible(true);
			
		}
		else			
			automate.consider(event);

	}
	
	public String getNom(){
		return nom;
	}
	
	public void initAutomate()
	{
		automate = new Automate();
		
		// On dï¿½fini des etats
		Etat e1 = automate.ajouterEtat("PageAccueil");
		Etat e2 = automate.ajouterEtat("AttenteReponseServeur"); 		
		Etat e3 = automate.ajouterEtat("SelectionnerChat");	
		
		//T1
		HashMap<String,Object> event1 = new HashMap<String,Object> ();
		event1.put("Event", "ClicBoutonConnecter");
		Transition t1 = new Transition(e2,event1);
		t1.setAction(new IAction () {
			public void faireAction() {
				nom = ((VueAccueil)vue.getPage("Accueil")).getNom(); // on rÃ©cupÃ©re le nom dans la page d'accueil
				
				 // on rï¿½cupï¿½re l'IP dans la page d'accueil
				
				try {
					IPServeur = InetAddress.getByName( ( (VueAccueil)vue.getPage("Accueil")).getIP() );

				} catch (UnknownHostException e) {
					System.out.println("Erreur : Hï¿½te inconnue ! ("+((VueAccueil)vue.getPage("Accueil")).getIP()+")");
					return;
				}
				
				vue.afficherPage("Attente");
				controleurReseau.connecterServeur(nom, IPServeur);			
			}				
		});
		
		//T2
		HashMap<String,Object> event2 = new HashMap<String,Object> ();
		event2.put("Event", "ConnexionEtablie");
		
		final Transition t2 = new Transition(e3,event2);
		
		t2.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t2.getEventRecu();
				vue.afficherPage("pagePrincipale");
				( (VuePagePrincipale)vue.getPage("pagePrincipale") ).setListChats( (HashMap<Integer,String>) eventRecu.get("Chats") );

			}				
		});
		
		
		//T3 si on recoit un clic connecter on demande une connection et on va dans l'etat d'attente
		HashMap<String,Object> event3 = new HashMap<String,Object> ();
		event3.put("Event", "ClicConnecterChat");
		
		final Transition t3 = new Transition(e2,event3);
		
		t3.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t3.getEventRecu();
				vue.afficher1Page("Attente");
				controleurReseau.connecterChat((int)eventRecu.get("chatID"));
			}				
		});
		
		//T4 quand on recoi la confirmation de connection au chat
		HashMap<String,Object> event4 = new HashMap<String,Object> ();
		event4.put("Event", "ConnexionChatAcceptee");
		
		final Transition t4 = new Transition(e3,event4);
		
		t4.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t4.getEventRecu();

				// On rï¿½cupï¿½re les messages
				LinkedList<Message> messages = (LinkedList<Message>) eventRecu.get("messages");
				
				// On récupère les users				
				HashMap<Integer,String> users = (HashMap<Integer,String>) eventRecu.get("users");
				/*HashMap<Integer,String> users = new HashMap<Integer, String>();
				users.put(0, "Fuck");*/
				
				// On rï¿½cupï¿½re l'ID du chat
				int ID = (int) eventRecu.get("chatID");
				
				VueChat chat = ((VueChat)vue.getChat(ID));
				
				// On affiche la liste de message
				chat.setListeMessages(messages);
				
				//On met a jour la liste liste de users
				if(users!=null)
				chat.majListUsers(users);
				
				// on met a jour le nombre d'utilisateur
				chat.setNbUtilisateurConnecte((Integer)eventRecu.get("nbUsers"));
				vue.CacherPage("Attente");
				vue.afficherChat(ID);

			}				
		});
		
		// T5
		HashMap<String,Object> event5 = new HashMap<String,Object> ();
		event5.put("Event", "ClicEnvoyerChat");
		final Transition t5 = new Transition(e3,event5);
		
		t5.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t5.getEventRecu();
				// appel de la mÃ©thode
				System.out.println((String) eventRecu.get("message"));
				System.out.println((int) eventRecu.get("chatID"));
				controleurReseau.envoyerMessageChat((String) eventRecu.get("message"), (int) eventRecu.get("chatID") );
			}				
		});
		
		// T6
		HashMap<String,Object> event6 = new HashMap<String,Object> ();
		event6.put("Event", "MessageRecu");
		final Transition t6 = new Transition(e3,event6);
		
		t6.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t6.getEventRecu();
				// mise a jour de la vue
				
				// On rï¿½cupï¿½re l'ID du chat
				int ID = (int) eventRecu.get("chatID");
								
				((VueChat)vue.getPage("chat"+ID)).AddMessage((Message)eventRecu.get("message")) ;
				

			}				
		});

		// T7
		HashMap<String,Object> event7 = new HashMap<String,Object> ();
		event7.put("Event", "ClicDeconnexionChat");
		final Transition t7 = new Transition(e3,event7);
		
		t7.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				
				eventRecu = t7.getEventRecu();
				
				// on se deconnecte du chat
				controleurReseau.deconnecterChat((Integer) eventRecu.get("chatID"));
				
				// mise a jour de la vue
				VueChat chat = vue.getChat((Integer) eventRecu.get("chatID"));
				chat.setVisible(false);
				chat.remiseAZeroJlist();
			}				
		});
		
		//T8 CLIC AJOUTER CHAT
		HashMap<String,Object> event8 = new HashMap<String,Object> ();
		event8.put("Event", "ClicAjouterChat");
		
		final Transition t8 = new Transition(e3,event8);
		
		t8.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t8.getEventRecu();
				
				// Lorsque l'on recoi un clic, on appelle la mï¿½thode d'ajout de chat du controleur serveur
				controleurReseau.ajouterChat((String) eventRecu.get("nomChat"));

			}				
		});
		
		//T9 NOUVEAU CHAT
		HashMap<String,Object> event9 = new HashMap<String,Object> ();
		event9.put("Event", "NouveauChat");
		
		final Transition t9 = new Transition(e3,event9);
		
		t9.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t9.getEventRecu();
				
				// On ajoute le nouveau chat a notre liste de chat
				int chatid = (Integer) eventRecu.get("chatID");
				String nom = (String) eventRecu.get("chatNom");
				
				( (VuePagePrincipale)vue.getPage("pagePrincipale") ).addChat(chatid, nom);
			}				
		});
		
		//T10 MAJ nombre utilisateur
		HashMap<String,Object> event10 = new HashMap<String,Object> ();
		event10.put("Event", "DecoCoUser");
		
		final Transition t10 = new Transition(e3,event10);
		
		t10.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t10.getEventRecu();
				
				// On ajoute le nouveau chat a notre liste de chat
				int chatid = (Integer) eventRecu.get("chatID");

				// On rï¿½cupï¿½re le chat
				VueChat chat = ((VueChat)vue.getChat(chatid));

				// on met a jour le nombre d'utilisateur
				chat.setNbUtilisateurConnecte((Integer)eventRecu.get("nbUsers"));
				
				// on met a jour la liste de user connectés
				boolean connexion = (Boolean) eventRecu.get("connexion");
				int userId = (Integer) eventRecu.get("userID");
				
				// si c'est une connexion on ajoute un user a la liste
				if(connexion)
				{
					String nom = (String) eventRecu.get("userNom");
					chat.addUserVueUser(userId, nom);
				}
				// si c'est une deconnexion on enleve le user de la liste
				else
				{
					chat.removeUser(userId);
				}
					
			}				
		});
		
		//T10 MAJ nombre utilisateur
		HashMap<String,Object> event11 = new HashMap<String,Object> ();
		event11.put("Event", "UtilisateurDejaConnecte");
		
		final Transition t11 = new Transition(e3,event11);
		
		t11.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t11.getEventRecu();
				// On ajoute le nouveau chat a notre liste de chat
				int chatid = (Integer) eventRecu.get("chatID");
				// On rï¿½cupï¿½re le chat
				VueChat chat = ((VueChat)vue.getChat(chatid));
				// on cache la page attente
				vue.CacherPage("Attente");
			}				
		});
		
		//T12 nombre utilisateur
		HashMap<String,Object> event12 = new HashMap<String,Object> ();
		event12.put("Event", "UtilisateurConnecte");
		
		final Transition t12 = new Transition(e3,event12);
		
		t12.setAction(new IAction () {
			private HashMap<String,Object> eventRecu;
			
			public void faireAction() {
				eventRecu = t12.getEventRecu();
				
			}				
		});
		
		Transition t5bis = new Transition(e2,event5);
		t5bis.setAction(t5.getAction());
		
		Transition t6bis = new Transition(e2,event6);
		t6bis.setAction(t6.getAction());
		
		Transition t7bis = new Transition(e2,event7);
		t7bis.setAction(t7.getAction());
		
		Transition t8bis = new Transition(e2,event8);
		t8bis.setAction(t8.getAction());
		
		Transition t9bis = new Transition(e2,event9);
		t9bis.setAction(t9.getAction());
		
		Transition t10bis = new Transition(e2,event10);
		t10bis.setAction(t10.getAction());
		
		// On ajoute les transitions aux ï¿½tats
		
		// Etat e1
		e1.ajouterTransition(t1);

		// Etat e2
		e2.ajouterTransition(t2);		
		e2.ajouterTransition(t4);
		e2.ajouterTransition(t5bis);
		e2.ajouterTransition(t6bis);
		e2.ajouterTransition(t7bis);
		e2.ajouterTransition(t8bis);
		e2.ajouterTransition(t9bis);
		e2.ajouterTransition(t10bis);
		e2.ajouterTransition(t11);
		
		// Etat e3
		e3.ajouterTransition(t3);		
		e3.ajouterTransition(t5);
		e3.ajouterTransition(t6);
		e3.ajouterTransition(t7);
		e3.ajouterTransition(t8);
		e3.ajouterTransition(t9);
		e3.ajouterTransition(t10);
		
		automate.setEtatInitial(e1);
		
		automate.demarrer();

	}
	
	public Vue getVue(){ return vue; }
	
	/**
	 * @param ip the ip to set
	 */
	public void setIPServeur(InetAddress ip) {
		this.IPServeur = ip;
	}

	public InetAddress getIpServeur() {
		// TODO Auto-generated method stub
		return IPServeur;
	}

	public IControleurReseauClient getControleurReseau() {
		return controleurReseau;
	}
}
