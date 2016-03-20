/*************************************************************************
 -------------------
 début                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;
#include<string>

//------------------------------------------------------ Include personnel
#include "Rectangle.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques

bool Rectangle ::  Deplacer (double  differenceX, double differenceY)
{
    bool verif = false;                         // variable permettant de
    if (this -> deuxiemepoint.DeplacerPoint(differenceX,differenceY)&&
        this -> premierpoint.DeplacerPoint(differenceX,differenceY))
    {
        verif = true;
    }
    return verif;
}
// fin de deplacer


// Ici on aurait tres bien pu retourner dans le package vue, mais la fonction nous est utile seulement
// pour vŽrifier que le programme fonctionne correctement.
void Rectangle:: Afficher (ostream & fichierSortie) 
{
    fichierSortie <<" "<<IComposant::type << "ectangle ";
    premierpoint.afficherPoint(fichierSortie);
    fichierSortie<< ",";
    deuxiemepoint.afficherPoint(fichierSortie);
    fichierSortie << endl;
}
// Fin de afficherRectangle


bool Rectangle :: EstDedans (Point pointATraiter)
{
    bool verif = false;
    
    // pour rŽsoudre ce probleme, on trace les lignes entourant le rectangle que nous devons traiter
    
    // PremiŽrement les lignes horizontale.
    if ((pointATraiter.getAbscisse()  >=  this->premierpoint.getAbscisse()  &&
         pointATraiter.getAbscisse()  <=  this->deuxiemepoint.getAbscisse())||
         (pointATraiter.getAbscisse() >=  this->deuxiemepoint.getAbscisse() &&
         pointATraiter.getAbscisse()  <=  this->premierpoint.getAbscisse()))
    {
        // deuxiement les lignes horizontale.
        if ((pointATraiter.getOrdonne() <=  this->premierpoint.getOrdonne()   &&
            pointATraiter.getOrdonne()  >=  this->deuxiemepoint.getOrdonne())  ||
            (pointATraiter.getOrdonne() <=  this->deuxiemepoint.getOrdonne() &&
             pointATraiter.getOrdonne() >=  this->premierpoint.getOrdonne()))
        {
            verif = true;
        }

    }
    
    return verif;
}

string  Rectangle :: toWrite (string nom)
{
    return "R "+ nom + " "+ premierpoint.toWrite() + " " + deuxiemepoint.toWrite();
}


IFigure* & Rectangle :: Copie ()
{
    IFigure * figure;
    std::vector<Point> ensembleDePoint;
    ensembleDePoint.push_back(this->premierpoint);
    ensembleDePoint.push_back(this->deuxiemepoint);
    figure = new Rectangle ("R",ensembleDePoint);
    return figure;
}

//------------------------------------------------- Surcharge d'opérat

//-------------------------------------------- Constructeurs - destructeur

Rectangle :: Rectangle (string unType, std::vector<Point> ensembleDePoint): deuxiemepoint(ensembleDePoint[0]),premierpoint (ensembleDePoint[1])
    {
        IFigure::type = unType;

    } //----- Fin de Rectangle

    
    
    Rectangle :: ~Rectangle ()
    {

    } //----- Fin de ~Rectangle


    
    //------------------------------------------------------------------ PRIVE
    
    //----------------------------------------------------- Méthodes protégées
    
    //------------------------------------------------------- Méthodes privées
