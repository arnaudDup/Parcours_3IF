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
#include "Point.h"
#include <stdio.h>
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques
    bool Point :: DeplacerPoint(double differenceX,double differenceY)
    {
        this -> ordonne += differenceY;
        this -> abscisse += differenceX;
        //cout << "nouvelle ordonne" << abscisse << endl;
        return true;
    } //----- Fin de MÈthode

    // Ici on aurait tres bien pu retourner dans le package vue, mais la fonction nous est utile seulement
    // pour vérifier que le programme fonctionne correctement.
    void Point :: afficherPoint(ostream & fichierSortie ) const
    {
        fichierSortie << "[" <<  abscisse
             << " , " << this -> ordonne << "]" ;
    }

    string  Point :: toWrite ()
    {
        string a  = to_string(abscisse);
        string b = to_string(ordonne);
        string S = a + " " +b;
        return S ;
    }


//------------------------------------------------- Surcharge d'opÈrat

//-------------------------------------------- Constructeurs - destructeur

    Point :: Point (double uneAbscisse, double uneOrdonne)

    {
        this -> abscisse = uneAbscisse;
        this -> ordonne = uneOrdonne;

    } //----- Fin de Rectangle

    Point :: Point (const Point & pointACopier )
    {
        abscisse = pointACopier.abscisse;
        ordonne = pointACopier.ordonne; 
    }


    Point :: ~Point ()
    {
        
    } //----- Fin de ~Rectangle


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
