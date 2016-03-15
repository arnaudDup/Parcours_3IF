/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/
#ifndef TP4Forme_Header_h
#define TP4Forme_Header_h

//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Rectangle:
//
// Interface permettant de définir le comportement d'une action.
//
//------------------------------------------------------------------------
#include <iostream>
#include "Point.h"
class IFigure
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    virtual bool Deplacer (double differenceX = 0, double differenceY = 0) = 0;
    // Attribut:
    // < differenceX > : Deplacement de la structure selon l'axe de ordonnées
    // < differenceY > : Deplacement de la structure selon l'axe
    
    // Mode d'emploi :
    // Permet de déplacer la classe selon un deplacement selon le déplacement
    // placé en paramétres.
    
    
    virtual void Afficher (std :: ostream & fichierSortie = std :: cout) = 0;
    // Attribut:
    // <fichierSortie> : permet de specifier l'objet sur lequel nous allons
    // rediriger le flux.
    
    // Mode d'emploi :
    // Permet d'afficher la figure traiter.
    
    virtual bool EstDedans (Point pointATraiter) = 0;
    
    // Attribut:
    // <pointATraiter> : permet de specifier le point que nous allons tester
    
    // Mode d'emploi :
    // Permet de tester si le point appartient à la figure traitée.
    // renvoie true si le point appartient a la figure.
    // renvoie false si le point n'appartient pas à la figure.
    
    virtual std::string toWrite (std::string nom = "") = 0;
    // Mode d'emploi :
    // Permet de codifié la façon d'externaliser chaque figures.
    
    inline std::string & getType()
    {
        return type;
    }
    // Mode d'emploi :
    // Permet de renvoyer le type de la figure traité.
    
    virtual IFigure* & Copie () = 0;
    // Mode d'emploi :
    // Permet de renvoyer une copie profonde de la copie tester.
    
    virtual ~IFigure (){};
    // desctruteur de la classe.
    
protected:
    std::string type;
    
    
};

//----------------------------------------- Types dÈpendants de Rectangle


#endif
