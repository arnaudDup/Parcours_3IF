package Serveur.ManageServeur;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.InetAddress;
import java.net.UnknownHostException; 

import Serveur.ControleurServeur.ControleurSe;

/**
 * Classe  permettant de gerer les différentes listes nécessaire au bon fonctionnement du 
 * programme:
 * <p>
 * - La liste des utilisateurs connecter au serveur. 
 * - La liste des chats disponible sur le serveur.
 * </p>
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */

public class ModeleServeur
{
	/**
	 * Liste des différents chat disponible sur le serveur.
	 */
    private LinkedHashMap<Integer, Chat> listeChat; 
    /**
	 * Liste des différents utilisateurs connectés sur le serveur.
	 */
    private HashMap<Integer, Utilisateur> listeUtilisateurs; 
    /**
	 * Adresse IP de notre serveur.
	 */
    private String adresseIp;  
    /**
	 * Permet de connaitre le nombre d'utilisateur connectés sur le serveur.
	 */
    private static int nombreDeClient;
    /**
	 * Permet de faire le lien entre l'interface graphique et le programme.
	 */
    private ControleurSe controleur;
    
    
    /**
	 * Instancie un nouvel objet de la classe.
	 * 
	 *@param controleur Permet de faire le lien entre l'interface graphique et les différentes parties du programme. 
	 */
    public ModeleServeur(ControleurSe controleur) {
    	this.controleur = controleur;
    	

    	// On d�s�ralise la liste de chat
		if(!LoadChat(controleur.getNomFichier()))
		{
			this.listeChat = new LinkedHashMap<Integer, Chat>();
		}
        this.listeUtilisateurs = new HashMap<Integer, Utilisateur>();
        recupererAdresseIp();
        
	}
    
    
	/**
	 * Methode permettant d'obtenir et initialiser l'adresse IP du serveur.
	 *
	 */ 
    
	private void recupererAdresseIp()
    {
    	 try 
         { 
              this.adresseIp = InetAddress.getLocalHost().getHostAddress();
              System.out.println("L'adresse associ�e au serveur est:"+this.adresseIp);
         } 
         catch(UnknownHostException e) 
         { 
              System.err.println("Impossible de se connecter: " + e.toString());
         }
    }
	
    
	/**
	 * Methode <code> ajouterChat </code> permettant d'ajouter un <code> Chat </code> à notre <code> ModeleServeur </code>.
	 * 
	 * @param nomChat Permettant de créer un nouveau Chat et d'ajouter celui à la liste des Chats disponibles.
	 * @return Objet de la classe Chat ajouté a liste des chat disponibles.
	 *@see Class Chat
	 */  
	
    public Chat ajouterChat(String nomChat)
    {
    	Chat nouveauChat = new Chat (nomChat);
    	this.listeChat.put(nouveauChat.getIDChat(),nouveauChat);
    	return nouveauChat;
    }
    
    /**
	 *  Méthode permettant d'ajouter un <code> Utilisateur </code> connecté à notre <code> ModeleServeur </code>.
	 *  
	 *  @param nom Spécifie le nom de l'utilisateur.
	 *  @param adresseIpClient Identifiant unique permettant de connecté l'utilisateur.
	 *  
	 *  @return Objet de la classe <code>Utilisateur</code>. ajouté a la liste d'utilisateur connectés.
	 *  @see Utilisateur 
	 */ 
    
    public Utilisateur ajouterUtilisateur(String nom, int userID)
    {
		Utilisateur nouveauUtilisateur = new Utilisateur ( nom, userID); // On ajoute un user
		listeUtilisateurs.put(userID,nouveauUtilisateur);
		return nouveauUtilisateur;
    }
    
    /**
	 * Méthode permettant de supprimer un <code> Utilisateur </code> connecté de notre <code> ModeleServeur </code>.
	 * 
	 * @param adresseIpClient identifiant unique permettant de déconnecter l'utilisateur du <code> ModeleServeur </code>. 
	 */ 
    
    public void deconnecterUtilisateurServeur(int adresseIpClient)
    {
    	// On r�cup�re l'utilisateur
    	Utilisateur user = listeUtilisateurs.get(adresseIpClient);
    	
    	// On l'enl�ve des chats auquel il est connect�
    	Iterator<Integer> i = listeChat.keySet().iterator();
    	
    	while(i.hasNext())
    	{
    		Chat cur = listeChat.get(i.next());
    		
    		if(cur.getlisteUtilissateur().contains(user))
    			cur.enleverUtilisateur(user);
    	}
    }
    
    /**
	 * @return Retourne la liste des différents chats ouverts  
	 */
    public LinkedHashMap<Integer, Chat> getChats()
    {
    	return listeChat;
    }
    
    /**
	 * @return Retourne la liste des différents utilisateurs connectés au serveur.  
	 */
    public HashMap<Integer, Utilisateur> getListeUtilisateurs()
    {
    	return listeUtilisateurs;
    }
    
    /**
	 * @return Retourne l'adresse IP du serveur 
	 */
    public String getIpAdress ()
    {
    	return this.adresseIp;
    }
    
    
    /**
     * Permet d'externaliser les chats, permettant de mettre en place un historique permanent. 
     * @param nomFicher
     * @throws IOException
     */
    public void SerialiserChats(String nomFicher) throws IOException
    {
    	FileOutputStream fileStream = new FileOutputStream(nomFicher,false);
    	
    	Iterator<Integer> c = this.listeChat.keySet().iterator();
    	ObjectOutputStream oos = new ObjectOutputStream(fileStream);
    	
    	oos.writeObject(listeChat);
    }
    
    
    /**
     * Permet de r�cupere � partir d'un fichier un historique persistant. 
     * 
     * @param nomFicher
     * @return Vrai si le fichier existe
     * @throws IOException
     */
    public boolean LoadChat(String nomFicher) 
    {
    	// de-serialize chats
    	try {
    	    FileInputStream fi = new FileInputStream(nomFicher);
    	    ObjectInputStream si = new ObjectInputStream(fi);  	    
    	    listeChat = (LinkedHashMap<Integer, Chat>) si.readObject();
    	}
    	catch (Exception e) {
    	System.out.println("Exception:"+e.getMessage());
    	  return false;
    	}
		return true;
    }

}
