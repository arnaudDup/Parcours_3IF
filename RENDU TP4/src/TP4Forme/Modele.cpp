/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systËme
#include <iostream>
using namespace std;
#include <string>

//------------------------------------------------------ Include personnel

#include "Controleur.h"
#include "Modele.h"
#include "Rectangle.h"
#include "Segment.h"
#include "Vecteur.h"
#include "Composite.h"
#include "Polygone.h"
#include "Rectangle.h"
#include "Segment.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques

bool Modele :: Clear (bool complet)
{
    vector<string> vectorTemp;
    it = this->figures.begin();
    for (; it != figures.end() ; it++)
    {
        //on l'enregistre dans notre liste
        vectorTemp.push_back(it->first);
        corbeille.insert(*it);
    }
    
    figures.clear();
    clearVector.push_back(vectorTemp);
    
    return true;
    
}

void Modele :: SupprimerTousLeModele()
{
    figures.clear();
    corbeille.clear();
}

bool Modele :: RedoClear ()
{
    vector<string> vectorTemp;
    vectorTemp = clearVector.back();
    vector<string> :: iterator iterateur;
    for (iterateur = vectorTemp.begin() ; iterateur != vectorTemp.end(); iterateur++)
    {
        it = corbeille.find(*iterateur);
        figures.insert(*it);
        corbeille.erase(it);
    }
    
    clearVector.resize(clearVector.size()-1);
    return true; 
}


bool Modele :: CreerRectangle (const std :: string nom, std::vector<Point> & ensembleDePoint)
{
    if (! (ValideRectangle (ensembleDePoint)))
    {
        return false;
    }
    
    IFigure * figure;
    figure = new Rectangle ("R", ensembleDePoint);
    
    // on supprime la figure du modèle si celle-ci est deja existante.
    if (RetrouverFigure(nom) != NULL)
    {
        figures.erase(nom);
    }
    
    figures.insert(pair< string ,IFigure*> (nom,figure));
    return true;
    
}
bool Modele :: CreerPolygone (const std :: string nom,std::vector<Point> & ensembleDePoint)
{
    if (! (ValidePolygone(ensembleDePoint)))
    {
        return false;
    }
    IFigure * figure;
    
    
    // on supprime la figure du modèle si celle-ci est deja existante.
    if (RetrouverFigure(nom) != NULL)
    {
        figures.erase(nom);
    }
    
    figure = new Polygone ("PC", ensembleDePoint);
    figures.insert(pair< string ,IFigure*> (nom,figure));

    return true;
}
bool Modele :: CreerSegment (const std :: string nom, std::vector<Point> & ensembleDePoint)
{

    if (! (ValideSegment(ensembleDePoint)))
    {
        return false;
    }
    
    IFigure * figure;
    // on supprime la figure du modèle si celle-ci est deja existante.
    if (RetrouverFigure(nom) != NULL)
    {
        figures.erase(nom);
    }
    figure = new Segment ("S" , ensembleDePoint);
    figures.insert(pair< string ,IFigure*> (nom,figure));
    return true;
}

vector<IFigure*>& Modele :: RechercheParNom(std::vector<string> & ensembleDePoint, std::vector<IFigure*> & vectorFigures)
{
    vector<string> :: iterator it = ensembleDePoint.begin();
    
    for(;it != ensembleDePoint.end() ; it++)
    {
        IFigure * figure = RetrouverFigure(*(it));
        
        // nous testons qu'il existe une figure associé au nom choisis.
        if (figure != NULL)
        {
            vectorFigures.push_back(figure);
        }
    }
    return vectorFigures;
}
bool Modele :: CreerComposite (bool intersection, const std :: string nom, std::vector<string> &ensembleDeFigure)
{
    IFigure * figure;
    vector<IFigure*> vectorFigures;
    RechercheParNom(ensembleDeFigure,vectorFigures);
    if (vectorFigures.size() < 2)
    {
        return false;
    }

    // on supprime la figure du modèle si celle-ci est deja existante.
    if (RetrouverFigure(nom) != NULL)
    {
        figures.erase(nom);
    }
    figure = new Composite("C",intersection,vectorFigures);
    
    // nous l'insérons dans les figures potentiellement traitable.
     cout << "Nous avons creer le composite avec " << vectorFigures.size() << " figures" << endl;
    figures.insert(pair< string ,IFigure*> (nom,figure));
    return true;
}

bool Modele :: TestSuppression (std::vector<string> & noms)
{
    vector<string> :: iterator it = noms.begin();
    
    for(;it != noms.end() ; it++)
    {
        IFigure * figure = RetrouverFigure(*(it));
        
        // nous testons qu'il existe une figure associé au nom choisis.
        if (figure == NULL)
        {
            return false;
        }
    }

    return true;
}

bool Modele ::  Deplacer(const std :: string nom, int dx, int dy)
{
    IFigure * figure = RetrouverFigure(nom);
    if ( figure == NULL)
    {
        return false;
    }
    figure -> Deplacer(dx,dy);
    return true;
}

bool Modele :: SupprimerFigures(std::vector<string> &noms)
{
    // nous testons si toutes les figures sont presentes dans le modele
    if (TestSuppression(noms) == false)
    {
        return false;
    }
    if (noms.size() == 0)
    {
        return false; 
    }
    
    // Tous les elements de la liste sont present.
    vector<string> :: iterator it = noms.begin();
    for (; it != noms.end(); it++)
    {
        SupprimerFigure(*it);
    }
    return true;
    
}
bool Modele :: RestaurerFigures(std::vector<std::string> & noms)
{
    // les tests ne sont pas nécessaire car traité en interne.
    
    // Tous les elements de la liste sont present.
    vector<string> :: iterator it = noms.begin();
    for (; it != noms.end(); it++)
    {
        RestaurerFigure(*it);
    }
    return true;
    
}

