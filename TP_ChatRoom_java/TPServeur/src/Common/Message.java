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
 * Classe permettant de representer informatiquement un message qui s'échange entre les differents clients. 
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */
public class Message implements Serializable, ObjectInputValidation {
    
		/**
		 * Permettant de serialiser l'objet 
		 */
		private static final long serialVersionUID = 1L;
		
		/**
		 * Represente le contenu d'un message. 
		 */
		private String contenu;
		
		/**
		 * Represente l'auteur du message.
		 */
		private String  auteur; 
		
		/**
		 * Date de la creation du message. 
		 */
		private Calendar date;
		
		/**
		 * Identifiant unique d'un message 
		 */
		private int IDMessage;                             			
		
		/**
		 * Permettant de specifier si le message appartient a l'auteur.
		 */
		private boolean source = false;									
		
		/**
		 * Permettant de specifier l'identifiant de l'utilisateur
		 */
	    private static int IDcourant;
	    
	    /**
	     * Instancie un nouvel objet de classe 
	     * @param unContenu
	     * @param unAuteur
	     */
	    public Message (String unContenu,String unAuteur )
	    {
	        Message.IDcourant++;
	        IDMessage = IDcourant;
	        this.contenu = unContenu;
	        this.auteur = unAuteur;
	        this.date = Calendar.getInstance();
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
	     * 
	     * @return Retourne le contenu d'un message
	     */
	    public String getContenu() 
	    {
	    	return contenu;
	    }
	    
	    /**
	     * 
	     * @return Retourne l'auteur d'un message 
	     */
	    public String getAuteur()
	    {
	    	return auteur;
	    }
	    
	    /**
	     * Permet de changer le nom de l'auteur
	     * @param unAuteur change le nom de l'auteur 
	     */
	    public void  setNom (String unAuteur)
	    {
	    	this.auteur = unAuteur;
	    }
	    
	    /**
	     * 
	     * @return Retourne une information sur l'auteur du message 
	     */
	    public boolean getSource() 
	    {
	    	return source;
	    }
	    
	    /**
	     * Permet de modifier la source du message. 
	     * @param aSource
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
