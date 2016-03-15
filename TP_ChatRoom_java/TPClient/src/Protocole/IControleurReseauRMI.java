package Protocole;

import java.net.InetAddress;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IControleurReseauRMI extends Remote {
	
	// fonction permettant la connexion au serveur de l'objet 
	public void Accept (String nom, InetAddress adresseIP, IControleurReseauClientRMI Client) throws RemoteException;	
	// fonction permettant la deconnexion au serveur.
	public void Deconnect(IControleurReseauClientRMI Client) throws RemoteException;
	//méthode permettant d'envoyer un message à toute les personnes étant sur le serveur. 
	public void Envoyer(String MessageAEnvoyer,IControleurReseauClientRMI Client) throws RemoteException;
	// Méthode implementant la création de Chat
	public void CreationChat(String NomDuChat, IControleurReseauClientRMI Client)throws RemoteException;
	// Affichage des chat dispo
	public void AccederAuChat(int chatID, IControleurReseauClientRMI Client) throws RemoteException;
	// Méthode permettant de gérer la deconnexion au chat
	public void DeconnecterAuChat(IControleurReseauClientRMI Client, int IDChat) throws RemoteException;
	// Méthode permettant d'envoyer un message au chat. 
	public void EnvoyerMessageChat(String MessageAEnvoyer,int ChatID, IControleurReseauClientRMI Client) throws RemoteException;
	

}
