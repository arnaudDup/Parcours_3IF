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
#include "ActionAjout.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques

bool ActionAjout :: redo()
{
    Modele *modele = Controleur::getInstance()->getModele();
	modele->RestaurerFigure(nom);
    
    
    return true; 
}
bool ActionAjout ::  undo()
{
	
    Modele *modele = Controleur::getInstance()->getModele();
    modele->SupprimerFigure(nom);
    return true;
}



//-------------------------------------------- Constructeurs - destructeur
    
    
    ActionAjout:: ActionAjout (string nom)
    {
		this->nom = nom;
    }





    ActionAjout:: ~ActionAjout()
    {

    }
    
    
    //------------------------------------------------------------------ PRIVE
    
    //----------------------------------------------------- MÈthodes protÈgÈes
    
    //------------------------------------------------------- MÈthodes privÈes
