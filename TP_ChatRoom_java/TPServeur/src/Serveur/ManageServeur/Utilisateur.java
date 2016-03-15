package Serveur.ManageServeur;
import java.io.IOException;
import java.io.InvalidObjectException;
import java.io.ObjectInputValidation;
import java.io.Serializable;
import java.net.InetAddress;

/**
 * Classe permettant de représenter informatiquement un utilisateur connecté au serveur.
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * @see ModeleServeur
 */
public class Utilisateur implements Serializable, ObjectInputValidation
{
	/**
	 * 	Identifiant unique de l'utilisateur.
	 */
	private int ID;   
	/**
	 * 	Nom de l'utilisateur.
	 */
	private String nom; 
	/**
	 * 	Adresse IP du client.
	 */
	private InetAddress IPClient;			
  
	/**
	 * Instancie un nouvel objet de la classe.
	 * 
	 * @param unNom Nom de l'utilisateur.
	 * @param identifiant Identifiant de l'utilisateur.
	 * @param IpAdresse Adresse IP de l'utilisateur.
	 */
    public Utilisateur ( String unNom, int identifiant)
    {
    	this.nom = unNom;   
        this.ID = identifiant;
     
    }
    
    
    /**
	 * @return Retourne l'ID de l'utilisateur.  
	 */
    public int getID ()
    {
    	return this.ID;
    }
    
    /**
	 * @return Retourne le nom de l'utilisateur.  
	 */
    public String getNom()
    {
    	return nom;
    }
    

    private void writeObject(java.io.ObjectOutputStream out) throws IOException
    {
    	out.defaultWriteObject();
    }
    
    private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException
    {
    	in.defaultReadObject();
    }
    
	@Override
	public void validateObject() throws InvalidObjectException {
		System.out.println("Objet valide");
	}

	/**
	 * @return Retourne l'adresse IP de l'utilisateur.  
	 */
	public InetAddress getIPClient() {
		return IPClient;
	}


	public int getIDClient() {
		// TODO Auto-generated method stub
		return ID;
	}
}
