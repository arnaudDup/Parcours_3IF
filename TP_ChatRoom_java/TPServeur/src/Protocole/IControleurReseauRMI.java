package Protocole;

import java.net.InetAddress;
import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *  Interface permettant d'instaurer les codes de communication RMI, definie les méthodes RMI disponible pour le client.
 */
public interface IControleurReseauRMI extends Remote{
	
	/**
	 * Methode permettant de traiter la connexion a un serveur.  
	 * @param nom		Nom de l'utilisateur.
	 * @param adresseIP Adresse IP de l'utilisateur.
	 * @param Client	Permetant d'avoir une reference sur un Client(skeleton).
	 * @throws RemoteException
	 */
	public void Accept (String nom, InetAddress adresseIP, IControleurReseauClientRMI Client) throws RemoteException;	
	
	/**
	 *  Methode permettant de traiter la deconnexion a un serveur.
	 * @param Client	Permetant d'avoir une reference sur un Client(skeleton).
	 * @throws RemoteException
	 */
	public void Deconnect(IControleurReseauClientRMI Client) throws RemoteException;
	
	/**
	 * Methode permettant de gere la creation d'un nouveeau chat.  
	 * @param NomDuChat	Permettant de specifier le nom du nouveau chat. 
	 * @param Client	Permetant d'avoir une reference sur un Client(skeleton).
	 * @throws RemoteException
	 */
	public void CreationChat(String NomDuChat, IControleurReseauClientRMI Client)throws RemoteException;
	
	/**
	 * Methode permettant de gere la connexion d'un client a un chat.
	 * @param chatID	Identifiant unique d'un chat.
	 * @param Client 	Permetant d'avoir une reference sur un Client(skeleton).
	 * @throws RemoteException
	 */
	public void AccederAuChat(int chatID, IControleurReseauClientRMI Client) throws RemoteException;
	
	/**
	 * Methode permettant de gere la deconnexion d'un client a un chat.
	 * @param Client	Permetant d'avoir une reference sur un Client(skeleton).
	 * @param IDChat	Identifiant unique d'un chat.
	 * @throws RemoteException
	 */
	public void DeconnecterAuChat(IControleurReseauClientRMI Client, int IDChat) throws RemoteException;
	
	/**
	 * Methode permettant de gere l'envoi de message d'un client a un chat.
	 * @param MessageAEnvoyer 	Message a envoye 
	 * @param ChatID			Identifiant du chat
	 * @param Client			Permetant d'avoir une reference sur un Client(skeleton).
	 * @throws RemoteException
	 */
	public void EnvoyerMessageChat(String MessageAEnvoyer,int ChatID, IControleurReseauClientRMI Client) throws RemoteException;
	

}
