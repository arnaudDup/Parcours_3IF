/*************************************************************************
 GestionBarriere  -  description
 -------------------
 début                : 15 mars 2016
 copyright            : (C) par Arnaud dupeyrat
 e-mail               : arnaud.dupeyrat@ginsa-lyon.fr
 *************************************************************************/

//---------- Réalisation du module <GestionBarriere> (fichier GestionBarriere.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
//------------------------------------------------------ Include personnel
#include "BarriereEntree.h"
#include "Config.h"
#include "IPC.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

static std::vector <Voiturier *> vecteurTacheVoiturier;
// Vecteur permettant de stocker les pid des taches voiturier en cours.

static int fileID;					                        
// Identifiant de la boite aux lettres. 

static int semID;					                        
// Identifiant du sémaphore générale.

static MemParking* pakingLibre; 				            
// Structure permettant de connaitre le nombre de place

static MemRequete* requetePartage;                          
// Structure permettant de mettre à jour les requétes pour rentrer dans le parking.

static int memID; 							                
// Identifiant de la mémoire partagé des places.

static int memIDRequete;                                    
// Identifiant de la mémoire partagé des requetes.

//------------------------------------------------------ Fonctions privées

static void masquerSignal (int numeroSignal)
// Mode d'emploi:
//
// Procédure permettant de masquer un signal <numeroSignal>
// Le programme ne répond plus à la reception du signal 
{
        struct sigaction action;
        action.sa_handler = SIG_IGN ;
        sigemptyset(&action.sa_mask);
        action.sa_flags = 0 ;
        sigaction(numeroSignal,&action,NULL);
}
// Fin de masquerSignal.

static void ecrireRequete (Requete requete, TypeBarriere barriere)
// Mode d'emploi:
//
// Procédure permettant de rajouter la <requete> dans la mémoire partagé.
// L'emplacement de la requete est alors définit par <barriere>
{
    static struct sembuf reserver = {REQ_SEM, -1 ,0};
    // structure permettant d'effectué un P
    static struct sembuf liberer = {REQ_SEM, 1 ,0};
    // structure permettant d'effectué un V

    // On effectue un P.
    semop(semID, &reserver, 1);
    
    // on ecris dans la mémoire partagé
    requetePartage->requetes[barriere] = requete;
    
    // On effectue un V.
    semop(semID, &liberer, 1);
}
// Fin de ecrireRequete

static void ecrireVoiture (Voiture voiture, int place)
// Mode d'emploi:
//
// Procédure permettant de rajouter la <voiture> dans la mémoire partagé.
// L'emplacement de la requete est alors définit par <place>,
// permettant de connaitre l'état du parking.
{
    static struct sembuf reserverP = {PARKING_SEM, -1 ,0};
    // structure permettant d'effectué un P 
    static struct sembuf libererP = {PARKING_SEM, 1 ,0};
    // structure permettant d'effectué un V
    
    
    voiture.numeroEmplacement = place;
    
    // On effectue un P. sur le parking
    semop(semID, &reserverP, 1);
    
    // On insére la voiture dans la mémoire partagé.
    pakingLibre->voitures[place] = voiture;
    
    // On effectue un V. sur le parking
    semop(semID, &libererP, 1);
}
// Fin de ecrireVoiture


static void creationVoiturier (pid_t unVoiturier, Voiture voiture)
// Mode d'emploi:
//
// Procédure permettant d'initialiser la structure voiturier,
// ceci permet de faire le lien entre le voiturier et la voiture.
// La structure voiture est alors ajouté au vecteur
// vecteurTacheVoiturier apres son initialisation.
{
    // initialisation de la structure reliant le voiturier
    // avec la voiture.
    Voiturier * voiturier = (Voiturier *) malloc(sizeof(Voiturier));
    voiturier -> pidVoiturier = unVoiturier;
    voiturier -> voiture = voiture;
    
    // on ajoute le lien entre le voiturier et la voiture.
    vecteurTacheVoiturier.push_back (voiturier);
}
// Fin de creationVoiturier

