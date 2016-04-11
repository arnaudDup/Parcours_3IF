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

//---------- Interface de la tâche <SORTIE> (fichier SORTIE.h) -------
#if ! defined ( SORTIE_H )
#define SORTIE_H

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Sortie (int FileID, int memShare, int memRqID, int semid);
// Mode d'emploi : Cette fonction correspond à la gestion de la barriere de sortie.
// Elle lance la phase d'initialisation puis la phase moteur. (voir fonction privées)

#endif // SORTIE_H

