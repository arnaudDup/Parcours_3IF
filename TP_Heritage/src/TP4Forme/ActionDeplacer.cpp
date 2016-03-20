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
#include "ActionDeplacer.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques

bool ActionDeplacer :: redo()
{
    Modele *modele = Controleur::getInstance()->getModele();
    modele->Deplacer(nom,dx,dy);
    return true;
}
bool ActionDeplacer ::  undo()
{
    
    Modele * modele = Controleur::getInstance()->getModele();
    double negatifdx = -dx;
    double negatifdy = -dy;
    modele->Deplacer(nom,negatifdx,negatifdy);
    return true;
}



//-------------------------------------------- Constructeurs - destructeur


ActionDeplacer:: ActionDeplacer (string unNom, double unDx,double unDy): nom (unNom)
{
 
    dx = unDx;
    dy = unDy;
}





ActionDeplacer:: ~ActionDeplacer()
{
    
}


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
