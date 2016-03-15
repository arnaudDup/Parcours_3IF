package Protocole;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.HashMap;

public interface IControleurReseauClientRMI extends Remote {

	public void traiterEvenement (HashMap <String, Object> event) throws RemoteException;

}
