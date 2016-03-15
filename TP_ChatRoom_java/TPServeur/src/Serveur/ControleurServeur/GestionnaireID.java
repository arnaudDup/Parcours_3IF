package Serveur.ControleurServeur;

import Serveur.ManageServeur.ModeleServeur;

/**
 * Classe permettant d'implementer un gestionnaire d'ID.
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */

public class GestionnaireID {
	
	/**
	 *  Identifiant unique de l'utilisateur.
	 */
	private static int NB_USER = 0;
	
	/**
	 * @return Retourne un identifiant unique.
	 */
	public static int getUserId()
	{
		return NB_USER++;
	}
	
}
