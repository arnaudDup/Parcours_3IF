package Protocole;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.HashMap;
/**
 * 
Interface permettant d'instaurer les codes de communication RMI, definie les méthodes RMI disponible pour le serveur.
 * @author Antoine BRETON et Arnaud DUPEYRAT
 *
 */
public interface IControleurReseauClientRMI extends Remote {

	public void traiterEvenement (HashMap <String, Object> event) throws RemoteException;

}
