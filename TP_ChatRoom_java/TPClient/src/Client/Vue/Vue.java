package Client.Vue;
import java.util.HashMap;
import java.util.Iterator;

import javax.swing.JFrame;

import Client.ControleurReseau.Controleur;

/**
 * Classe permettant de gerer les differentes vues de notre programme, les interactions avec l'utilisateur.
 * 
 *  <p> les liens entre les differentes vues du programme, permettant d'instancier et de cacher les differentes 
 *  vues de notre programme. <p>
 *  
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */

public class Vue {
	
	/**
	 * HashMap permettant de lier une string avec une JFrame, permettant une recherche rapide de la frame. 
	 */
	private HashMap<String,JFrame> pages;
	
	/**
	 * Permettant de faire le lien entre les vues et l'automate. 
	 */
	private Controleur controleur;
	
	/**
	 * Instancie un nouvel objet de classe.
	 * @param controleur Permet de faire le lien entre la vue et le model.  
	 */
	public Vue(Controleur controleur)
	{
		this.controleur = controleur;
		pages = new HashMap<String,JFrame>();
	}
	
	/**
	 * Permet de cacher la vue cibler.
	 */
	public void cacherPages()
	{
		Iterator<String> i  = pages.keySet().iterator();
		while(i.hasNext())
		{
			pages.get(i.next()).setVisible(false);
		}
	}
	
	
	/**
	 * @param chatID Identifiant unique d'un chat
	 * @return Retourne le vue du chat. 
	 */
	public VueChat getChat(int chatID)
	{
		String nomPage = "chat"+chatID;
		
		// Si le chat n'existe pas dans la liste des chats
		if(!pages.containsKey(nomPage))
		{
			
			//On le crée
				// On récupère son nom
			String nom = ((VuePagePrincipale)getPage("pagePrincipale")).getChatNameByID(chatID);
			VueChat pageAAfficher = new VueChat(this,chatID, nom);
			
			// On l'ajoute à l'HashMap de pages
			pages.put(nomPage,pageAAfficher);
			
			// On affiche la page		
			return pageAAfficher;	
		}
		else
			return (VueChat) pages.get(nomPage);
	
	}
	
	/**
	 * Methode permettant d'afficher un nouvelle page chez le client.
	 * La page est creer si et seulement si la page n'existe pas encore.
	 * La methode ecrase,(cache) toutes les autres les autres pages.
	 * @param page Nom de la page a afficher.
	 */
	public void afficherPage(String page)
	{
		JFrame pageAAfficher = null;
		
		cacherPages();
		
		if(pages.containsKey(page))
			pageAAfficher = pages.get(page);
		else // si la page n'existe pas
		{
			
			switch(page) // on l'initialise 
			{
				case "Accueil":
					pageAAfficher = new VueAccueil(this);
					
				break;
				
				case "Attente":
					pageAAfficher = new VueAttente(this);
				break;
				

				case "pagePrincipale":
					pageAAfficher = new VuePagePrincipale(this);
				break;
				

			}
			// on la met dans le dictionnaire
			
			pages.put(page,pageAAfficher);
		}
		
		pageAAfficher.setVisible(true);
	}
	
	/**
	 * Affiche la page du chat, possedant l'identifiant place en parametre
	 * @param idChat Identifiant unique du chat
	 */
	public void afficherChat(int idChat)
	{

		getChat(idChat).setVisible(true);
	}
	
	/**
	 * Methode permettant d'afficher un nouvelle page chez le client.
	 * La page est creer si et seulement si la page n'existe pas encore.
	 * La methode laisse toutes les autres fenetres visible.
	 * @param page Nom de la page a afficher.
	 */
	public void afficher1Page(String page)
	{
		JFrame pageAAfficher = null;
		
		
		if(pages.containsKey(page))
			pageAAfficher = pages.get(page);
		else // si la page n'existe pas
		{
			
			switch(page) // on l'initialise 
			{
				case "Accueil":
					pageAAfficher = new VueAccueil(this);
					
				break;
				
				case "Attente":
					pageAAfficher = new VueAttente(this);
				break;
				

				case "pagePrincipale":
					pageAAfficher = new VuePagePrincipale(this);
				break;

			}
			// on la met dans le dictionnaire
			
			pages.put(page,pageAAfficher);
		}
		
		pageAAfficher.setVisible(true);
	}
	
	/**
	 * Methode permettant de retourner la page place en parametre. 
	 * @param nom Nom de la page recherche.
	 * @return Retourne la JFrame correspondante.
	 */
	public JFrame getPage(String nom)
	{

		if(pages.containsKey(nom))
			return pages.get(nom);
		else // si la page n'existe pas
		{
			
			switch(nom) // on l'initialise 
			{
				case "Accueil":
					pages.put(nom, new VueAccueil(this));					
				break;
				
				case "Attente":
					pages.put(nom, new VueAttente(this));
				break;

				case "pagePrincipale":
					pages.put(nom, new VuePagePrincipale(this));
				break;
			}
		}
		
		return pages.get(nom);
		
	}
	
	/**
	 * Methode permettant de cacher la page recherche.
	 * @param nom Nom de la page a cacher. 
	 */
	public void CacherPage(String nom)
	{
		pages.get(nom).setVisible(false);
	}
	
	/**
	 * @return Retourne le controleur.
	 */
	public Controleur getControleur() 
	{
		return controleur; 
	}
}
