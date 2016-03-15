/*************************************************************************
Capteur.h  -  description
 -------------------
 début                : 23/10/2014
 copyright            : (C) 2015 par Jacques Folléas et Arnaud Dupeyrat
 *************************************************************************/

//---------- Interface de la classe Capteur (fichier Capteur.h) ------
#if ! defined ( CAPTEUR_H )
#define CAPTEUR_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

const int JOURS    =  7; // nombre de jours dans la semaine.
const int HEURES   = 24; // nombre d'heures dans la journée.
const int MINUTES  = 60; // nombre de minutes dans une heure.
const int COULEURS =  4; // nombre de couleurs qui peuvent être enregistrées par un capteur.
// Afin de ne pas faire un new de tableau à plusieurs dimensions, nous en avons recréé un à
// la main. Pour ce faire nous avons eu besoin de definir les constantes suivantes afin de procéder
// de façon similaire a une décomposition en facteur premier. 
const int CHOIXJOUR = (HEURES+1)*(MINUTES+1)*(COULEURS+1); // multiplié par un jour, permet de selectionner un jour de la semaine.
const int CHOIXHEURE = (MINUTES+1)*(COULEURS+1); // multiplié par une heure, permet de selectionner une heure de la journée.
const int CHOIXMINUTE = (COULEURS+1); // multiplié par une minute, permet de selectionner une minute de l'heure selectionnée.
// en sommant ces trois multiplications et en ajoutant le numéro d'une couleur on arrive alors à identifier
// chaques événements de manière unique et donc à recréer un tableau à 4 dimensions dans un tableau à une dimension.


//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe Capteur
// Elle permettra de stocker dans un tableau d'entier le nombre de fois qu'est apparu chaques couleurs
// chaques minutes de la semaine dans un tableau d'entier et offre quelques fonctions qui permettent
// l'executions de certaines commandes accessible à l'utilisateur.
//
//------------------------------------------------------------------------ 

class Capteur 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	inline int getIDParametre()
        {
            return ID;
        }
    // Mode d'emploi: permet de recupérer l'identifiant du capteur appelant
    // pour le retrouver dans la structure de données du traffic.

    void STAT_C ();
    // Mode d'emploi :
    // appelé par un capteur sans paramètres cette fonction à pour fonction de nous afficher
	// le pourcentage de chaques couleurs, en se basant sur toutes les mesures prises dans la semaine. 

    void InserTableau ( int jour, int heure, int minute, int couleur );
    // <jour> : jour de la semaine de prise de mesures.
    // <heure> : heure de la journée de la prise de mesures.
    // <minute> : minute de l'heure de la prise de mesures.
    // <couleur> : couleur mesurée par le capteur.

    	// Mode d'emploi :
	// Lors de l'insertion d'une valeur dans le tableau on incrémente le tableau du capteur mais également 
	// le tableau de traffic pour qu'il contienne le nombre de fois qu'une <coueleur> a été recupéré par les capteurs,
	// ainsi que la somme sur les <jour>s, les <heure>s, ainsi que sur l'ensemble des <couleur>s.
	// Cela est effectué en apelant la fonction trafficRemplirTableau.
	// De plus on a rajouté à chaques dimensions du tableau une case contenant les sommes respectives des 
    // couleurs mesuré sur une minute, une heure, une journée et sur l'ensemble de la semaine,
    // pour chaques couleurs et pour toutes couleurs confondues.

    // int GetID ();
    // Mode d'emploi:
    // Retour l'ID du capeur appelant la méthode.


    
  
//------------------------------------------------- Surcharge d'opérateurs
   

//-------------------------------------------- Constructeurs - destructeur
 

Capteur (int IDParametre );
    // <IDParamtre> : identifiant du capteur qui va permetre de le placer et de le
    // retrouver dans la structure de données.
    // Mode d'emploi:
    // construit un objet de type capteur avec IDParametre comme identifiant
    // Contrat :
    // l'ID ne doit pas être plus grand qu'un int et doit être supérieur strictement à zero.
    
    ~Capteur ( );
    // Mode d'emploi :
    // Détruit le capteur appelant la fonction.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
int ID ;    // Identifiant du capteur. Il nous permettra de le retrouver dans notre
            // structure de données qui contient tous nos objets capteurs.
int * tableauCapteur ;  // Ce pointeur pointera sur la mémoire alouée contenant
                        //toutes les informtions récupérées par le capteur modélisé par l'objet de type Capteur.
private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

friend class Traffic ; // On met en amis la classe capteur pour pouvoir utiliser ses attribut dans OPT
    

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};


#endif // CAPTEUR_H