bool Modele :: SupprimerFigure(const std::string nom)
{
    it = figures.find(nom);
    // si l'element existe alors nous l'inserons dans la corbeille et le
    // supprimons de l'ensemble des figures a traitees
    corbeille.insert(*it);
    figures.erase(it);
    return true;
    
}

bool Modele :: RestaurerFigure(const std::string nom)
{
    
    it = corbeille.find(nom);
    figures.insert(*it);
    corbeille.erase(it);
    return true;
    
}

bool Modele :: ValidePolygone(std::vector<Point> &ensembleDePoint)
{
    
    if ( ensembleDePoint.size() < 2)
    {
        return false;
    }
    
    bool interne = true;
    // on construit un vecteur pouvant traiter l'esemble des points dans une seule et unique boucle.
    // en utilisant le constructeur par defaut.
    Point a = ensembleDePoint[0];
    Point b = ensembleDePoint[1];
    Point c = ensembleDePoint[2];
    
    Vecteur vecteurTest1 (a, b);
    Vecteur vecteurTest2 (b, c);
    double angle = vecteurTest1.Angle(vecteurTest2);
    // nous vérifions le premier angle traité pour connaitre ce que nous devons teste
    // car un polygone est strictement convexe si ces angles sont inférieurs a 180 degres
    // --> determination du sens.
    if ( angle > 180)
    {
        interne = false;
    }
    
    
    vector<Point>::iterator it = ensembleDePoint.begin();
    // pour calculer l'angle il est necessaire de traiter tout le temps deux vecteurs
    Vecteur *courant;
    Vecteur *next;
    
    // on initialise le courant.
    Point p1 = *it;
    Point p2 = *(it+1);

    
    courant = new Vecteur(p1,p2);
    
    it++;
    
    
    for (;it != ensembleDePoint.end()-1;  it++ )
    {
        Point p1 = *it;
        Point p2 = *(it+1);
        
        next = new Vecteur(p1,p2);
    
        if((interne && (courant->Angle(*next) >= 180)) ||
           (!(interne) && (courant->Angle(*next) <= 180)))
        {
            delete next;
            delete courant;
            return false;
        }
        
        delete courant;
        courant = next;
    }
    
    
    // on traite le dernier point, le fermeture du polygone convexe.
    next = new Vecteur(*it,p1);
    
    if((interne && (courant->Angle(*next) >= 180)) ||
       (!(interne) && (courant->Angle(*next) <= 180)))
    {
        delete next;
        delete courant;
        return false;
    }
    
    // suppresion des pointeurs servant a l'algorithme.
    delete next;
    delete courant;
    return true;
    
}

bool Modele :: ValideSegment (std::vector<Point> & ensembleDePoint)
{
    bool verif = true;
    // Nous testons que le nombre d'entrée est bien égale à deux
    if ( ensembleDePoint.size() != 2)
    {
        verif = false;
    }
    
    // a voir si d'autres tests sont nécessaire.
    return verif;
}

bool Modele ::  ValideRectangle (std::vector<Point> & ensembleDePoint)
{
    bool verif = true;
    // Nous testons que le nombre d'entrée est bien égale à deux
    if ( ensembleDePoint.size() != 2)
    {
        verif = false;
    }
    
    // a voir si d'autres tests sont nécessaire.
    return verif;
}

// il faut bien penser a tester si la valeur est differentes de nullptr
IFigure *  Modele :: RetrouverFigure(const std::string nom)
{
    it = figures.find(nom);
    IFigure *temp = NULL;
    // Nous reinserons l'elements traites dans l'ensemble des figure qui sont traitees par notre programme.
    if (it != figures.end())
    {
        temp = it->second;
    }
    
    return temp;
}

bool Modele :: EstDedans(Point pointATraiter, string nom)
{
    bool verif = false;
    // on recupere la figure à l'aide du nom de la figure.
    it = figures.find(nom);
    if (it != figures.end())
    {
        verif  = it->second->EstDedans(pointATraiter);
        
    }
    
    return verif;    
}

void Modele :: AfficherElements()
{
    
    it = this->figures.begin();
    for (; it!= this->figures.end(); it++)
    {
        cout << it->first;
        it->second->Afficher();
    }
    
    
}

void Modele :: AfficherCorbeille()
{
    
    it = corbeille.begin();
    for (; it!=corbeille.end(); it++)
    {
        cout << it->first;
        it->second->Afficher();
    }
    
}

void Modele ::  Save (string nomFichier)
{
    // Ouverture du fichier
    ofstream fichierSave;
    fichierSave.open(nomFichier);
    
    // on parcourt la liste de figures, pour récuperer l'ensemble des string
    it = this->figures.begin();
    for (; it!= this->figures.end(); it++)
    {
        fichierSave << it->second->toWrite(it->first) << endl ;
    }
}

//------------------------------------------------- Surcharge d'opÈrat

//-------------------------------------------- Constructeurs - destructeur

// ici il faudra recharcher le modele avec l'option de sauvegarde....
Modele :: Modele ()
{
    it = figures.begin();
    figures;
    corbeille;
    clearVector;

}

Modele :: ~Modele ()
{
    // à la destruction il est nécessaire de libérer correctement la mémoire.
    // chaque figure étant instancié à l'aide d'un new il est nécessaire, de
    // delete zone de mémoire pointé.
    
    it = corbeille.begin();
    for (; it!=corbeille.end(); it++)
    {
        // Suppression de la zone de mémoire associé.
        delete it->second;
    }
    
    it = figures.begin();
    for (; it!= figures.end(); it++)
    {
        // Suppression de la zone de mémoire associé.
        delete it->second;
    }
    
} //----- Fin de ~Composite


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
