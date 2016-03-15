package Common;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.io.IOException;
import java.io.InvalidObjectException;
import java.io.ObjectInputValidation;
import java.io.Serializable;
import java.util.LinkedList;
import java.util.List;

/**
 * Classe permettant de representer informatiquement une liste de messsage.  
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */
public class ListeMessage implements Serializable, ObjectInputValidation
{
    /**
	 * Identifiant permettant la serialisation. 
	 */
	private static final long serialVersionUID = 33L;
	
	/**
	 * Liste des differents messages du serveur. 
	 */
	private LinkedList<Message> message;                   
    
    /**
     * Instancie un nouvel objet de classe. 
     */
    public ListeMessage ()
    {
        this.message = new LinkedList<Message>();
    }
    
    /**
     * Permet d'ajouter un message, � notre liste de message  
     * @param messageAEnvoyer
     * @param unAuteur
     */
    public void MettreAJour(String messageAEnvoyer,String unAuteur)
    {
    	Message unMessage = new Message(messageAEnvoyer, unAuteur);
        this.message.add(unMessage);
    }
    
    /**
     * 
     * Permet de charger un historique a notre liste de message. 
     * @param listemessage
     */
    public void Historique (ListeMessage listemessage)
    {
    	// On parcourt la liste de message place en parametre
    	for(int i=0; i< listemessage.size(); i++) 
        {
    		// On ajoute chaque nouvel élément dans la liste de message conservé côtés serveur.
			this.message.add(listemessage.get(i));	
        }
    }
    
    /**
     * 
     * @return Retourn la liste de message 
     */
    public LinkedList<Message> getMessages()
    {
    	return message; 
    }
    
    /**
     * Ajoute un message a la liste de messsage 
     * @param message message ajoute 
     */
    public void add(Message message)
    {
    	this.message.add(message);
    }
    
    /**
     * Permet la serialisation de l'objet 
     * @param out
     * @throws IOException
     */
    private void writeObject(java.io.ObjectOutputStream out) throws IOException
    {
    	out.defaultWriteObject();
    }
    
    /**
     * Permet la serialisation de l'objet
     * @param in
     * @throws IOException
     * @throws ClassNotFoundException
     */
    private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException
    {
    	in.defaultReadObject();
    }
    
    /**
     * Permet de vider, supprimer l'ensemble des message contenu dans notre liste.
     */
    public void SupprimerMessage()
    {
    	this.message.clear();
    }
    
    /**
     * 
     * @return Retourne la taille de notre liste de messsage 
     */
    private int size()
    {
    	return this.message.size();
    }
    
    /**
     * Methode permettant de renvoyer un message de la liste.  
     * 
     * @param indice indice du message recherche 
     * @return permet de renvoyer le message, reference par l'indice de la ligne.
     */
    private Message get(int indice)
    {
    	return this.message.get(indice);
    }

    /**
     * Methode permettant la serialisation. 
     */
	@Override
	public void validateObject() throws InvalidObjectException {
		System.out.println("Objet valide");
		
	}
}
