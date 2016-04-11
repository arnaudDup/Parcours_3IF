/*************************************************************************
GestionClavier  -  description
 -------------------
 début                : 15 mars 2016
 copyright            : (C) par Arnaud dupeyrat
 e-mail               : arnaud.dupeyrat@insa-lyon.fr
 *************************************************************************/

//---------- Réalisation du module <GestionClavier> (fichier GestionClavier.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <stdio.h>

//------------------------------------------------------ Include personnel
#include "GestionClavier.h"
#include "Config.h"
#include "Menu.h"
#include "IPC.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

static int filesVoitures;

//------------------------------------------------------ Fonctions privées

static unsigned int generationNumMineralogique()

// Mode d'emploi:
//
// Fonction permettant de générer un nombre entre [1,999]
// la nombre s'incrémente à chaque appel de la méthode.
//
{
    static unsigned int NumMineralogique = 0;
    NumMineralogique ++;
    if(NumMineralogique % 1000 == 0)
    {
        NumMineralogique = 1;
    }
    return NumMineralogique;
}
// fin GenerationNumMineralogique().

static Voiture * initilisationVoiture (char code)

// Mode d'emploi:
//
// attribut:
// < code > : valeur saisie par l'utilisateur.
//
// Fonction permettant la création d'un voiture, la valeur de retour est
// une voiture dont ses attributs sont initialisés.

{
    // création d'un nouvelle instance de voiture.
    Voiture * voiture = (Voiture*) malloc(sizeof(Voiture));
    
    // initialisation des valeurs.
    voiture -> typeUsager = code;
    voiture -> numeroEmplacement = -1;
    voiture -> heureArrive = -1;
    voiture -> heureDepart = -1;
    voiture -> numeroMineralogique = generationNumMineralogique();
    
    return voiture;
}

static void arriveeVoiture (char code,unsigned int valeur )

// Mode d'emploi:
//
// attribut:
// < code >   : valeur saisie par l'utilisateur, represente le type
//              d'usager
// < valeur > : représentant la porte par laquelle l'utilisateur veut
//              intéragir.
//
// Fonction permettant de simuler l'arrivée d'une nouvelle voiture.
//
{
    // on initilise la voiture qu'on transmet par une boite aux lettres
    Voiture * voiture = initilisationVoiture(code);
    
    // Permettant de choisir le boite aux lettres
    voiture -> type = valeur;
    
    EcrireFileMessage(filesVoitures, voiture, VOITURE);
    
    free(voiture);
   
}
// fin de ArriveeVoiture

static void departVoiture (char code, unsigned int valeur )

// Mode d'emploi:
//
// attribut:
// < code > : valeur saisie par l'utilisateur.
// < valeur > : représentant la place de la voiture qui quitte le parking.
//
// Fonction permettant de simuler le départ d'une nouvelle voiture.
// La méthode place une struct NumeroEmplacement dans la boite aux
// lettres associé à la tache de sortie.
//
// contrat: aucun
{
    // On initialise la structure emplacement pour le transmettre via 
    // la boite aux lettre. 
    NumeroEmplacement * numeroEmplacement ;
    numeroEmplacement = (NumeroEmplacement*) malloc(sizeof(NumeroEmplacement));
    
    // initailisation des valeurs.
    numeroEmplacement -> type = 4;
    numeroEmplacement -> numeroPlace = valeur;
    
    EcrireFileMessage(filesVoitures, numeroEmplacement, NUMERO_EMPLACEMENT);

    free(numeroEmplacement);
}
// Fin de departVoiture




//---------------------------------------------------- Fonctions publiques

// définition de la fonction commande
void Commande( char code, unsigned int valeur)
{
    // Nous traitons les différentes commandes possibles.
	switch(code)
    {
        case ('E') :
        case ('e') :
            exit(0);
        break;
        
        case ('P') :
        case ('p') : 
			switch (valeur)
			{
				case(1) :
            				arriveeVoiture(code, valeur);
				break; 
				case(2) :
            				arriveeVoiture(code, 3);
				break; 
			}
        break;

		case ('a') :
        case ('A') : 
            arriveeVoiture(code, valeur+1);
        break;

        case ('s') :
        case ('S') :
            departVoiture (code, valeur);
        break;

    }
    
}
// fin Commande( char code, unsigned int valeur).

// définition de la fonction GestionClavier
void GestionClavier(int identifiantFilesVoiture)
{
    
    // initialisation de l'identifiant de la boite aux lettres.
    filesVoitures = identifiantFilesVoiture;
    
    
    // Boucle Infini
    // Permetant de gérer les entrées clavier.
    for(;;)
    {
        Menu();
    }
    
}
// Fin de GestionClavier.



