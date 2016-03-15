package Client.ControleurReseau;

import java.net.InetAddress;

public interface IControleurReseauClient {

	public void connecterServeur(String nom, InetAddress adresseIP);
	public void connecterChat(int chatid);
	public void envoyerMessageChat(String contenu, int ID);
	public void deconnecterChat(int iDchat);
	public void ajouterChat(String string);
	public void envoyerMessagePrive(int userID, String text);
}
