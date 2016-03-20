/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

#ifndef __TP4Forme__ActionDeplacer__
#define __TP4Forme__ActionDeplacer__

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
class ActionDeplacer : public IAction
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    virtual bool redo();
    // Mode d'emploi:
    
    virtual bool undo();
    // Mode d'emploi:
    
    virtual void disp() { cout << "deplacer :" << nom << " difference x "<< dx << " difference y "<< dy << endl; }
    //-------------------------------------------- Constructeurs - destructeur
    
    // constructeur de la classe.
    ActionDeplacer (string nom, double dx, double dy);
    
    // Destructeur de la classe.
    virtual ~ActionDeplacer();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
    int dx;
    int dy;
    string nom;
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle



#endif /* defined(__TP4Forme__ActionDeplacer__) */
