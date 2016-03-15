/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

#if ! defined ( Controleur_H )
#define Controleur_H

//--------------------------------------------------- Interfaces utilisÈes
#include <iostream>
#include "ParserEntre.h"
#include "Modele.h"
#include "IAction.h"
#include "Vue.h"
#include <deque>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Point:
//
// Permet d'implementer informatiquement un point.
//
//------------------------------------------------------------------------


class Controleur
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
public:
    static Controleur* & getInstance();
    // Mode d'emploi :
    // Permet de renvoyer l'unique instance constroleur du programme (design pattern singleton)
    
    inline  Modele * & getModele()
    {
        return modele;
    }
    // Mode d'emploi :
    // Permet d'obtenir une référence sur le modèle de notre programme.
    
    inline Vue * & getVue()
    {
        return vue ;
    }
    // Mode d'emploi :
    // Permet d'obtenir une référence sur la vue de notre programme.
    
    bool undo();
    // Mode d'emploi :
    // Permet d'effectuer un UNDO, c'est à dire annuler la derniere action effectué.
    
    bool redo();
    // Mode d'emploi :
    // Permet d'effectuer un REDO, c'est à dire effectuer l'action annuler auparavant.
    
    void afficherActions();
    // Mode d'emploi :
    // Permet l'affichage des actions présentes dans le modéle.
    
    void AjouterAction(IAction* & action);
    // attribut:
    // < action > Action que l'on souhaite ajouter.
    
    // Mode d'emploi :
    // Permet d'ajouter l' < action > à l'ensemble des actions effectué lors du deroulement de notre programme.
    
    void DebuterLecture();
    // Mode d'emploi :
    // Permet de débuter la lecture des entrées, début du parseur.
    

    //-------------------------------------------- Constructeurs - destructeur
    
    // Destructeur de la classe.
    virtual ~Controleur ();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
    
    Controleur();                           // Constructeur de la classe.
    Modele * modele;                        // Référence au modele.
    Vue * vue;                              // Référence à la vue.
    static Controleur * uniqueInstance;     // Référence unique du controleur.
    int currentAction;                      // indice de l'action courante
    ParserEntre *parser;                    // référence sur le parseur d'entrée
    deque <IAction*> actions;               // Vecteur référençant les actions ajoutées au controleur.
    
    
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle

// initialisation de la variable static. 




#endif // CONTROLEUR_H
