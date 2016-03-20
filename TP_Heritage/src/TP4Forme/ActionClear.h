/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

#ifndef __TP4Forme__ActionClear__
#define __TP4Forme__ActionClear__


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
class ActionClear : public IAction
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    virtual bool redo();
    // Mode d'emploi:
    
    virtual bool undo();
    // Mode d'emploi:
    
    virtual void disp() { cout << "Clear :" << endl; }
    //-------------------------------------------- Constructeurs - destructeur
    
    // constructeur de la classe.
    ActionClear ();
    
    // Destructeur de la classe.
    virtual ~ActionClear ();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle


#endif /* defined(__TP4Forme__ActionClear__) */
