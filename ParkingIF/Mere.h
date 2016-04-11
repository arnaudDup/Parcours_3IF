/*************************************************************************
                           MERE 
                             -------------------
    début                : 18/03/16
    copyright            : (C) MERE par Antoine Breton 
    e-mail               : antoine.breton@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <MERE> (fichier MERE.h) -------
#if ! defined ( MERE_H )
#define MERE_H

//------------------------------------------------------------------------
// Le rôle de la tâche mère est d'initialiser 
// d'initialiser et de terminer l'application. Elle
// crée les différents IPC ainsi que les tâches.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

// Définition des différents noms des tâches, utiles pour le tableau de pid
enum TypeTache { THEURE, ENTREE1, ENTREE2, ENTREE3, SORTIE };
enum memoirePartage{MEM_PARKING, REQUETES};

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

int main();


#endif // MERE_H