static void destructionTache(int noSignal)
// Mode d'emploi:
//
// Procédure permettant de supprimer proprement l'ensemble des processus,
// associé à la tache (Processus lié à la methode garerVoiture())
// D'autre part la méthode de détache la tache des mémoires attaché
// permettant uen destruction propres de celle-ci.
{
    if(noSignal == SIGUSR2)
    {
        // On masque le signal SIGCHLD pour éviter que le voiturier 
        // puisse finir de garer la voiture et ainsi l'enlever du
        // vecteur alors que la fonctionne essai de supprimer
        // l'éléments concerné du vecteur
        masquerSignal(SIGCHLD);
        
        for( std::vector <Voiturier *>::iterator 
             it = vecteurTacheVoiturier.begin();
             it!= vecteurTacheVoiturier.end() ; it++)
        {
            // on arréte proprement les processus qui sont 
            // encore en marche.
            kill((*it )-> pidVoiturier,SIGUSR2);
            waitpid((*it)-> pidVoiturier,NULL,0);
            
        }
        // Détachement de la memoire partagé.
        shmdt(pakingLibre);
        shmdt(requetePartage);
        
        exit(0);
        
    }
}
// fin de destructionTache

static void finVoiturier (int noSignal)
// Mode d'emploi:
//
// Procédure permettant d'enlever la structure voiturier liant
// la voiture au voiturier du vecteur.
// La méthode supprime le contenu de la structure du voiturier qui 
// a fini son action et libérere la contenue du vecteur 
// vecteurTacheVoiturier
{
    if(noSignal == SIGCHLD)
    {
        Voiturier* voiturier;
        std::vector <Voiturier *>::iterator it; 
        it = vecteurTacheVoiturier.begin();
        int status;
        
        // On récupere le pid du fils qui envoie le signal. 
        pid_t unVoiturier = wait(&status);
        
        // on récupere le couple (voiturier, voiture) correspondant.
        for(; it!= vecteurTacheVoiturier.end() ; it++)
        {
            if((*it )-> pidVoiturier ==  unVoiturier )
            {
                voiturier = *it;
                break;
            }
        }
        
        // Permet l'affichage de l'état du parking dans l'interface 
        // graphique
        switch (voiturier->voiture.typeUsager)
        {
            case 'P' :
                AfficherPlace(
                              WEXITSTATUS(status),
                              PROF,
                              voiturier->voiture.numeroMineralogique,
                              voiturier->voiture.heureArrive
                              );
                break;
                
            case 'A' :
                AfficherPlace(
                              WEXITSTATUS(status),
                              AUTRE,
                              voiturier->voiture.numeroMineralogique,
                              voiturier->voiture.heureArrive
                              );
                break;
                
        }

        // écriture dans la mémoire partagé.
        ecrireVoiture (voiturier-> voiture, WEXITSTATUS(status));
        
        // Suppression du Voiturier
        free(*it);
        vecteurTacheVoiturier.erase(it);
        
    }
}
// Fin finVoiturier

static void initialisation (int identifiantFilesVoiture , 
                            int identifiantSemaphore    , 
                            int identifiantMemoirePark  , 
                            int  identifiantMemoireRequete )
// Mode d'emploi:
//
// Procédure permettant d'initialiser la tache barriereEntree correctement.
// - Initialisation des passifs 
// - Attachement aux mémoires partagés
// - Association des handlers associés aux signaux utiles.
{
    // On masque les signaux le temps d'initialiser l'application.
    masquerSignal(SIGUSR2);
    masquerSignal(SIGCHLD);

    // initilisation des passifs de l'applications
    fileID = identifiantFilesVoiture;
    semID = identifiantSemaphore;
    memID = identifiantMemoirePark;
    memIDRequete = identifiantMemoireRequete;
    
    // attachement à la mémoire partagé.
    pakingLibre = (MemParking*) shmat(memID, NULL, 0) ;
    requetePartage = (MemRequete*) shmat(memIDRequete, NULL, 0) ;
    Afficher(MESSAGE, LirePlace(pakingLibre,semID) );
    // description de l'handler associé à la destruction de la tache.
    
    struct sigaction action;
    action.sa_handler = destructionTache ;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0 ;
    
    
    // description de l'handler associé
    struct sigaction actionFinVoiturier;
    actionFinVoiturier.sa_handler = finVoiturier ;
    sigemptyset(&actionFinVoiturier.sa_mask);
    actionFinVoiturier.sa_flags = 0 ;
    
    
    // on  arme les signaux.
    sigaction(SIGCHLD,&actionFinVoiturier,NULL);  
    sigaction(SIGUSR2,&action,NULL);              
    
}

