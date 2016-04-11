/*************************************************************************
                           SORTIE  - Cette tâche gère la barrière de sortie 
                           du parking. Son rôle est de, lorsqu'une voiture 
                           veux sortir, appeler le voiturier. Quand ce 
                           dernier à sorti la voiture la tâche doit également
                           afficher les informations concernant la voiture 
                           qui viens de sortir et décider qui est la prochaine 
                           voiture qui va rentré en cas de conflit.
                           
                           -------------------
                           
    début                : 18/03
    copyright            : (C) SORTIE par Antoine Breton
    e-mail               : antoine.breton@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <SORTIE> (fichier SORTIE.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <vector>
#include <sys/shm.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <errno.h>

//------------------------------------------------------ Include personnel
#include "Sortie.h"
#include "IPC.h"
#include "Outils.h"
#include "Config.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
// Identifiants des différents IPC
static int fileID;
static int memReqId; 	
static int memParkingId; 
static int semId;

static std::vector <pid_t> vecteurPidVoiturier; // vecteur permettant de stocker les pid des taches voiturier en cours.

// structure des mémoires partagées
static MemRequete* requetes; 
static MemParking* parking;

// sembuf permettant de manipuler les différents sémaphores
static struct sembuf reserverPlace = {NB_PLACE_SEM, -1 ,0};
static struct sembuf libererPlace = {NB_PLACE_SEM, 1, 0};
static struct sembuf reserverReq = {REQ_SEM, -1 ,0};
static struct sembuf libererReq = {REQ_SEM, 1, 0};
static struct sembuf reserverTab = {PARKING_SEM, -1 ,0};
static struct sembuf libererTab = {PARKING_SEM, 1, 0};

//------------------------------------------------------ Fonctions privées
static void finVoiturier(int noSignal);
static void destruction (int noSignal);
static int calculerJeton();

static void initialisation ()
// Mode d'emploi : 
// Cette fonction gère l'initialisation de la SORTIE.
// Elle s'attache aux mémoires partagés des requetes ainsi que du parking.
// Elle défini les handlers des signaux.
// Algorithme :
// Attachement à une mémoire partagé
// gestion des signaux
{
	// on s'attache à la mémoire partagée de requête --------------
	requetes = (MemRequete*) shmat(memReqId, NULL, 0) ;	
	parking = (MemParking*) shmat(memParkingId, NULL, 0) ;

  // Gestion des signaux --------------------------------------
  struct sigaction fin;
  struct sigaction voiturierAction;
  
  // On masque les autres signaux
  sigemptyset(&fin.sa_mask);
  sigemptyset(&voiturierAction.sa_mask);
  sigaddset(&fin.sa_mask, SIGCHLD);
  sigaddset(&voiturierAction.sa_mask, SIGUSR2);
  
   
  // Défini les handler
  fin.sa_handler = destruction;
  voiturierAction.sa_handler = finVoiturier ;
  
	//Armement des signaux
  sigaction(SIGUSR2,&fin,NULL);   
	sigaction(SIGCHLD,&voiturierAction,NULL);              
} 

static void finVoiturier(int noSignal)
// Mode d'emploi :
// Cette fonction est le Handler de fin de voiturier.
// Lorqu'un voiturier a finit son travail, elle affiche les informations concernant la sortie de la voiture,
// elle met a jour l'état courant du parking, puis, en cas de besoin, elle décide quelle voiture sera la prochaine à entrer.
//
{
  if(noSignal == SIGCHLD)
	{
		//On récupère la voiture concernée par la fin du voiturier -------

		int numPlace;    
    
		//Recuperer le fils qui a envoye le SIGCHLD
		pid_t pidVoiturier = wait(&numPlace);
    
    numPlace=WEXITSTATUS(numPlace);
    Afficher(MESSAGE, numPlace);
   
   	Voiture voiture;
		// On récupère la voiture dans la mémoire partagée du parking
		semop(semId, &reserverTab, 1);
		voiture = parking->voitures[numPlace];
		semop(semId, &libererTab, 1);

		

    // On affiche la sortie
		switch (voiture.typeUsager) 
		{
			case 'P' : 
			AfficherSortie(PROF, voiture.numeroMineralogique,voiture.heureArrive,time(NULL));			
			break;
	 
			case 'A' : 
			AfficherSortie(AUTRE, voiture.numeroMineralogique,voiture.heureArrive,time(NULL));			
			break; 
			
		}
		
		// On clear la zone d'affichage

		switch(voiture.numeroEmplacement)
		{
			case 1:
			Effacer(ETAT_P1);
			break;
			case 2:
			Effacer(ETAT_P2);
			break;
			case 3:
			Effacer(ETAT_P3);
			break;
			case 4:
			Effacer(ETAT_P4);
			break;
			case 5:
			Effacer(ETAT_P5);
			break;
			case 6:
			Effacer(ETAT_P6);
			break;
			case 7:
			Effacer(ETAT_P7);
			break;
			case 8:
			Effacer(ETAT_P8);
			break;
		}
		
		// On regarde si le parking est plein ------------------
		while(semop(semId, &reserverPlace, 1) == -1 && errno ==EINTR);
		
    
		int nbPlace = parking->nbPlace;
				
		if(nbPlace != 0) // s'il y a des places dans le parking
		{
			parking->nbPlace++;	// On augmente le nombre de place
			nbPlace = parking->nbPlace;
		}		
		
		else		// Si le parking est plein
		{
			// Trouver à qui donner le prochain jeton avec CalculerJeton		
			while(semop(semId, &reserverReq, 1) == -1 && errno ==EINTR);
			
			// S'il n 'y à pas de requêtes on sort et on augmente le nombre de places
			if(requetes->requetes[PROF_BLAISE_PASCAL].typeUsager == 'N'
				&&requetes->requetes[AUTRE_BLAISE_PASCAL].typeUsager == 'N'
				&&requetes->requetes[ENTREE_GASTON_BERGER].typeUsager == 'N' )
			{
				parking->nbPlace++;
			}	
			else
			{

			    int jeton = calculerJeton();

			    struct sembuf DonnerJeton = {(short unsigned int)jeton, 1, 0};
			
			    // On vide les requetes
			    switch(jeton)
			    {
				    case 1:
					    Effacer(REQUETE_R1);
				    break;
				    case 2:
					    Effacer(REQUETE_R2);
				    break;
				    case 3:
					    Effacer(REQUETE_R3);
				    break;
			    }

          requetes->requetes[jeton] = {0, 'N'};
			    // On donne un jeton
			    semop(semId, &DonnerJeton, 1);			

      }
      // On libère les requêtes
			semop(semId, &libererReq, 1);
				
		}
		
		semop(semId, &libererPlace, 1); // et on libère le sémaphore

    // On enleve le voiturier de la liste des voiturier Actif
    for( std::vector <pid_t>::iterator it = vecteurPidVoiturier.begin(); it!= vecteurPidVoiturier.end() ; it++)
    {
      if(*it == pidVoiturier)
      {
        vecteurPidVoiturier.erase(it);
        break;
      }
    }
	}
}
// Mode d'emploi :
// Cette fonction permet de décider à quelle voiture nous allons decerner le prochain jeton en cas de parking plein.
// Elle consultes la mémoire partagée "requête" et nécéssite donc qu'elle soit une section critique 
static int calculerJeton()
{
	int jeton = 0;

	Requete voiturePrioritaire;
	voiturePrioritaire.typeUsager='N';
	voiturePrioritaire.heureArrive=time(NULL)+10;
	
	// On regarde toutes nos bariere
	for(int i =1;i <4; i++)
	{

		if(requetes->requetes[i].typeUsager != 'N') 
		{
			if(requetes->requetes[i].typeUsager =='P')
			{
				if( (requetes->requetes[i].heureArrive <= voiturePrioritaire.heureArrive ) || voiturePrioritaire.typeUsager != 'P' )
				{
					voiturePrioritaire = requetes->requetes[i];
					jeton = i;
				}
			}
			else if(requetes->requetes[i].typeUsager !='P')
			{
				if( (requetes->requetes[i].heureArrive <= voiturePrioritaire.heureArrive) && voiturePrioritaire.typeUsager != 'P' )
				{
					voiturePrioritaire = requetes->requetes[i];
					jeton = i;
				}
			}
		}
	}
	

	return jeton;
}
static void moteur ()
// Mode d'emploi : 
// Cette Fonction correspond à la phase moteur de la tâche.
// Jusqu'à une interruption par SIGUSR2, on récupère la premiere voiture de la file sortie (s'il y en a une)
// On appelle le voiturier pour qu'il sorte la voiture.
{

		// structure permettant de récupere le jeton.

	while(true) // boucle principal du moteur
	{
		NumeroEmplacement numeroEmplacement;
		
		// On récupère la première voiture
   	while (LireEmplacementFileMessage(fileID,SORTIE_GASTON_BERGER,&numeroEmplacement) == -1 );
		
    // On appel le voiturier
    pid_t pidVoiturier = SortirVoiture(numeroEmplacement.numeroPlace);	

    // On enregistre son pid
    if(pidVoiturier != -1)
      vecteurPidVoiturier.push_back(pidVoiturier);
	}

} 

static void destruction (int noSignal)
// Mode d'emploi :
// Cette fonction est le handler du signal SIGUSR2 et déclanche la destruction de la tâche.
// Elle tue les processus voiturier en cours, puis se détâche de ses passifs avant de se suicider.
{
  if(noSignal == SIGUSR2)
    {
        // on masque le signal SIGCHLD pour éviter que que le processus supprime un elements du vecteur.

      struct sigaction action;
      action.sa_handler = SIG_IGN ;
      sigemptyset(&action.sa_mask);
      action.sa_flags = 0 ;
      sigaction(SIGCHLD,&action,NULL);
    
      for( std::vector <pid_t>::iterator it = vecteurPidVoiturier.begin(); it!= vecteurPidVoiturier.end() ; it++)
      {
          // On tue les processus, voiturier qui sont encore en état de marche.
          kill(*it,SIGUSR2);
          waitpid(*it,NULL,0);
      }

      // Détachement de la memoire partagé.
      shmdt(requetes);
      shmdt(parking);
      exit(0);

    }
} 
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Sortie (int FileID, int memShare, int memRqID, int semid)
// Algorithme :
// lancement des phases d'initialisation et moteur
{
	fileID=FileID;
	memReqId= memRqID;
	semId=semid;
	memParkingId = memShare; 
  
	initialisation();

	moteur();
} //----- fin de Nom


