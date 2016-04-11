/*************************************************************************
                           MERE  -  Le rôle de la tâche mère est d'initialiser 
                           d'initialiser et de terminer l'application. Elle
                           crée les différents IPC ainsi que les tâches.
                             -------------------
    début                : MERE
    copyright            : (C) MERE par Antoine Breton antoine.breton@insa-lyon.fr
    e-mail               : MERE
*************************************************************************/

//---------- Réalisation de la tâche <MERE> (fichier MERE.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//------------------------------------------------------ Include personnel
#include "Heure.h"
#include "Mere.h"
#include "GestionClavier.h"
#include "Outils.h"
#include "Sortie.h"
#include "IPC.h"
#include "BarriereEntree.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int fileID;
//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

int main ()
// Algorithme : 
//Phase d'initialisation : Création des passifs, création des actifs;
//Phase moteur : en attente de la fin de la gestion clavier;
//Destruction : destruction des actifs, destruction des passifs;
{
	
	// -------------- INITIALISATION ---------------------- //
	pid_t noClavier;

	// Création du tableau de pid
	pid_t TablePid [6];
	// Création du tableau des mémoires partagés
	int TableMem[2];
        
        
	// 1 --- Création des passifs ------------------------
	
	// 1.1 Création de la file
	fileID = CreerFileMessage();

	// 1.2 Création du sémaphore général
	int semID = semget(ftok(chemin, CLE_SEM), NB_SEM_ELEM, IPC_CREAT|DROITS);
  
	// Initialisation des sémaphores élémentaires
	semctl(semID, PROF_BLAISE_PASCAL, SETVAL, 0);	// Au départ il n'y a aucun jeton donc la valeur initiale est 0 	
	semctl(semID, AUTRE_BLAISE_PASCAL, SETVAL, 0);	// Au départ il n'y a aucun jeton donc la valeur initiale est 0 
	semctl(semID, ENTREE_GASTON_BERGER, SETVAL, 0);	// Au départ il n'y a aucun jeton donc la valeur initiale est 0 
	semctl(semID, REQ_SEM, SETVAL, 1);	// Au départ il est libre donc on initialise la valeur à 1
	semctl(semID, NB_PLACE_SEM, SETVAL, 1);	// Au départ il est libre donc on initialise la valeur à 1
	semctl(semID, PARKING_SEM, SETVAL, 1);	// Proteger la RC tableau de place

	// 1.3 Création de la mémoire partagée Parking qui gère le nombre de place, et la position des voitures
	TableMem[MEM_PARKING] = shmget(ftok(chemin, 1), sizeof(MemParking), IPC_CREAT|DROITS);

	// Initialisation du nombre de place
	MemParking* pakingLibre = (MemParking*) shmat(TableMem[MEM_PARKING], NULL, 0) ;	
	pakingLibre -> nbPlace = 8;	
	int clef = ftok(chemin, 2);

	// 1.4 Création de la mémoire partagée qui gère les requêtes 
	TableMem[REQUETES] = shmget(clef, sizeof(MemRequete), IPC_CREAT|DROITS);

	// Initialisation de la requete Mem	
	MemRequete* requetes = (MemRequete*) shmat(TableMem[REQUETES], NULL, 0) ;	
	requetes->requetes[PROF_BLAISE_PASCAL] = {0, 'N'};
	requetes->requetes[AUTRE_BLAISE_PASCAL] = {0, 'N'};
	requetes->requetes[ENTREE_GASTON_BERGER] = {0, 'N'};

  // 2 ---- Création des actifs ------------------------

	// Initialiation de l'appli
	InitialiserApplication(XTERM);

	// 2 1 --- Création du clavier
	// Tâche clavier
	if( (noClavier = fork ()) == 0)
	{
		GestionClavier(fileID);
	}
	// Création de ENTREE1
	else if ( (TablePid[ENTREE1] = fork()) == 0)
	{
		GestionBarriereEntre(fileID, PROF_BLAISE_PASCAL,semID,TableMem[MEM_PARKING],TableMem[REQUETES]);
	}
	// Création de ENTREE2
	else if ( (TablePid[ENTREE2] = fork()) == 0)
	{
		GestionBarriereEntre(fileID, AUTRE_BLAISE_PASCAL ,semID,TableMem[MEM_PARKING],TableMem[REQUETES]);
	}
	// Création de ENTREE3
	else if ( (TablePid[ENTREE3] = fork()) == 0)
	{
		GestionBarriereEntre(fileID, ENTREE_GASTON_BERGER,semID,TableMem[MEM_PARKING],TableMem[REQUETES]);
	}
	// Création de SORTIE
	else if ( (TablePid[SORTIE] = fork()) == 0)
	{
		Sortie (fileID, TableMem[MEM_PARKING],TableMem[REQUETES], semID);
	}
	// Père
	else 
	{				
		// 2 3 Création de l'heure
		
		TablePid[THEURE] = ActiverHeure();	

		// --------------- MOTEUR ----------------------------- //
		// On attends la fin du fils
		waitpid(noClavier,NULL,0);
		

		// --------------- DESTRUCTION ------------------------ //

		// ------- 2 Destruction des Actifs --------------------- //
		
		// Destruction des tâches
		
		for(int i =0; i<5; i++)
		{
			kill(TablePid[i], SIGUSR2);
		}
		
		//Terminer appli
    TerminerApplication();
		
		// ------- 2 Destruction des Passifs ------------------- //
		SupprimerFileMessage(fileID);
		// 2.1 déstruction mémoire partagés
		
		for(int i =0; i<2; i++)
		{
			shmctl(TableMem[i], IPC_RMID, NULL); // Appel peut être différé si il y a encore des gens attachés
		}
		
		// 2.2 destruction du sémapore général
		semctl(semID, 0, IPC_RMID, 0);
		shmdt(pakingLibre);
		shmdt(requetes);
	}	


	return 0;
}


