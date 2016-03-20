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
#include "Composite.h"
#include "Segment.h"
#include "Rectangle.h"
#include "Polygone.h"


//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques
bool Composite :: Deplacer(double differenceX,double differenceY)
{
    std::set<IFigure*>::iterator it;
    for ( it = composants.begin(); it!= composants.end(); ++it)
    {
        // je déplace la figure en appelant la fonction Deplacer associé à la figure
        // traitée.
        if ((*(*it)).Deplacer(differenceX,differenceY))
        {
            continue;
        }
        else
        {
            cout << " le deplacement est incorecte";
        }
    }
    return true;
} //----- Fin de MÈthode

// Ici on aurait tres bien pu retourner dans le package vue, mais la fonction nous est utile seulement
// pour vérifier que le programme fonctionne correctement.
// donc inutile de passer par du MVC
void Composite :: Afficher(ostream & fichierSortie )
{
    std::set<IFigure*>::iterator it;
    
    // nous affichons le type de l'intersection
    if ( intersection == true)
    {
        fichierSortie << " Intersection " << endl <<"{" << endl;
    }
    
    else
    {
        fichierSortie << " Réunion " << endl << "{" << endl;
    }
    
    // nous affichons les figures qui ont servis pour construire la nouvelle figure.
    
    for ( it = composants.begin(); it!= composants.end(); ++it)
    {
        // j'affiche les multiples figure contenue dans l'intersection ou
        // la réunion de multiples figures.
        (*(*it)).Afficher();
       
    }
    cout << "}" << endl;
}

bool Composite :: EstDedans (Point pointATraiter)
{
    bool verif = false;
    std::set<IFigure*>::iterator it;
    
        if(intersection)
        {
            verif = VerificationIntersection(pointATraiter);
        }
            
        if(!intersection)
        {
            verif =  VerificationReunion(pointATraiter);
        }
    
   
    return verif; 
}

// Attribut:
// <pointATraiter> : permet de specifier le point que nous allons tester

// Mode d'emploi :
// Permet de tester si le point appartient à la figure traitée.
// renvoie true si le point appartient a la figure.
// renvoie false si le point n'appartient pas à la figure.


//------------------------------------------------- Surcharge d'opÈrat

//-------------------------------------------- Constructeurs - destructeur
Composite::Composite (string unType ,bool intersection, vector <IFigure*> ensembleFigure)
{
    vector <IFigure*> :: iterator it = ensembleFigure.begin();
    // copie profoonde des figures appartenant au composite.
    for (;it != ensembleFigure.end();it++)
    {
        IFigure * figure;
        IFigure * figureTemp;
        figureTemp = *it;
        figure = figureTemp->Copie();
        composants.insert(figure);
    }
    
    this->intersection = intersection;
    IFigure::type = unType;
}

string  Composite :: toWrite (string nom)
{
    int i = 1;
    string res = "LOADCOMP "+ nom + " " + to_string(intersection) + " <"+nom +">"+ "";
    std::set<IFigure*>::iterator it = composants.begin();
    res += (*(it))->toWrite(nom +"_0");
    
    for (it++; it != composants.end(); it++)
    {
        string a = to_string(i);
        res += " | "+(*(it))->toWrite(nom +"_"+ a);
        res += + "";
        i++;
    }
    
    res +=  " </"+nom +"> "  ;
    return res;
}

IFigure* & Composite :: Copie ()
{
    std::vector<IFigure *> res;
    std::set<IFigure*>::iterator it = composants.begin();
    for (; it != composants.end(); it++)
    {
        IFigure * figure = (*it)->Copie();
        res.push_back(figure);
    }
    
    IFigure * composite = new Composite("C",intersection,res);
    return composite;
}

// libération de la mémoire obligatoire car allocation dynamique. 
Composite :: ~Composite ()
{
    set <IFigure*> :: iterator it = composants.begin();
    for (; it!= composants.end(); it++)
    {
        delete *it;
    }
    
} //----- Fin de ~Composite


//------------------------------------------------------------------ PRIVE

bool Composite :: VerificationIntersection(Point pointAtraiter)
{
    std::set<IFigure*>::iterator it;
    for ( it = composants.begin(); it!= composants.end(); ++it)
    {
        IFigure *figure = *(it);
        if (figure->EstDedans(pointAtraiter) == false )
        {
            return false;
        }
    }
    return true;
    
    
}

bool Composite :: VerificationReunion(Point pointAtraiter)
{
    std::set<IFigure*>::iterator it;
    bool test = false;
    for ( it = composants.begin(); it!= composants.end(); it++)
    {
        IFigure *figure = *(it);
        if (figure->EstDedans(pointAtraiter))
        {
            test =  true;
        }
    }
    return test;
    
    
}
//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
