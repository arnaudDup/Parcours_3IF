/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

#ifndef __TP4Forme__ActionAjout__
#define __TP4Forme__ActionAjout__

#include <stdio.h>
#include "IAction.h"
#include "Controleur.h"
#include "Modele.h"
//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Rectangle:
//
//
//------------------------------------------------------------------------
class Point;
class ActionAjout : public IAction
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    virtual bool redo();
    // Mode d'emploi:
    
    virtual bool undo();
    // Mode d'emploi:
    
	virtual void disp() { cout << "Ajout : " << nom << endl; }
    //-------------------------------------------- Constructeurs - destructeur
    
    // constructeur de la classe.
    ActionAjout (string nom);
    
    // Destructeur de la classe.
    virtual ~ActionAjout();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
	string nom;
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle


#endif /* defined(__TP4Forme__ActionAjout__) */
