/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

#ifndef TP4Forme_Composant_h
#define TP4Forme_Composant_h

#include "Ifigure.h"
#include "Point.h"
//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Rectangle:
//
// Interface permettant de définir le role des composant unique de notre application.
// L'interface permet de codifier les actions necessaire d'une figure.
//
//------------------------------------------------------------------------

class IComposant : public IFigure
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    virtual bool Deplacer (double differenceX, double differenceY) = 0;
    // Attribut:
    // < differenceX > : Deplacement de la structure selon l'axe de ordonnées
    // < differenceY > : Deplacement de la structure selon l'axe
    
    // Mode d'emploi :
    // Permet de déplacer la classe selon un deplacement selon le déplacement
    // placé en paramétres.
    
    virtual void Afficher(std::ostream & fichierSortie = std::cout)  = 0;
    // Attribut:
    
    // Mode d'emploi :
    // Permet d'afficher la figure traiter.
    
    virtual bool EstDedans (Point pointATraiter) = 0;
    
    // Attribut:
    // <pointATraiter> : permet de specifier le point que nous allons tester
    
    // Mode d'emploi :
    // Permet de tester si le point appartient à la figure traitée.
    // renvoie true si le point appartient a la figure.
    // renvoie false si le point n'appartient pas à la figure.
    
    virtual std::string toWrite (std::string  nom = "") = 0;
    // Mode d'emploi :
    // Permet de codifié la façon d'externaliser chaque figures.
    
    virtual IFigure* & Copie () = 0;
    // Mode d'emploi :
    // Permet de renvoyer une copie profonde de la copie tester.

    virtual ~IComposant(){};
    
protected:
    
};

//----------------------------------------- Types dÈpendants de Rectangle

#endif
