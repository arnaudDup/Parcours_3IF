/*************************************************************************
                           IPC  -  Ce module encapsule certain services
des IPCs. L'objectif est de concerver un exemple d'utilisation des IPC
pour une potentielle future réutilisation personelle. Dans cette optique,
tous les services IPC de l'application ne sont pas dans ce modules.

                             -------------------
    début                : 15/04
    copyright            : (C) IPC par Arnaud Dupeyrat et Antoine Breton
    e-mail               : arnaud.dupeyrat@insa-lyon.fr et antoine.breton@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <IPC> (fichier IPC.h) ---------
#if ! defined ( IPC_H )
#define IPC_H


/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Config.h"
#include <sys/sem.h>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int CreerFileMessage ();
//
// Contrat : Créer une file de message et retourne sont identifiant en cas
// de succès
//

int SupprimerFileMessage (int ID);
//
// Contrat : Supprime une file de message dont l'ID est passé en paramètre
// Retourne -1 en cas d'erreure
//

int EcrireFileMessage (int ID, const void * msgStruct, typeMsg t);
// Mode d'emploi:
// Cette fonction permet de poster un message dans une file de message.
// attribut:
// <ID> : identifiant de la file de message sur laquelle on veut écrire un message.
// <msgStruct> : Message qui va être posté dans la file de message
// <t> : type de message qui va être posté. Il peut être de deux types : VOITURE ou NUMERO_EMPLACEMENT


int LireVoitureFileMessage (int ID, long numBarriere, Voiture * voiture);
// Mode d'emploi:
// Cette fonction permet de lire une Voiture, présente à une certaine barrière, sur une file de message. 
// <return>: correspond au return de msgrcv.

// attribut:
// <ID> : identifiant de la file de message sur laquelle on récuperer la voiture.
// <numBarriere> : correspond au numéro de la barriere concernée.
// <t> : type de message qui va être posté. Il peut être de deux types : VOITURE ou NUMERO_EMPLACEMENT

int ReserverPlaceSiPossible (MemParking* nbPlaceStruct, int semId);
// Mode d'emploi:
// Cette fonction décrémente le nombre de place disponible, s'il y en à.
// La concurence est sychronisée par mutex.
// <return>: On retourne le nombre de place, avant la reservation.
// 
// attribut:
// <nbPlaceStruct> : mémoire partagée sur laquelle on lit le nombre de place courant.
// <semId> : ID du sémaphore qui protège la lecture. 

int LireEmplacementFileMessage (int ID, long numBarriere, NumeroEmplacement * numeroEmplacement );
// Mode d'emploi:
// Cette fonction retourne le dernier message de type numéroEmplacement, d'une file de message. (utilisé dans la sortie)
// <return>: correspond au return de msgrcv.

// attribut:
// <ID> : Identifiant de la file de message sur laquelle nous allons lire le message.
// <numBarriere> : Corresponds à l'identifiant de la barriere qui lit le message (Dans notre cas, la sortie).
// <numeroEmplacement> : Corresponds au message qui va être remplit.

int LirePlace (MemParking* nbPlaceStruct, int semId);
// Mode d'emploi:
// Cette méthode lit le nombre de place dans une mémoire partagée. L'utilisation est synchronisée par sémaphore.

// attribut:
// <nbPlaceStruct> : Structure de la mémoire partagée du parking, permetant de lire le nombre de place
// <semid> : identifiant du sémaphore.

#endif // IPC_H

