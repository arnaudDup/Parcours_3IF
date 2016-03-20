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
#include "Vecteur.h"
#include <cmath>

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques

double  Vecteur ::  Norme ()
{
    double longueur = 0 ;
    
    // Nous calculons la norme du vecteur associé.
    longueur = sqrt(abscisse*abscisse + ordonne*ordonne);
    return longueur;
}


double Vecteur :: Angle (Vecteur & vecteurATester)
{
    
    double Na = Norme();
    double Nb = vecteurATester.Norme();
    
    double C = (abscisse*vecteurATester.abscisse +ordonne*vecteurATester.ordonne)/(Na*Nb);
    double S = (abscisse*vecteurATester.ordonne-ordonne*vecteurATester.abscisse);
    double angle = Sign(S)*acos(C);
    
    // conversion en degres
    angle = 180 + (angle*180) / M_PI;
    return angle;
    
}
// fin de deplacer



//------------------------------------------------- Surcharge d'opÈrat

//-------------------------------------------- Constructeurs - destructeur

Vecteur :: Vecteur (Point & a , Point & b)
{
    abscisse = b.getAbscisse() - a.getAbscisse();
    ordonne = b.getOrdonne() - a.getOrdonne();
    
} //----- Fin de Rectangle



Vecteur :: ~Vecteur ()
{
    
} //----- Fin de ~Rectangle



//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes


int Sign (double nombre)
{
    if (nombre < 0)
    {
        return -1;
    }
    if (nombre > 0)
    {
        return 1;
    }
    return 0;
}
