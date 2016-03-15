package Serveur.ControleurServeur;

import java.net.InetAddress;
import java.rmi.AlreadyBoundException;
import java.rmi.RMISecurityManager;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

import Serveur.ControleurServeur.InterfaceGraphiqueServeur;
import Protocole.IControleurReseauRMI;
import Serveur.ControleurServeur.ControleurReseauServeurRMI;
import Serveur.ControleurServeur.ControleurReseauServeurSockets;
import Serveur.ManageServeur.ModeleServeur;
import Serveur.ManageServeur.Utilisateur;


/**
 * La classe Permet de faire le lien entre les deux protocoles de communication que possede notre application RMI et les protocoles sockets
 * 
 * <p> La classe gere la creation de <code> ControleurSE </code>
 *  qui intancie le protocole utilise pour les communications.  <p>
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */
public class ControleurSe {
	
	/**
	 * Interface graphique cote serveur
	 */
	private InterfaceGraphiqueServeur vue;
	
	/**
	 * Permerttant de connaitre l'etat courant de notre serveur. 
	 */
	private ModeleServeur modele;
	
	/**
	 * Permettant de specifier le nom du fichier dans lequel les informations externalisees sont enregistrees
	 */
	private String nomFichierSauvegarde;
	
	/**
	 * Instancie un nouvel objet de classe.
	 * @param RMI
	 * @param nomFichier
	 */
	public ControleurSe(boolean RMI, String nomFichier) {
		
		nomFichierSauvegarde = nomFichier;
		modele = new ModeleServeur(this);
				
		if(RMI)
		{
			// CrÃ©ation de l'interface permettant de communiquer.
			IControleurReseauRMI ProtocoleReseau = (IControleurReseauRMI) new ControleurReseauServeurRMI (this);
			
			// puis on place l'objet dans le registre
			try {
				ouvertureDuRegistre(ProtocoleReseau);
			} catch (Exception e) {e.printStackTrace();} 
	
		}
		else
		{
			// 
			// Partie sockets
			ControleurReseauServeurSockets ControleurServeur = new ControleurReseauServeurSockets(this);
		}

			
		// affichage de l'interfage graphique 
		vue = new InterfaceGraphiqueServeur(this);
		vue.repaint();
		vue.pack();
	}
	
	
	/**
	 * Methodes permettant l'ouverture du registre RMI, nécessaire aux échanges client/Serveur. 
	 *  
	 * @param protocoleReseau
	 * @throws RemoteException
	 * @throws AlreadyBoundException
	 */
	public void ouvertureDuRegistre(IControleurReseauRMI protocoleReseau) throws RemoteException, AlreadyBoundException
	{
        IControleurReseauRMI stub = (IControleurReseauRMI) UnicastRemoteObject.exportObject(protocoleReseau, 0);
		LocateRegistry.createRegistry(1099);
		Registry registry = LocateRegistry.getRegistry();
		registry.bind("Serveur",stub);
	}
	
	
	/**
	 * 
	 * @return Retourne la vue, l'interface graphique du serveur.  
	 */
	public InterfaceGraphiqueServeur getVue ()
	{
		return vue;
	}
	
	
	/**
	 * 
	 * @return Retourne le modele du serveur.
	 */
	public ModeleServeur getModele()
	{
		return modele;
	}

	
	/**
	 * Methode permettant d'ecrire dans l'interface graphique du serveur.
	 * @param texte
	 */
	public void log(String texte)
	{
		vue.AddMessageLog(texte);
	}

	
	/**
	 * Methode permettant de retourner l'utilisateur en fonction de son ID
	 * 
	 * @param sender Recherche de l'utilisateur dans le modele
	 * @return Retourne l'utilisateur possedant l'ID recherche 
	 */
	public Utilisateur getUserByID(int sender) {
		// TODO Auto-generated method stub
		return modele.getListeUtilisateurs().get(sender);
	}

	/**
	 * 
	 * @return Retourne le nom du ficher de l'historique. 
	 */
	public String getNomFichier() {
		
		return nomFichierSauvegarde ;
	}
}
