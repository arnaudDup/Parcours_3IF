/*************************************************************************
Capteur.h  -  description
 -------------------
 d�but                : 23/10/2014
 copyright            : (C) 2015 par Jacques Foll�as et Arnaud Dupeyrat
 *************************************************************************/

//---------- Interface de la classe Capteur (fichier Capteur.h) ------
#if ! defined ( CAPTEUR_H )
#define CAPTEUR_H

//--------------------------------------------------- Interfaces utilis�es

//------------------------------------------------------------- Constantes 

const int JOURS    =  7; // nombre de jours dans la semaine.
const int HEURES   = 24; // nombre d'heures dans la journ�e.
const int MINUTES  = 60; // nombre de minutes dans une heure.
const int COULEURS =  4; // nombre de couleurs qui peuvent �tre enregistr�es par un capteur.
// Afin de ne pas faire un new de tableau � plusieurs dimensions, nous en avons recr�� un �
// la main. Pour ce faire nous avons eu besoin de definir les constantes suivantes afin de proc�der
// de fa�on similaire a une d�composition en facteur premier. 
const int CHOIXJOUR = (HEURES+1)*(MINUTES+1)*(COULEURS+1); // multipli� par un jour, permet de selectionner un jour de la semaine.
const int CHOIXHEURE = (MINUTES+1)*(COULEURS+1); // multipli� par une heure, permet de selectionner une heure de la journ�e.
const int CHOIXMINUTE = (COULEURS+1); // multipli� par une minute, permet de selectionner une minute de l'heure selectionn�e.
// en sommant ces trois multiplications et en ajoutant le num�ro d'une couleur on arrive alors � identifier
// chaques �v�nements de mani�re unique et donc � recr�er un tableau � 4 dimensions dans un tableau � une dimension.


//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe Capteur
// Elle permettra de stocker dans un tableau d'entier le nombre de fois qu'est apparu chaques couleurs
// chaques minutes de la semaine dans un tableau d'entier et offre quelques fonctions qui permettent
// l'executions de certaines commandes accessible � l'utilisateur.
//
//------------------------------------------------------------------------ 

class Capteur 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques

	inline int getIDParametre()
        {
            return ID;
        }
    // Mode d'emploi: permet de recup�rer l'identifiant du capteur appelant
    // pour le retrouver dans la structure de donn�es du traffic.

    void STAT_C ();
    // Mode d'emploi :
    // appel� par un capteur sans param�tres cette fonction � pour fonction de nous afficher
	// le pourcentage de chaques couleurs, en se basant sur toutes les mesures prises dans la semaine. 

    void InserTableau ( int jour, int heure, int minute, int couleur );
    // <jour> : jour de la semaine de prise de mesures.
    // <heure> : heure de la journ�e de la prise de mesures.
    // <minute> : minute de l'heure de la prise de mesures.
    // <couleur> : couleur mesur�e par le capteur.

    	// Mode d'emploi :
	// Lors de l'insertion d'une valeur dans le tableau on incr�mente le tableau du capteur mais �galement 
	// le tableau de traffic pour qu'il contienne le nombre de fois qu'une <coueleur> a �t� recup�r� par les capteurs,
	// ainsi que la somme sur les <jour>s, les <heure>s, ainsi que sur l'ensemble des <couleur>s.
	// Cela est effectu� en apelant la fonction trafficRemplirTableau.
	// De plus on a rajout� � chaques dimensions du tableau une case contenant les sommes respectives des 
    // couleurs mesur� sur une minute, une heure, une journ�e et sur l'ensemble de la semaine,
    // pour chaques couleurs et pour toutes couleurs confondues.

    // int GetID ();
    // Mode d'emploi:
    // Retour l'ID du capeur appelant la m�thode.


    
  
//------------------------------------------------- Surcharge d'op�rateurs
   

//-------------------------------------------- Constructeurs - destructeur
 

Capteur (int IDParametre );
    // <IDParamtre> : identifiant du capteur qui va permetre de le placer et de le
    // retrouver dans la structure de donn�es.
    // Mode d'emploi:
    // construit un objet de type capteur avec IDParametre comme identifiant
    // Contrat :
    // l'ID ne doit pas �tre plus grand qu'un int et doit �tre sup�rieur strictement � zero.
    
    ~Capteur ( );
    // Mode d'emploi :
    // D�truit le capteur appelant la fonction.

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

private:
//------------------------------------------------------- M�thodes priv�es

protected:
//----------------------------------------------------- Attributs prot�g�s
int ID ;    // Identifiant du capteur. Il nous permettra de le retrouver dans notre
            // structure de donn�es qui contient tous nos objets capteurs.
int * tableauCapteur ;  // Ce pointeur pointera sur la m�moire alou�e contenant
                        //toutes les informtions r�cup�r�es par le capteur mod�lis� par l'objet de type Capteur.
private:
//------------------------------------------------------- Attributs priv�s

//---------------------------------------------------------- Classes amies

friend class Traffic ; // On met en amis la classe capteur pour pouvoir utiliser ses attribut dans OPT
    

//-------------------------------------------------------- Classes priv�es

//----------------------------------------------------------- Types priv�s

};


#endif // CAPTEUR_H
