/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

//---------- Interface de la classe Rectangle (fichier Rectangle) ------
#ifndef __TP4Forme__Parseur__
#define __TP4Forme__Parseur__

//--------------------------------------------------- Interfaces utilisÈes
#include "Point.h"
#include "Controleur.h"
#include "Composite.h"
#include <vector>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// 
//
//------------------------------------------------------------------------


class ParserEntre
{
    //----------------------------------------------------------------- PUBLIC
    
   
    
public:
    //----------------------------------------------------- MÈthodes publiques
    void DebuterLecture();
    // Mode d'emploi :
    // Permet de débuter la lecture, rentre dans une boucle infinie qui débute la lecture des différentes ligne.

    //-------------------------------------------- Constructeurs - destructeur
    
    ParserEntre(void);
    // constructeur de la classe.
    
    ~ParserEntre(void);
    // destructeur de la classe.
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- MÈthodes protÈgÈes
    
private:
    //------------------------------------------------------- MÈthodes privÈes
    void LireLigne(std::istream & flux = std::cin, bool loading = 0);
    // Attribut:
    // < flux > : permet de préciser le flux sur lequel les commandes doit etre lus.
    // < loading > : permet de l'ajout dans le vecteur d'action.
    
    // Mode d'emploi :
    // Permet de lire une ligne de commande, de la traiter en fonctione de la commande.
    // Par défaut la lesture se fait sur cin.
    
    Composite * LireComp(std::istringstream & lineStream);
    // Attribut:
    // < lineStream > : Flux sur lequel nous alllons lire le flux
    
    // Mode d'emploi :
    // Permet de lire, une comme LOADCOMP à partir d'un fichier,sauvegardé avec la commande SAVEC.
    // Actuellement, la méthode ne fonctionne pas. ( Probleme de flux )
    
    void Load(std::string nomFic);
    // Attribut:
    // < nomFic > : Noms du fichier qu'il faut charger.
    
    // Mode d'emploi :
    // Permet de charger le modéle à partir d'un fichier de commande.
    // la modéle chargé contient l'ensemble des actions
    
    
protected:
    //----------------------------------------------------- Attributs protÈgÈs
    
private:
    //------------------------------------------------------- Attributs privÈs
    std::vector<Point> LireTabPoint(std::istringstream & cmd);              // permet de stocker l'ensemble des points.
    std::vector<std::string>LireTabString(std::istringstream & lineStream); // permet de lire l'ensemble des noms.
    std::vector<std::string> commandes;                                     // permet d'avoir un un lien des commandes.
    bool statusLecture;                                                     // permet de stopper la lecture.
    
    //---------------------------------------------------------- Classes amies
    
    //-------------------------------------------------------- Classes privÈes
    
    //----------------------------------------------------------- Types privÈs
    
};

//----------------------------------------- Types dÈpendants de Rectangle

#endif /* defined(__TP4Forme__Parser__) */