/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systËme
#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include <string>
#include "ActionClear.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques


bool ActionClear:: redo()
{
    Modele *modele = Controleur::getInstance()->getModele();
    modele->Clear();
    return true;
}
bool ActionClear ::  undo()
{
    
    Modele * modele = Controleur::getInstance()->getModele();
    modele->RedoClear();
    return true;
}



//-------------------------------------------- Constructeurs - destructeur


ActionClear :: ActionClear ()
{

}


ActionClear :: ~ActionClear()
{
    
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes