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
import java.util.Calendar;

/**
 *
 * @author adupeyrat
 */
public class Message implements Serializable, ObjectInputValidation {
    
   
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private String contenu;                          			// Contenu du message d�livr�
	private String  auteur;                           			// Identifie de maniere unique l'auteru du message. 
	private Calendar date;                            			// Information sur la date de l'envoi du message. 
	private int IDMessage;                             			// Identifie de mani�re unique le message.
	
	// Arnaud: couleur
	private boolean source = false;										// true si la source du message est l'utilisateur
    private static int IDcourant;
    
    public Message (String unContenu,String unAuteur )
    {
        Message.IDcourant++;
        IDMessage = IDcourant;
        this.contenu = unContenu;
        this.auteur = unAuteur;
        this.date = Calendar.getInstance();
    }
    
    private void writeObject(java.io.ObjectOutputStream out) throws IOException
    {
    	out.defaultWriteObject();
    }
    private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException
    {
    	in.defaultReadObject();
    }
    
    public String getContenu() { return contenu;}
    public String getAuteur() { return auteur;}
    
    /*
     * La source du message
     */
    public boolean getSource() { return source;}
    
    /*
     * set la source du message
     */
    public void setSource(boolean aSource)
    {
    	source = aSource;
    }

	@Override
	public void validateObject() throws InvalidObjectException {
		System.out.println("Objet valide");
		
	}
    
}
