/*************************************************************************
 Traffic.h  -  description
 -------------------
 début                : 23/10/2015
 copyright            : (C) 2015 par Jacques Folleas et Arnaud Dupeyrat
 *************************************************************************/

//---------- Interface de la classe Taffic (fichier Traffic.h) ------

//--------------------------------------------------- Interfaces utilisées
# include "Capteur.h"

typedef struct Element
{
    Capteur * capteur;
    struct Element * droite;  /* pointeur sur la partie droite de l'arbre */
    struct Element * gauche;  /* pointeur sur la partie gauche de l'arbre */

}Element;

// Définition de la structure de données qui va être la base de notre B-arbre.

//------------------------------------------------------------- Constantes


//Ces constantes sont utiles pour definir le tableau static.

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Traffic:
// La classe a pour but à travers ces deux attributs de gérer la "base de données" contenant les capteurs
// en effet celle-ci permet une recherche rapide d'élements ( utilisation d'un B-arbre).
// permettant d'effectuer les différents tests demandés.

//-----------------------------------------------------------------------


#ifndef __Capteur__Traffic__
#define __Capteur__Traffic__

class Traffic
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- Méthodes publiques
    
    bool AjouterElement (int IDParametre, int jour, int heure, int minute, int couleur);
    
    // < IDParametre > : ID du capteur néccessaire pour le retrouver dans notre structure de données.
    // < jour > : d7 nous permet de connaitre le jour de la semaine où le capteur a envoyé des résultats.
    // < heure > : nous permet de connaitre l'heure de la semaine où le capteur a envoyé des résultats.
    // < minute > : nous permet de connaitre la minute de la semaine où le capteur a envoyé des résultats.
    // < Couleur > : nous permet de connaitre l'état du traffic.
    
    // Mode d'emploi :
    // La méthode a pour but de rechercher dans le B-arbre l'emplacement du capteur dont on cherche à modifier les
    // données
    // enregistrées représentant son activité à un instant donné, si ce capteur est présent nous modifions son
    // tableau
    // d'activité si c'est un nouveau capteur (<IDParamete> différents de celui rentré auparavant) alors nous cherchons
    // son emplacement "optimal". c'est à dire s'appuyant sur les règles du B-arbre.
    
    
    void AffichageArbre (Element * traffic );
    
    // < traffic > : racine du B-arbre
    
    // Mode d'emploi :
    // La méthode a pour but d'afficher les différents éléments du B-arbre dans l'ordre décroissant
    

    
    Capteur * RechercheElement (int IDParametre);
    
     // < IDParametre > : Id du capteur
    
    // Mode d'emploi :
    // La méthode parcourt la structure de données et renvoie le capteur correspondant au numéro d'identifiant demandé
    
    // Contrat :
    
    inline Element * gettraffic ()
    {
        return traffic;
    }
    
    void JAM_DH (int jour );
	// <jour> : code correspondant au jour de la semaine sur lequel on veut faire nos statistiques.

    // Mode d'emploi : Affiche pour chaque heure les pourcentages de couleur rouge plus celui de
	// couleur noire mesurées, modélisant un traffic encombré, par l'ensemble des capteurs présents sur le traffic
	// à toutes les heures du <jour> correspondant à l'entier placé en paramètre.
    // Si aucune valeur n'a été récupérée par un capteur pour le <jour> indiqué alors la commande affiche tous les pourcentages à 0%.

	void STATS_D7 (int jour);
	// <jour> : code correspondant au jour de la semaine sur lequel on veut faire nos statistiques.

        //Mode d'emploi : 
    // Affiche les pourcentages de couleurs mesurées par l'ensemble des capteurs présents sur le traffic durant le jour de la semaine
	// correspondant à l'entier placé en paramètre.
    // Si aucune valeur n'a été récupérée par un capteur pour le <jour> indiqué alors la commande affiche tous les pourcentages à 0%.


   
    void OPT(int jour, int heureDepartMin, int heureArriveeMax, int nombreDeSegment, int * Seg);
    // <jour> : code correspondant au jour de la semaine où l'on souhaite calculer le temps optimal.
    // <heureDepartMin> : heure du départ le plus tôt que l'on peut faire.
    // <heureArriveeMax> : heure de l'arrivée la plus tard que l'on peut faire.
    // <nombreDeSegment> : le nombre d'ID de capteur qui seront placés en paramètre après ce dernier paramètre.
	// <Seg> : pointeur sur le premier élément du tableau d'entiers contenant les IDs des capteurs à passer devant.

	// Mode d'emploi:
	// Affiche l'heure de départ la plus tôt après <heureDepartMin> pour laquelle on passe le temps de trajet
	// le plus court et qui permet d'arriver avant l'heure <heureArriveeMax>.
	// le trajet est représenté par l'ensemble des segments mis en paramètre. 
	// On considère qu'il faut 1 minute pour passer un segment avec une mesure V, 2 pour J, 4 pour R,et 10 pour N.
    // Pour calculer le temps pour passer devant un segement on fait la moyenne pondérée par les temps par couleur
    // avec les pourcentages de couleur mesurés, par le capteur, chaque heure et chaque minute pour le <jour> indiqué en paramètre.
	// Si jamais pour une minute le capteur n'a aucune information, alors on considère que le capteur n'a enregistré que V.
    
    //------------------------------------------------- Surcharge d'opérateurs
    
    
    //-------------------------------------------- Constructeurs - destructeur
   
    
    Traffic ( );
    // constructeur de traffic.
    
    virtual ~Traffic ( );
    // destructeur de traffic.
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- Méthodes protégées
    
private:
    //------------------------------------------------------- Méthodes privées
     Element * CreationElement (int IDParametre );
     void Desallocation (Element * &traffic);
     void trafficRemplirTableau (int jour, int heure, int minute, int couleur );
protected:
    //----------------------------------------------------- Attributs protégés
    Element * traffic;
    int NBCapteur;
    int StableauCapteur [JOURS+1][HEURES+1][MINUTES+1][COULEURS+1];
private:
    //------------------------------------------------------- Attributs privés
    
    //---------------------------------------------------------- Classes amies

    //-------------------------------------------------------- Classes privées
    
    //----------------------------------------------------------- Types privés
    
};

//----------------------------------------- Types dépendants de Traffic


#endif /* defined(__Capteur__Traffic__) */
