/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/
#ifndef __TP4Forme__Modele__
#define __TP4Forme__Modele__

#include <iostream>
#include <map>
#include <deque>
#include <vector>
#include "IFigure.h"
#include <fstream>
#include <vector>
//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Rectangle:
//
//------------------------------------------------------------------------



class Point;
class Modele
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    void SupprimerTousLeModele();
    // Mode d'emploi :
    // Permet de supprimer entiérement les figures qui composent notre modéliser.
    
    bool CreerRectangle (const std :: string nom,std::vector<Point> & ensembleDePoint);
    // Attribut:
    // < nom > : Nom associeé à la figure.
    // < ensembleDePoint > : Ensemble de Point servant à la création du Segment.
    
    // Mode d'emploi :
    // Permet la création d'un rectangle, composé de l' < ensembleDePoint > portant le < nom >
    // La méthode renvoie true si et seulement si et suelement si l'insertion est correctement effectué. c'est a dire que l' < ensembleDePoint >
    // satisfait les conditions de création d'un rectangle.
    
    bool CreerPolygone (const std :: string nom, std::vector<Point> & ensembleDePoint);
    // Attribut:
    // < nom > : Nom associeé à la figure.
    // < ensembleDePoint > : Ensemble de Point servant à la création du Polygone.
    
    // Mode d'emploi :
    // Permet la création d'un Polygone, composé de l' < ensembleDePoint > portant le < nom >
    // La méthode renvoie true si et seulement si et suelement si l'insertion est correctement effectué. c'est a dire que l' < ensembleDePoint >
    // satisfait les conditions de création d'un Polygone.
    
    bool CreerSegment (const std :: string nom,std::vector<Point> & ensembleDePoint);
    // Attribut:
    // < nom > : Nom associeé à la figure.
    // < ensembleDePoint > : Ensemble de Point servant à la création du Segment.
    
    // Mode d'emploi :
    // Permet la création d'un Segment, composé de l' < ensembleDePoint > portant le < nom >
    // La méthode renvoie true si et seulement si et suelement si l'insertion est correctement effectué. c'est a dire que l' < ensembleDePoint >
    // satisfait les conditions de création d'un segment.
    
    
    std::vector<IFigure*>& RechercheParNom(std::vector<std::string> & ensembleDePoint,std::vector<IFigure*> & vectorDeFigures);
    // Attribut:
    // < ensembleDePoint > : booléen permetant de spécifier si c'est une intersection ou une réunion.
    // < vectorDeFigures > : Nom associeé à la figure.
    
    // Mode d'emploi :
    // Permet de renvoyer un vecteur de figures à partir d'un vecteur de point.
    // si les figures ne sont actuellement pas présentes dans le modéle alors celle-ci ne sont pas ajouter au vecteur de figures

    bool CreerComposite (bool intersection,const std :: string nom, std::vector<std::string> & ensembleDePoint);
    // Attribut:
    // < intersection > : booléen permetant de spécifier si c'est une intersection ou une réunion.
    // < nom > : Nom associeé à la figure.
    // < ensembleDeFigures > : Ensemble de figure servant à la création du composite.
    
    // Mode d'emploi :
    // Permet la création d'un composite, composé de l'< ensembleDeFigures > portant le < nom > et spécifie à travers < intersection > si nous
    // traitons une intersection ou une réunion.
    // d'autre part lors de la
    // La méthode renvoie true si et seulement si et suelement si l'insertion est correctement effectué.
    
    IFigure * RetrouverFigure(const std :: string nom);
    // Attribut:
    // < nom > : Noms des figure à retrouver
    
    // Mode d'emploi :
    // Permet à partir du noms de tester si les figures sont réélement presentes dans le modéle.
    // la methode renvoie true si la totalite des noms référence des figures présentes.
    
    bool SupprimerFigure(const std :: string nom);
    // Attribut:
    // < nom > : Nom de la figure à supprimer
    
    // Mode d'emploi :
    // Permet à partir du noms de supprimer la figure du modéle
    // La méthode renvoie true si le suppresion s'est faite de maniére correcte
    
    bool TestSuppression (std::vector<std::string> & noms);
    // Attribut:
    // < noms > : Noms des figures que la méthodes doit tester
    
    // Mode d'emploi :
    // Permet à partir du noms de tester si les figures sont réélement presentes dans le modéle.
    // la methode renvoie true si la totalite des noms référence des figures présentes.

    bool SupprimerFigures(std::vector<std::string> & noms);
    // Attribut:
    // < nom > : Noms des figures à supprimer
    
    // Mode d'emploi :
    // Permet à partir du nom de suprimer la figure.
    // la methode renvoie true si la suppression s'est faites de manière correcte dans le cas contraire la valeur retourné est false.
    
    bool Deplacer(const std :: string nom, int dx, int dy);
    // Attribut:
    // < nom > : Nom de la figure à restaurer
    // < dx > : Déplacement selon les abscisses
    // < dy > : Déplacement selon les ordonnées
    
    // Mode d'emploi :
    // Permet à partir du nom de déplacer la figure selon < dx > et < dy > .
    
    bool RestaurerFigures(std::vector<std::string> & noms);
    // Attribut:
    // < nom > : Noms des figures à restaurer
    
    // Mode d'emploi :
    // Permet à partir du nom de restaurer la figure.
    // la methode renvoie true si la restauration s'est faites de manière correcte dans le cas contraire la valeur retourné est false.
    
    bool RestaurerFigure(const std :: string nom);
    // Attribut:
    // < nom > : Nom de la figure à restaurer
    
    // Mode d'emploi :
    // Permet à partir du nom de restaurer dans le modele, une figures qui a été supprimer.
    // la methode renvoie true si la restauration s'est faites de manière correcte dans le cas contraire la valeur retourné est false.
    
    bool EstDedans(Point pointATraiter, std::string nom);
    // Attribut:
    // < pointAtraiter > : Point surlequel porte les tests d'appartenance
    // < nom > : Nom de la figure surlaquelle porte les tests d'appartenance
    
    // Mode d'emploi :
    // Permet de renvoyer true si le point testé sur trouve dans la figure traité.
    
    bool ValidePolygone (std::vector<Point> & ensembleDePoint);
    // Attribut:
    // < ensembleDePoint > : Vecteur contenant les points nécessaire à la creation du composant.
    
    // Mode d'emploi :
    // La methode permet de tester si la creation du polygone est possible a travers les différents points
    // placés en entrée.
    // La méthode envoie true si et seulement si les points de  sastifait.
    
    bool ValideSegment (std::vector<Point> & ensembleDePoint);
    // Attribut:
    // < ensembleDePoint > : Vecteur contenant les points nécessaire à la creation du composant.
    
    // Mode d'emploi :
    // La methode permet de tester si la creation du segment est possible a travers les différents points
    // placés en entrée.
    // La méthode envoie true si et seulement si les points de  sastifait.
    
    bool ValideRectangle (std::vector<Point> & ensembleDePoint);
    
    // Attribut:
    // < ensembleDePoint > : Vecteur contenant les points nécessaire à la creation du composant.
    
    // Mode d'emploi :
    // La methode permet de tester si la creation du rectangle est possible a travers les différents points
    // placés en entrée.
    // La méthode envoie true si et seulement si les points de  sastifait.
    
    void AfficherElements();
    // Mode d'emploi :
    // La methode permet de tester si la creation du rectangle est possible a travers les différents points
    // placés en entrée.
    // La méthode envoie true si et seulement si les points de  sastifait.
    
    void AfficherCorbeille();
    // Mode d'emploi :
    // La methode permet de tester si la creation du rectangle est possible a travers les différents points
    // placés en entrée.
    // La méthode envoie true si et seulement si les points de  sastifait.
    
    bool Clear (bool complet = false);
    // Mode d'emploi :
    // La methode permet de supprimer l'ensemble des figures présentes dans le modèle.
    // A la suite de l'appel de la fonction, transféreras l'ensemble présente dans le modèle, dans la corbeille.
   
    bool RedoClear ();
    // Mode d'emploi :
    // La methode permet de supprimer l'ensemble des figures présentes dans le modèle.
    // A la suite de l'appel de la fonction, transféreras l'ensemble présente dans le modèle, dans la corbeille.
    
    inline unsigned long nbElements ()
    {
        return figures.size();
    }
    
    void Save (std::string fichier);
    //-------------------------------------------- Constructeurs - destructeur
    
    // constructeur de la classe.
    Modele();
    
    // Destructeur de la classe.
    virtual ~ Modele();
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
    
    std::map< std::string, IFigure*> figures;           // Permet d'obtenir une reference sur les figures
    // traites par l'application
    std::map< std::string, IFigure*> corbeille;         // permet de conserver une reférence sur les figures supprimés
    
    std::deque < std::vector <std::string> > clearVector; // Liste nous permettant de conserver les evenement clear
    
    std::map<std::string, IFigure*>::iterator it; // uniterateur afin de les parcourir
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle

#endif /* defined(__TP4Forme__Modele__) */
