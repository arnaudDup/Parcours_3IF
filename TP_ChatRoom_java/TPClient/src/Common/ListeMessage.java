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


public class ListeMessage implements Serializable, ObjectInputValidation
{
    /**
	 * 
	 */
	private static final long serialVersionUID = 33L;
	
	LinkedList<Message> message;                   // liste de messages conservée localement sur la machine client.
    
    // Construteur de la liste de messages.
    public ListeMessage ()
    {
        this.message = new LinkedList<Message>();
    }
    
    // Méthode permettant la mise à jour de notre liste de message.
    public void MettreAJour(String messageAEnvoyer,String unAuteur)
    {
    	Message unMessage = new Message(messageAEnvoyer, unAuteur);
        this.message.add(unMessage);
    }
    
    // Méthode permettant d'impleémenter la fonctionnalité de l'hstorique.
    public void Historique (ListeMessage listemessage)
    {
    	// On parcourt la liste de message place en parametre
    	for(int i=0; i< listemessage.size(); i++) 
        {
    		// On ajoute chaque nouvel élément dans la liste de message conservé côtés serveur.
			this.message.add(listemessage.get(i));	
        }
    }
    
    public LinkedList<Message> getMessages()
    {
    	return message; 
    }
    public void add(Message message)
    {
    	this.message.add(message);
    }
    private void writeObject(java.io.ObjectOutputStream out) throws IOException
    {
    	out.defaultWriteObject();
    }
    private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException
    {
    	in.defaultReadObject();
    }
    
    public void SupprimerMessage()
    {
    	this.message.clear();
    }
    private int size()
    {
    	return this.message.size();
    }
    private Message get(int indice)
    {
    	return this.message.get(indice);
    }

	@Override
	public void validateObject() throws InvalidObjectException {
		System.out.println("Objet valide");
		
	}
}
