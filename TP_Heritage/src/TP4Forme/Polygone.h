/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/
#ifndef __TP4Forme__Polygone__
#define __TP4Forme__Polygone__

#include "Point.h"
#include "IComposant.h"
#include <vector>
//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Polygone:
//
// Permet d'implementer informatiquement une figure decrivant un rectangle
// Cette Classe contient comme attribut le point en haut a gauche puis en bas
// gauche.
//
//------------------------------------------------------------------------


class Polygone : public IComposant
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    
    
    virtual bool Deplacer (double differenceX = 0, double differenceY = 0);
    // Attribut:
    // < differenceX > : Deplacement de la structure selon l'axe de ordonnées
    // < differenceY > : Deplacement de la structure selon l'axe
    
    // Mode d'emploi :
    // Permet de déplacer la classe selon un deplacement selon le déplacement
    // placé en paramétres.
    
    
    virtual void Afficher (std::ostream & fichierSortie = std::cout);
    // Attribut:
    // < fichierSortie> Permet de rediriger le flus de sortie.
    
    // Mode d'emploi :
    // Permet d'afficher les coordonnées du rectangle trantés.
    
    
    virtual bool EstDedans (Point pointATraiter);
    
    // Attribut:
    // <pointATraiter> : permet de specifier le point que nous allons tester
    
    // Mode d'emploi :
    // Permet de tester si le point appartient à la figure traitée.
    // renvoie true si le point appartient a la figure.
    // renvoie false si le point n'appartient pas à la figure.
    
    virtual IFigure* & Copie ();
    // Mode d'emploi :
    // Permet de renvoyer une copie profonde de la copie tester.
    
    string  toWrite (string nom = "");
    // Mode d'emploi :
    // Permet de restituer la commande, à partir de la figure.
    
    //-------------------------------------------- Constructeurs - destructeur
    
    // constructeur de la classe.
    Polygone (std::string unType,std::vector<Point> ensembleDePoint);
    
    // Attribut:
    // < nom > : nom du rectangle.
    // < tabPoint > : Tableau contenant deuxx points permett de spécifier entiérement les caractéristique
    // d'un rectangle.
    // Le premier point inséré est el coin supérieur.
    // le deuxiéme point inséré est le coin inférieur gauche.
    // < longueur > : Permet de spécifier la longueur du tableau.
    
    // Destructeur de la classe.
    virtual ~Polygone ();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
    
    vector <Point> ensembleDePoint;
    std::string nom;
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle

#endif /* defined(__TP4Forme__Polygone__) */
