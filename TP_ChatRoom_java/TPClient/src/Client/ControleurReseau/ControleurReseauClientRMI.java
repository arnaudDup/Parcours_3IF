package Client.ControleurReseau;

import java.net.InetAddress;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.LinkedList;

import Common.Message;
import Protocole.IControleurReseauClientRMI;
import Protocole.IControleurReseauRMI;


public class ControleurReseauClientRMI extends UnicastRemoteObject implements IControleurReseauClient, IControleurReseauClientRMI {
	private Controleur controleur;
	private IControleurReseauRMI serveur;
	
	public ControleurReseauClientRMI( Controleur controleur) throws java.rmi.RemoteException
	{
		this.controleur = controleur;
	}

	public void connecterServeur(final String nom, final InetAddress adresseIP) {
	// La connexion implique la recherche dans le registre afin de récuperer le stub cotés client
	String host = adresseIP.toString();
	host = host.substring(1, host.length());
    Registry registry;
	try {
		//registry = LocateRegistry.getRegistry(adresseIP.toString());
		registry = LocateRegistry.getRegistry(host);
		IControleurReseauRMI stub = (IControleurReseauRMI) registry.lookup("Serveur");
		serveur = stub;	
	} catch (Exception e) {e.printStackTrace();}
	
	
	final IControleurReseauClientRMI tampon = this;
	// passage par référence de l'objet.
	new Thread(new Runnable(){

		@Override
		public void run() {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {e.printStackTrace();}
			
			try {
		    	serveur.Accept(nom, adresseIP, tampon);
		  
			} catch (RemoteException e) {e.printStackTrace();}
		}
		
	}).start();
    
	}

	public void connecterChat(final int chatid) {
		
	final IControleurReseauClientRMI tampon = this;
	// passage par référence de l'objet.
	new Thread(new Runnable(){

		@Override
		public void run() {
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {e.printStackTrace();}
			
			try {
		    	
		    	serveur.AccederAuChat(chatid,tampon);
		  
			} catch (RemoteException e) {e.printStackTrace();}
		}
		
	}).start();
	
}
	
	@Override
	public void envoyerMessageChat(final String contenu, final int IDChat) {
		final IControleurReseauClientRMI tampon = this;
		// passage par référence de l'objet.
		new Thread(new Runnable(){

			@Override
			public void run() {
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {e.printStackTrace();}
				
				try {
			    	serveur.EnvoyerMessageChat(contenu, IDChat, tampon);
			  
				} catch (RemoteException e) {e.printStackTrace();}
			}
			
		}).start();
		
	}

	// Méthode remote que le serveur appel pour mettre a jour les différentes vue cotés client. 
	@Override
	public void traiterEvenement(HashMap<String, Object> event)
			throws RemoteException {
		this.controleur.considererEvent(event);
		
	}

	@Override
	public void deconnecterChat(final int IDChat) {
		final IControleurReseauClientRMI tampon = this;
		// passage par référence de l'objet.
		new Thread(new Runnable(){

			@Override
			public void run() {
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {e.printStackTrace();}
				
				try {
			    	serveur.DeconnecterAuChat(tampon, IDChat);
			  
				} catch (RemoteException e) {e.printStackTrace();}
			}
			
		}).start();
		
	}

	@Override
	public void ajouterChat(final String nomDuChat) {
		final IControleurReseauClientRMI tampon = this;
		// passage par référence de l'objet.
		new Thread(new Runnable(){

			@Override
			public void run() {
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {e.printStackTrace();}
				
				try {
			    	serveur.CreationChat(nomDuChat, tampon);
			  
				} catch (RemoteException e) {e.printStackTrace();}
			}
			
		}).start();
		
	}

	@Override
	public void envoyerMessagePrive(int userID, String text) {
		// TODO Auto-generated method stub
		
	}

}