// Fin de initialisation

static void travailMoteur(TypeBarriere barriere)
// Mode d'emploi:
//
// Procédure permettant de simuler l'arrivé d'un seule voiture à la barriére. 
// Si le nombre de places le permet, la méthode gare la voiture. 
// Si le parking est plein alors la méthode attend un jeton de la tache 
// Sortie.
{
    static struct sembuf reserverB = {barriere, -1 ,0};				
    // structure permettant de récupere le jeton.

    Voiture voiture;  

    int status;
    // entier permettant de spécifier l'état de la lecture dans la boite 
    // aux lettres
    
    // On selectionne la boite aux lettres associé à la barriére
    // On receptionne une voiture des qu'il y en a un présente
    do {
        
        status = LireVoitureFileMessage(fileID,barriere,&voiture); 

        // exeption non gére.
        if(status == -1 && errno != EINTR)
        {
            destructionTache(0); 
        }
    } while (status == -1 );
    
    // Mise à jour de l'heure de départ.
    voiture.heureArrive = time(NULL);
    
    // On dessine la voiture dérriere la barriére.
    switch (voiture.typeUsager)
    {
        case 'P' :
            DessinerVoitureBarriere (barriere,PROF);
            break;
            
        case 'A' :
            DessinerVoitureBarriere (barriere,AUTRE);
            break;
    }
    
    // On Vérifie que le parking ne soit pas plein. 
    // Si ce dernier est plein alors nous attendons que la tache sortie
    // nous délivre un jeton.
    if (ReserverPlaceSiPossible(pakingLibre,semID) == 0)
    {
        // affichage des requetes.
        switch (voiture.typeUsager)
        {
            case 'P' :
                AfficherRequete(barriere, PROF, voiture.heureArrive);
                break;
                
            case 'A' :
                AfficherRequete(barriere,AUTRE, voiture.heureArrive);
                break;
        }
        
        
        // Ajout de la voiture dans la mémoire parté de la requete.
        Requete requete;
        requete.heureArrive  = voiture.heureArrive;
        requete.typeUsager = voiture.typeUsager;
        ecrireRequete (requete,barriere);
        
        // On endort le pocessus tant que la tache sortie ne nous délivre
        // pas de jeton.
        while (semop(semID, &reserverB, 1) == -1);	
        
         // On enlève la requête de la mémoire
         requete = {0, 'N'};
         ecrireRequete (requete,barriere);
    }
    
    
    
    // On fait appel à un voiturier.
    pid_t pidVoiturier = GarerVoiture(barriere);
    
    Afficher(MESSAGE,pakingLibre->nbPlace);

    // creation du lien entre le voiturier et la voiture.
    if (pidVoiturier != -1)
    {
        creationVoiturier (pidVoiturier,voiture);
    }
    
    // on attend que la voiture est passé la barriére avant de pouvoir
    // faire entrer un voiture
    sleep(TEMPORISATION); 
    
}
// fin de travail Moteur

//---------------------------------------------------- Fonctions publiques


// définition de la méthode GestionBarriere
void GestionBarriereEntre(int identifiantFilesVoiture   ,
                          TypeBarriere barriere         ,
                          int identifiantSemaphore      , 
                          int identifiantMemoirePark    ,
                          int  identifiantMemoireRequete )
{
    
    initialisation (identifiantFilesVoiture, identifiantSemaphore, identifiantMemoirePark, identifiantMemoireRequete );
    
    for (;;)
    {
        travailMoteur(barriere);
    }
    
}
// Fin de la méthode GestionBarriere.


