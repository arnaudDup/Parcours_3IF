/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/
#ifndef __TP4Forme__Vecteur__
#define __TP4Forme__Vecteur__

#include "Point.h"
#include <vector>
//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Rectangle:
//
// Permet d'implementer informatiquement une figure decrivant un rectangle
// Cette Classe contient comme attribut le point en haut a gauche puis en bas
// gauche.
//
//------------------------------------------------------------------------


class Vecteur
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques

    double Norme();
    double Angle (Vecteur & vecteurATester);
    // permet de donner l'angle interne avec 2 vecteurs. 
    
    //-------------------------------------------- Constructeurs - destructeur
    
    // constructeur de la classe.
    Vecteur (Point & a, Point & b);
    
    // Destructeur de la classe.
    virtual ~Vecteur ();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
    
    double   abscisse;       // Point en haut à gauche du rectangle
    double ordonne;         // Point en bas à droite du rectangle
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle

int Sign (double nombre);

#endif /* defined(__TP4Forme__Vecteur__) */
