/*************************************************************************
                       		 GestionClavier  
                             -------------------
    dÈbut                : 9/04/2016
    copyright            : (C) 2016 par Arnaud Dupeyrat
*************************************************************************/

//---------- Interface de la classe GestionClavier.h (fichier GestionClavier.h) ------
#if ! defined GESTIONCLAVIER_H
#define GESTIONCLAVIER_H
//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------ 
// ROLE: 
// Gestion des différentes saisie de l'utilisateur. 
// Permet de simuler les différentes sorties et arrivées des utilisateurs. 
//
//------------------------------------------------------------------------ 

////////////////////////////////////////////////////////////////////////////////////// PUBLIC

void Commande( char code, unsigned int valeur);

// Mode d'emploi:
//	
// attribut:
// < code > : valeur saisie par l'utilisateur.
// < valeur > : représentant la porte par laquelle l'utilisateur veut intéragir. 
// 
// Si code = P || p || a || A, la méthode simule l'arrivé d'un véhicule à l'entrée d'une
//								 barriére.
// Si code = S || s, la méthode simule la sortie d'un véhicule.
// Si code = E || e alors l'application se termine, déclenche le fin de la tache
//					gestionClavier. 
//
// contrat: la méthode gére uniquement les entrées cités au-dessus.
// Les entrées différentes sont alors non traités par l'application. 


void GestionClavier(int identifiantFilesVoiture);

// Mode d'emploi:
//
// attribut:
// < identifiantFilesVoiture > : identifiant de la boite aux lettres, servant de moyens 
//	de communication entre BarriereEntree et gestionClavier
//
// Méthode permettant de gérer les différents entrée clavier et d'effectuer leur
// différentes actions associées.
// procédure bloquante, c'est dire que l'utilisateur peut continuer à simuler les voitures 
// tant que la touche E n'est pas appuyé.



#endif // GESTIONCLAVIER_H
