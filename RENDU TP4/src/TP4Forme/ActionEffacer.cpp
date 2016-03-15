/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

//---------- RÈalisation de la classe <${file_base}> (fichier ${file_name}) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systËme
#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include <string>
#include "ActionEffacer.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques

bool ActionEffacer :: redo()
{
    
    Modele *modele = Controleur::getInstance()->getModele();
    modele->SupprimerFigures(noms);
    return true;
}
bool ActionEffacer ::  undo()
{
    
    Modele *modele = Controleur::getInstance()->getModele();
    modele->RestaurerFigures(noms);
    return true;
}

void ActionEffacer :: disp()
{   cout << "Effacer { ";
    vector <string> :: iterator it = noms.begin();
    for ( ;it != noms.end(); it++)
    {
        cout << *(it) << ",";
    }
    cout << "}" << endl;
}

//-------------------------------------------- Constructeurs - destructeur


ActionEffacer:: ActionEffacer (vector <string> & noms)
{
    this->noms = noms;
}


ActionEffacer:: ~ActionEffacer()
{
    
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
