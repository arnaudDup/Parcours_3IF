/*************************************************************************
 CONFIG  -  description
 -------------------
 début                : 15 MARS 2016
 copyright            : (C) par Antoine Breton et Arnaud Dupeyrat 
 e-mail               : arnaud.dupeyrat@insa-lyon.fr et antoine.breton@insa-lyon.fr
 *************************************************************************/

//---------- Interface de la tâche <CONFIG> (fichier CONFIG.h) -------
#if ! defined ( CONFIG_H )
#define CONFIG_H

//------------------------------------------------------------------------
// Rôle de la tâche CONFIG
//
// Définir les structure et constantes partagées par l'ensemble du programme.
// 
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <time.h>

//------------------------------------------------------------- Constantes

enum typeMsg {VOITURE, NUMERO_EMPLACEMENT};

const int NB_PLACE_SEM=5;
// Constante désignant le sémaphore élémetaire permettant d'acceder à la mémoire partagé 
// contenant les place de parking 

const int REQ_SEM=6;
// Constante désignant le sémaphore élémetaire permettant d'acceder à la mémoire partagé 
// contenant les requétes

const int PARKING_SEM = 7;
// Constante désignant le sémaphore élémetaire permettant d'acceder à la mémoire partagé 
// contenant le contenu du parking.

const int NB_SEM_ELEM = 4;
// Constante permettant de définir le nombre de sémaphore dans le sémaphore générale. 

enum cleSecondaire{CLE_SEM, CLE_MEM_NB_PLACE, CLE_MEM_REQUETE, CLE_MEM_PARKING}; 
// Utilisé pour générer les clefs


const unsigned int NBPLACE = 8;
// Constante permettant de définir le nombre de places disponibles dans le parking 

const unsigned int TEMPORISATION = 1; 
// Constante permettant de définit le temps d'attente à la porte 


const int DROITS = 0660;
// Constante définissant les droits d'accées.


#define chemin "./"
// Constante permettant de définir le chemin pour la création de passifs

//------------------------------------------------------------------ Types

// Structure représentant une voiture, La voiture est échanger entre les différentes taches
// à l'aide de boite aux lettres et de mémoire partagé. 
typedef struct Voiture
{
    long type;
    char typeUsager;
    unsigned int numeroMineralogique;
    time_t heureArrive;
    time_t heureDepart;
    unsigned int numeroEmplacement;
    
} Voiture;

// Structure permettant de simuler la sortie d'une voiture.
// La structure est échangé entre la barriereSortie et la gestionClavier, permettant 
// de faire sortir la voiture à la place voulu.
typedef struct NumeroEmplacement
{
    long type;
    unsigned int numeroPlace;
}NumeroEmplacement;

// Structure permettant faire un lien entre un voiturier et la voiture qu'il gare.
typedef struct Voiturier
{
    pid_t pidVoiturier;
    Voiture voiture;
}Voiturier;

// Structure permettant de définir les requetes échangé entre la barriereEntree et 
// la barriereSortie,  .
typedef struct Requete
{
    time_t heureArrive;
    char typeUsager;  
}Requete;

// Structure contenue dans la mémoire partagé des requétes, 
// La structure permet de rassembler les futurs requetes des 3 barrieres. 
typedef struct MemRequete
{
    Requete requetes[4];
}MemRequete;

// Structure contenue dans la mémoire partagé du parking, 
// La structure permet de rassembler: 
// - Le nombre de places disponible.
// - Le contenue dub parking. 
typedef struct MemParking
{
	int nbPlace;
	Voiture voitures[8];
}MemParking;




#endif // CONFIG_H
