/*************************************************************************
 -------------------
 d�but                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

#if ! defined ( Rectangle_H )
#define Rectangle_H

#include "Point.h"
#include "IComposant.h"
#include <vector>
//--------------------------------------------------- Interfaces utilis�es

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe Rectangle:
//
// Permet d'implementer informatiquement une figure decrivant un rectangle
// Cette Classe contient comme attribut le point en haut a gauche puis en bas
// gauche.
//
//------------------------------------------------------------------------ 


class Rectangle : public IComposant
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    
    
    
    virtual bool Deplacer (double differenceX = 0, double differenceY = 0);
    // Attribut:
    // < differenceX > : Deplacement de la structure selon l'axe de ordonn�es
    // < differenceY > : Deplacement de la structure selon l'axe
    
    // Mode d'emploi :
    // Permet de d�placer la classe selon un deplacement selon le d�placement
    // plac� en param�tres.
    
    
    virtual void Afficher (std::ostream & fichierSortie = std::cout);
    // Attribut:
    // < fichierSortie> Permet de rediriger le flus de sortie. 
    
    // Mode d'emploi :
    // Permet d'afficher les coordonn�es du rectangle trant�s.
    
    
    virtual bool EstDedans (Point pointATraiter);
    
    // Attribut:
    // <pointATraiter> : permet de specifier le point que nous allons tester
    
    // Mode d'emploi :
    // Permet de tester si le point appartient � la figure trait�e.
    // renvoie true si le point appartient a la figure.
    // renvoie false si le point n'appartient pas � la figure.
    
    
    virtual IFigure*  & Copie ();
    // Mode d'emploi :
    // Permet de renvoyer une copie profonde de la copie tester.
    
    std::string toWrite (std::string nom = "");
    // Mode d'emploi :
    // Permet de restituer la commande, � partir de la figure.

//-------------------------------------------- Constructeurs - destructeur

    // constructeur de la classe.
    Rectangle (std::string nom, std::vector<Point> ensembleDePoint);
    
    // Attribut:
    // < nom > : nom du rectangle.
    // < tabPoint > : Tableau contenant deuxx points permett de sp�cifier enti�rement les caract�ristique
    // d'un rectangle.
    // Le premier point ins�r� est el coin sup�rieur.
    // le deuxi�me point ins�r� est le coin inf�rieur gauche.
    // < longueur > : Permet de sp�cifier la longueur du tableau.

    // Destructeur de la classe.
    

    
    virtual ~Rectangle ();

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

private:
//------------------------------------------------------- M�thodes priv�es
   

protected:
//----------------------------------------------------- Attributs prot�g�s

private:
//------------------------------------------------------- Attributs priv�s
    
    Point premierpoint;       // Point en haut � gauche du rectangle
    Point deuxiemepoint;        // Point en bas � droite du rectangle
    std::string nom;
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes priv�es

//----------------------------------------------------------- Types priv�s

};

//----------------------------------------- Types d�pendants de Rectangle

#endif // Rectangle_H
