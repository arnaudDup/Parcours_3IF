/*************************************************************************
 GestionBarriere
 -------------------
 dÈbut                : 9/04/2016
 copyright            : (C) 2016 par Arnaud Dupeyrat
 *************************************************************************/

//---------- Interface de la classe GestionBarriere.h (fichier GestionBarriere.h) ------
#if ! defined GESTIONBARRIERE_H
#define GESTIONBARRIERE_H
//--------------------------------------------------- Interfaces utilisÈes
#include "Config.h"
#include "Outils.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// ROLE:
// Le module permet de gérer les entrées dans le parking.
// Le module peut prendre en charge plusieurs barrieres.
//
//------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////// PUBLIC


void GestionBarriereEntre(int identifiantFilesVoiture ,TypeBarriere barriere,
                          int identifiantSemaphore,
                          int identifiantMemoireParking,
                          int identifiantMemoireRequete );

// Mode d'emploi:
//
// attribut:
// < barriere > : identifiant sur la barriere que gere le processus.
// < identifiantFilesVoiture > : identifiant sur la boite aux lettres.
// < identifiantSemaphore > : identifiant sur le sémaphore générale.
// < identifiantmemoire > : identifiant sur la mémoire partage.
//
// Procédure permettant de gérer la gestion des bariéres entrées.
// La procédure laisse entrer les voitures si le parking est vide.
// La procédure met à jour la place sur lequel la voiture est effectivement.
// La procédure met à jour la mémoire partagé, qui représente le parking
// La procédure s'endort si le parking est plein et attends qu'une place se libére. 
//
// contrat: Aucun.



#endif // GestionBarriere_H
