/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

//---------- Interface IAction ------

#ifndef IACTION_H
#define IACTION_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe IAction
// Service qu'une action doit rendre.
//
//------------------------------------------------------------------------

class Figure;
class IAction
{
    public:
        virtual bool redo() = 0;
        // Mode d'emploi:
        // Permet de reffectuer l'action précedement annulé

        virtual bool undo() = 0;
        // Mode d'emploi:
        // Permet d'annuler l'action.
    

		virtual void disp() = 0;
        // Mode d'emploi:
        // affiche l'action.
    
        virtual ~IAction(){};
        // destructeur de la classe. 
    
    private:
       
};


#endif // IACTION_H

