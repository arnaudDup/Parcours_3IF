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
#include "Segment.h"
#include "Vecteur.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques

bool Segment ::  Deplacer (double differenceX, double differenceY)
{
    bool verif = false;                         // variable permettant de
    if (this -> premierPoint.DeplacerPoint(differenceX,differenceY)&&
        this -> deuxiemePoint.DeplacerPoint(differenceX,differenceY))
    {
        verif = true;
    }
    return verif;
}
// fin de deplacer


// Ici on aurait tres bien pu retourner dans le package vue, mais la fonction nous est utile seulement
// pour vérifier que le programme fonctionne correctement.
void Segment:: Afficher (ostream & fichierSortie)
{
    fichierSortie <<" "<<IComposant::type << "egment ";
    premierPoint.afficherPoint(fichierSortie);
    fichierSortie<< ",";
    deuxiemePoint.afficherPoint(fichierSortie);
    fichierSortie << endl;
}
// Fin de afficherRectangle

bool Segment :: EstValide(std::vector<Point> ensembleDePoint)
{
    bool verif = true;
    // Nous testons que le nombre d'entrée est bien égale à deux
    if ( ensembleDePoint.size() != 2)
    {
        verif = false;
    }
    
    // A voir s'il faut faire des test sur les points...
    return verif;
}

bool Segment :: EstDedans (Point pointATraiter)
{
    bool verif = false;
    Vecteur VecteurA (premierPoint, pointATraiter);
    Vecteur VecteurB (deuxiemePoint, pointATraiter);
    Vecteur VecteurC (premierPoint, deuxiemePoint);
    
    double  longueurSegment = VecteurC.Norme();
    double  longueurIntermediaireA = VecteurA.Norme();
    double  longueurIntermediaire = VecteurB.Norme();
    
    double somme = longueurIntermediaireA + longueurIntermediaire;
    
    if (somme == longueurSegment)
    {
        verif = true; 
    }
    
    return verif;
}

string  Segment :: toWrite (string  nom)
{
    return "S "+ nom + " "+ premierPoint.toWrite() + " " + deuxiemePoint.toWrite();
}

IFigure* & Segment :: Copie ()
{
    IFigure * figure;
    std::vector<Point> ensembleDePoint;
    ensembleDePoint.push_back(this->premierPoint);
    ensembleDePoint.push_back(this->deuxiemePoint);
    figure = new Segment ("S",ensembleDePoint);
    return figure;
}


//------------------------------------------------- Surcharge d'opÈrat

//-------------------------------------------- Constructeurs - destructeur

Segment :: Segment (string unType, std::vector<Point> ensembleDePoint): premierPoint(ensembleDePoint[0]),deuxiemePoint (ensembleDePoint[1])
{
    IFigure::type = unType;
    
} //----- Fin de Rectangle



Segment :: ~Segment ()
{
    
} //----- Fin de ~Rectangle



//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
