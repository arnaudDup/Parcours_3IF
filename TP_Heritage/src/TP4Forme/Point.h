/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/
#ifndef __TP4Forme__Point__
#define __TP4Forme__Point__

//--------------------------------------------------- Interfaces utilisÈes
#include <iostream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Point:
//
// Permet d'implementer informatiquement un point.
//
//------------------------------------------------------------------------


class Point
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques

    bool DeplacerPoint(double differenceX,double differenceY);
    // Attribut:
    // < differenceX > : Deplacement du point selon l'axe de ordonnées
    // < differenceY > : Deplacement du point selon l'axe
    
    // Mode d'emploi :
    // Permet de déplacer le point selon un deplacement selon le déplacement
    // placé en paramétres.
    
    void afficherPoint( std::ostream & fichierSortie = std::cout) const;
    // Attribut:
    
    // Mode d'emploi :
    // Permet d'afficher le point selon la forme:
    //
    
    inline double getAbscisse()
    {
        return abscisse;
    }
    
    inline double getOrdonne()
    {
        return ordonne; 
    }
    
    std::string toWrite ();
    //-------------------------------------------- Constructeurs - destructeur
    
    // constructeur de la classe.
    Point(double abscisse, double ordonne);
    
    Point (const Point & pointACopier);
    // Destructeur de la classe.
    virtual ~Point ();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
    
    double abscisse;       // Abscisse du point
    double ordonne;        // Ordonne du point
    
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle

#endif /* defined(__TP4Forme__Point__) */
