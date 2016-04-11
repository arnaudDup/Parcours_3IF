/*************************************************************************
                           IPC  -  Ce module encapsule certain services
des IPCs. L'objectif est de concerver un exemple d'utilisation des IPC
pour une potentielle future réutilisation personelle. Dans cette optique,
tous les services IPC de l'application ne sont pas dans ce modules.

                             -------------------
    début                : 15/04
    copyright            : (C) IPC par Arnaud Dupeyrat et Antoine Breton
    e-mail               : antoine.breton@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <IPC> (fichier IPC.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
//------------------------------------------------------ Include personnel
#include "IPC.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
static struct sembuf reserver = {NB_PLACE_SEM, -1 ,0};
// Structure permettant d'effectuer une opération P protégeant la mémoire
// partagé contenant le nombre de place.

static struct sembuf liberer = {NB_PLACE_SEM, 1, 0};
// Structure permettant d'effectuer une opération V protégeant la mémoire
// partagé contenant le nombre de place.

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques


int ReserverPlaceSiPossible (MemParking* nbPlaceStruct, int semId)
{
	int res ;   // retourne le nombre de places libres dans le parking.

	// On Reserve le sem
	semop(semId, &reserver, 1);
	
	// On lit la valeur
	res = nbPlaceStruct->nbPlace;

	if(res > 0)
	{
		nbPlaceStruct->nbPlace--;	
		//res = nbPlaceStruct->nbPlace;
	
	}
	
	// On relache le sem
	semop(semId, &liberer, 1);

	return res;
}
// Fin de ReserverPlaceSiPossible

int LirePlace (MemParking* nbPlaceStruct, int semId)
{
	int res ;

	// On Reserve se sem
	semop(semId, &reserver, 1);
	
	// On lit la valeure 
	res = nbPlaceStruct->nbPlace;
	
	// On relache le sem
	semop(semId, &liberer, 1);

	return res;
}
// Fin de LirePlace

void LibererPlace(MemParking* nbPlaceStruct, int semId)
{

	// On Reserve se sem
	semop(semId, &reserver, 1);
	
	// On lit la valeure 
	nbPlaceStruct->nbPlace++;
	
	// On relache le sem
	semop(semId, &liberer, 1);
}
// Fin de LibererPlace

int CreerFileMessage ()

{
	return msgget(IPC_PRIVATE, 0700 | IPC_CREAT);
}
// Fin de CreerFileMessage

int SupprimerFileMessage (int ID)
{
	return msgctl(ID, IPC_RMID,0);
}
// Fin de SupprimerFileMessage

int EcrireFileMessage (int ID, const void * msgStruct, typeMsg t)
{
  switch(t)
  {
    case VOITURE : 
      return msgsnd(ID, msgStruct, (sizeof(Voiture)-sizeof(long)), 0);
    break;

    case NUMERO_EMPLACEMENT : 
      return msgsnd(ID, msgStruct, (sizeof(NumeroEmplacement)-sizeof(long)), 0);
    break;
  }
	return -1;
}
// Fin de EcrireFileMessage

int LireVoitureFileMessage (int ID, long numBarriere, Voiture * voiture)
{
	return msgrcv(ID, voiture, (sizeof(*voiture)-sizeof(long)), numBarriere,0);
}
// Fin LireVoitureFileMessage

int LireEmplacementFileMessage (int ID, long numBarriere, NumeroEmplacement * numeroEmplacement )
{
	return msgrcv(ID, numeroEmplacement, (sizeof(*numeroEmplacement)-sizeof(long)), numBarriere,0);
}
// Fin LireEmplacementFileMessage
