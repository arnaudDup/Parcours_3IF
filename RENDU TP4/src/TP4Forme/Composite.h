/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

#ifndef __TP4Forme__Composite__
#define __TP4Forme__Composite__

#include "IFigure.h"
#include "IComposant.h"
#include <set>
#include <iostream>
#include <vector>
//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Point:
//
// Permet d'implementer informatiquement un point.
//
//------------------------------------------------------------------------

class Composite : public IFigure
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    virtual bool Deplacer(double differenceX,double differenceY);
    // Attribut:
    // < differenceX > : Deplacement du point selon l'axe de ordonnées
    // < differenceY > : Deplacement du point selon l'axe
    
    // Mode d'emploi :
    // Permet de déplacer le point selon un deplacement selon le déplacement
    // placé en paramétres.
    
    virtual void Afficher( std::ostream & fichierSortie = std :: cout);
    // Attribut:
    
    // Mode d'emploi :
    // Permet d'afficher le point selon la forme:
    
    virtual bool EstDedans (Point pointATraiter);
    
    // Attribut:
    // <pointATraiter> : permet de specifier le point que nous allons tester
    
    // Mode d'emploi :
    // Permet de tester si le point appartient à la figure traitée.
    // renvoie true si le point appartient a la figure.
    // renvoie false si le point n'appartient pas à la figure.
    
    std::string toWrite (std::string nom = "");
    // Mode d'emploi :
    // Permet de restituer la commande, à partir de la figure.
    
    virtual IFigure* & Copie ();
    // Mode d'emploi :
    // Permet de renvoyer une copie profonde de la copie tester.
    
    
    //-------------------------------------------- Constructeurs - destructeur
    
    // constructeur de la classe.
    Composite (std::string unType,bool intersection, std::vector <IFigure*> ensembleFigure);
    
    // constructeur par defaut
    Composite ();
    
    // Destructeur de la classe.
    virtual ~ Composite ();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    bool VerificationIntersection(Point pointAtraiter);
    bool VerificationReunion(Point pointAtraiter);
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
    
    // oblige de mettre des pointeurs sinon ça le prend pas mais utilise car directement pris des pointeurs
    // Figure du controleur.
    std :: set <IFigure*> composants;
    bool intersection; // permet de spécifier que le composite est la renion des figures ou l'intersections de ces dernieres.
    
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle


#endif /* defined(__TP4Forme__Composite__) */
