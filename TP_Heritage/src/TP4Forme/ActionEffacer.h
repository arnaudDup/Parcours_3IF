/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

#ifndef __TP4Forme__ActionEffacer__
#define __TP4Forme__ActionEffacer__

#include <stdio.h>
#include "IAction.h"
#include "Controleur.h"
#include "Modele.h"
//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// 
//
//
//------------------------------------------------------------------------
class Point;
class ActionEffacer : public IAction
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    virtual bool redo();
    // Mode d'emploi:
    // Permet d'effectuer l'action précedement annulé.
    
    virtual bool undo();
    // Mode d'emploi:
    // Permet d'annuler l'action effectué.
    
    virtual void disp();
    // Mode d'emploi:
    // Permet l'affichage de l'action courante.
    //-------------------------------------------- Constructeurs - destructeur
    
    // constructeur de la classe.
    ActionEffacer (vector<string> & noms);
    
    // Destructeur de la classe.
    virtual ~ActionEffacer();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
   vector <string> noms;
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle


#endif /* defined(__TP4Forme__ActionEffacer__) */
