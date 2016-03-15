package Serveur.ManageServeur;

import java.io.Externalizable;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

import Common.ListeMessage;
import Common.Message;

/**
 * Classe permettant de représenter informatiquement un Chat disponible sur le serveur.
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * @see ModeleServeur
 */

public class Chat implements Externalizable
{
	/**
	 * 	Variable static permetant d'intancer l'identifiant non static du Chat.
	 */
	private static int IDcourant = -1;
	/**
	 * 	Identifiant unique du Chat.
	 */
    private int IDChat; 
    /**
	 * 	Nom du Chat, variable non unique.
	 */
    private String nomChat; 
    /**
	 * 	Liste des utilisateurs connecté au chat.
	 */
    private LinkedList<Utilisateur> listeUtilisateur; 
    /**
	 * 	Liste des messages échangés sur le Chat.
	 */
    private ListeMessage  listeChatMessage; 
   
    /**
	 * Instancie un nouvel objet de la classe.
	 * 
	 * @param unNom Nom du Chat. 
	 */
    public Chat (String unNom)
    {
          this.nomChat = unNom;   
          Chat.IDcourant ++ ;
          IDChat = IDcourant;
          this.listeUtilisateur = new LinkedList<Utilisateur>();
          this.listeChatMessage = new ListeMessage();
    }
    
    public Chat ()
    {

          this.listeUtilisateur = new LinkedList<Utilisateur>();
    }
    
    /**
   	 * @return Liste des Messages du chat.
   	 */
    public LinkedList<Message> getMessages()
    {
    	return this.listeChatMessage.getMessages();
    }
    
    
    /**
   	 * @return Liste des utilisateur connecté au chat. 
   	 */
    public List<Utilisateur> getlisteUtilissateur()
    {
        return this.listeUtilisateur;
    }
    
    /**
   	 * @return Identifiant unique du Chat. 
   	 */
    public int getIDChat()
    {
        return this.IDChat;
    }
    
    /**
   	 * @return Nom du chat. 
   	 */
    public String getnomChat()
    {
        return this.nomChat;
    }
    
   /**
     * Méthode permettant d'ajouter un message à liste des messages échangés sur le serveur. 
   	 * @param Contenu Spécifie le contenue du message
   	 * @param nomUtilisateur Référence à l'auteur du message.
   	 *
   	 */
    public void ajouterMessage (String Contenu, String nomUtilisateur)
    {
        this.listeChatMessage.MettreAJour(Contenu, nomUtilisateur);
    }
    
    /**
     * Méthode permettant d'ajouter un message à liste des messages échangés sur le serveur. 
   	 * @param message Message à ajouter dans la liste des messages du Chat.
   	 * 
   	 * @see Message
   	 */
    public void ajouterMessage (Message message)
    {
        this.listeChatMessage.add(message);
    }
    
    /**
     * Méthode permettant de connecter un utilisateur au chat. 
   	 * @param iDutilisateur Utilisateur à ajouter au chat traité.
   	 * 
   	 */ 
    public void ajouterUtilisateur (Utilisateur iDutilisateur)
    {
        this.listeUtilisateur.add(iDutilisateur);
    }

    /**
     * Méthode permettant de déconnecter un utilisateur au chat. 
   	 * @param user Utilisateur à déconnecter du chat traité.
   	 * 
   	 */
	public void enleverUtilisateur(Utilisateur user) {
		this.listeUtilisateur.remove(user);
	}
	

	@Override
	public void readExternal(ObjectInput in) throws IOException,
			ClassNotFoundException {
		
		listeChatMessage= (ListeMessage) in.readObject();		
		nomChat= (String) in.readObject();
		IDChat= in.readInt();
		IDcourant =in.readInt();
	}

	@Override
	public void writeExternal(ObjectOutput out) throws IOException {
		// TODO Auto-generated method stub
		out.writeObject(listeChatMessage);		
		out.writeObject(nomChat);
		out.writeInt(IDChat);
		out.writeInt(IDcourant);
	}
    
    
}
