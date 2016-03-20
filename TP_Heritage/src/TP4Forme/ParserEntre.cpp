/*************************************************************************
 -------------------
 début                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/


//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <sstream>
//-------------------------------------------------------- Include Personnel
#include "Point.h"
#include "IAction.h"
#include "ActionAjout.h"
#include "ActionEffacer.h"
#include "ActionDeplacer.h"
#include "ActionClear.h"
#include "ParserEntre.h"
#include "Rectangle.h"
#include "Segment.h"
#include "Polygone.h"
#include "Composite.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques


void ParserEntre::DebuterLecture()
{
    while(statusLecture)
    {
        LireLigne();
    }
    
}
// Fin DebuterLecture()




//-------------------------------------------- Constructeurs - destructeur


ParserEntre::ParserEntre(void)
{
    statusLecture = true;
    commandes;
}


ParserEntre::~ParserEntre(void)
{
    
}

//------------------------------------------------------------------ PRIVE

void ParserEntre::LireLigne(std::istream & flux, bool loading)
{
    //cout << "reading line " << endl;
    
    // on récupère la ligne
    string line;
    getline(flux, line);
    
    
    
    istringstream lineStream(line);
    Controleur* c = Controleur::getInstance();
    Modele* modele = c->getModele();
    string cmd;
    string nom;
    // lecture le l'entrée
    lineStream >> cmd;
    
    // si on est pas en loading on ajoute la commande en cour a la liste de commande
    if(!loading && cmd != "LOAD" && cmd != "LIST" && cmd != "HIT" && cmd != "SAVEC" && cmd != "EXIT" && cmd != "SAVE" )
        commandes.push_back(line);
    
    // on déclare la future action a effectuée en fonction de la liste
    IAction * action;
    
    // switch case des type d'entrée --------
    if(cmd == "R") // Cas du rectangle
    {
        // on récupère le nom de la figure
        lineStream >> nom;
        
        // on récupère le tableau de points
        vector<Point> points = LireTabPoint(lineStream);
        // Si la figure est valide, on crée l'action associée
        if(modele->CreerRectangle(nom, points)) // retourne true si la figure est valide
        {
            c->getVue()->AfficherOK();
            // on crée l'action associée
            action = new ActionAjout(nom);
            
        }
        else
        {   c->getVue()->AfficherErreur();       // si la figure n'est pas valide on sort
            return;
        }
    }
    else if (cmd =="PC") // Cas du polygone convexe
    {
        
        // on récupère le nom de la figure
        lineStream >> nom;
        
        // on récupère le tableau de points
        vector<Point> points = LireTabPoint(lineStream);
        
        if(modele->CreerPolygone(nom, points)) // retourne true si la figure est valide
        {
            c->getVue()->AfficherOK();
            action = new ActionAjout(nom);// on crée l'action associée
        }
        else    // si la figure n'est pas valide on sort
        {
            c->getVue()->AfficherErreur();
            return;
        }
    }
    
    else if (cmd =="S") // Cas du segment
    {
        
        
        // on récupère le nom de la figure
        lineStream >> nom;
        
        // on récupère le tableau de points
        vector<Point> points = LireTabPoint(lineStream);
        
        if(modele->CreerSegment(nom, points)) // retourne true si la figure est valide
        {
            c->getVue()->AfficherOK();
            action = new ActionAjout(nom);// on crée l'action associée
        }
        else    // si la figure n'est pas valide on sort
        {
            c->getVue()->AfficherErreur();
            return;
        }
        
    }
    else if (cmd == "EXIT")
    {
        statusLecture = false;
        return;
    }
    
    else if (cmd == "LIST")
    {
        modele->AfficherElements();
        return;
    }
    
    else if (cmd == "DISPACTIONS")
    {
        c->afficherActions();
        return;
    }
    
    else if (cmd == "SAVEC")
    {
        string nom;
        
        if (c->getModele()->nbElements() != 0)
        {
            lineStream >> nom;
            c->getModele()->Save(nom);
            c->getVue()->AfficherOK();
        }
        else
        {
            c->getVue()->AfficherNbdispo();
            c->getVue()->AfficherSuppressionImpossible();
        }
        return;
    }
    
    else if (cmd == "SAVE")
    {
        if (c->getModele()->nbElements() != 0)
        {
            string nom;
            lineStream >> nom;
            if(nom =="")
            {
                c->getVue()->AfficherErreur();
                return;
            }
            
            ofstream logFile(nom, ios::out | ios::trunc);  // ouverture en écriture d'un fichier
            
            for(int i =0; i <commandes.size();i++)
            {
                logFile << commandes[i]<<endl;
            }
            c->getVue()->AfficherOK();
        }
        else
        {
            c->getVue()->AfficherNbdispo();
            c->getVue()->AfficherSuppressionImpossible();
        }
        return;
    }
    
    else if (cmd == "REDO")
    {
        if (c->redo())
        {
            c->getVue()->AfficherOK();
        }
        else
        {
            c->getVue()->AfficherActionImpossible();
        }
        return;
    }
    
    else if (cmd == "UNDO")
    {
        if (c->undo())
        {
            c->getVue()->AfficherOK();
        }
        else
        {
            c->getVue()->AfficherActionImpossible();
        }
        return;
    }
    
    else if (cmd == "OR")
    {
        // on récupère le nom de la figure
        lineStream >> nom;
        
        // on récupère le tableau de nom
        vector<string> noms = LireTabString(lineStream);
        
        if(modele->CreerComposite(false,nom, noms)) // retourne true si la figure est
        {
            c->getVue()->AfficherOK();
            action = new ActionAjout(nom);// on crée l'action associée
        }
        else    // si la figure n'est pas valide on sort
        {
            c->getVue()->AfficherErreur();
            return;
        }
    }
    
    else if (cmd == "OI")
    {
        // on récupère le nom de la figure
        lineStream >> nom;
        
        // on récupère le tableau de nom
        vector<string> noms = LireTabString(lineStream);
        
        if(modele->CreerComposite(true,nom, noms)) // retourne true si la figure est valide
        {
            c->getVue()->AfficherOK();
            action = new ActionAjout(nom);// on crée l'action associée
        }
        else    // si la figure n'est pas valide on sort
        {
            c->getVue()->AfficherErreur();
            return;
        }
    }
    
    else if (cmd == "DELETE")
    {
        // on récupère le tableau de nom
        vector<string> noms = LireTabString(lineStream);
        if(modele->SupprimerFigures(noms)) // retourne true si la figure est valide
        {
            c->getVue()->AfficherOK();
            action = new ActionEffacer(noms);// on crée l'action associée
        }
        else    // si la figure n'est pas valide on sort
        {
            c->getVue()->AfficherSuppressionImpossible();
            return;
        }
    }
    
    else if (cmd == "CLEAR")
    {
        if ( c->getModele()->nbElements() != 0)
        {
            modele->Clear();
            c->getVue()->AfficherOK();
            action = new ActionClear();// on crée l'action associée
        }
        else
        {
            c->getVue()->AfficherNbdispo();
        }
        
    }
    
    else if (cmd == "LOADCOMP")
    {
        Composite * comp = LireComp(lineStream);
        comp->Afficher();
    }
    
    else if (cmd == "LOAD")
    {
        c->getModele()->SupprimerTousLeModele();
        string nomFic;
        lineStream >> nomFic;
        /*
        if (lineStream.good())
        {*/
            Load(nomFic);
            c->getVue()->AfficherFinLoad();/*
        }*/
    }
    
    else if (cmd == "MOVE")
    {
        // on récupère le nom de la figure
        lineStream >> nom;
        
        // on récupère les variations
        int dx,dy;
        
        lineStream >> dx;
        lineStream >> dy;
        
        if(modele->Deplacer(nom,dx,dy)) // retourne true si la figure est valide
        {
            c->getVue()->AfficherOK();
            action = new ActionDeplacer(nom,dx,dy);// on crée l'action associée
        }
        else// si la figure n'est pas valide on sort
        {
            c->getVue()->AfficherMessageFigureNonPresente();
            return;
        }
    }
    
    else if (cmd == "HIT")
    {
        // on récupère le nom de la figure
        lineStream >> nom;
        
        // on récupère les variations
        int x,y;
        
        lineStream >> x;
        lineStream >> y;
        Point pointTest (x,y);
        if(modele->EstDedans(pointTest, nom))
        {                                // retourne true si la figure est valide
            c->getVue()->AfficherMessagePointDedans();
            action = new ActionAjout(nom);// on crée l'action associée
        }
        else
            // si la figure n'est pas valide on sort
        {
            c->getVue()->AfficherMessagePointNONDedans();
            return;
        }
    }
    else if (cmd == "")
    {
    }
    else
    {
        c->getVue()->AfficherCommandeNonDispo();
        
    }
    
    // On ajoute l'action au controleur
    c->AjouterAction(action);
}

// retourne un tableau de point a partir d'une lecture sur la sortie standarde
vector<Point> ParserEntre::LireTabPoint(istringstream & lineStream)
{
    // instanciation du tableau de point
    vector<Point> points;
    
    double x,y;
    while(lineStream >> x >> y)
    {
        points.push_back(Point(x,y));
    }
    
    return points;
}

// retourne un tableau de nom a partir d'une lecture sur la sortie standarde
vector<string> ParserEntre::LireTabString(istringstream & lineStream)
{
    // instanciation du tableau de point
    vector<string> noms;
    
    // lecture des points
    string tmp;
    
    while(lineStream >> tmp)
    {
        noms.push_back(tmp);
    }
    
    return noms;
}

Composite * ParserEntre::LireComp(std::istringstream & lineStream)
{
    string ligneCmp;    // Correspond a la potentielle ligne de composite
    string nomComp;     // nom du potentiel composite
    string reste;       // reste de la ligne a traiter
    string tmp;
    IFigure * curFig;
    string nom;
    string bin;
    bool intersection;
    std::vector<IFigure*> figures;
    string cmd;
    int idCurFils = 0;
    string primaireS;
    string curComm;
    
    // on récupère le nom et le type du composite
    lineStream >> nom;
    lineStream >> intersection;
    
    // On découpe la ligne interne du composant ( correspond a reste)
    getline( lineStream, tmp);
    
    cout << "nom : " << nom << endl;
    cout << "traitement de : " << tmp << endl<< endl;
    
    size_t fin = tmp.find("</"+nom+">");
    size_t debut = tmp.find("<"+nom+">");
    reste = tmp.substr(debut+nom.size()+3, fin-nom.size()-4);
    
    istringstream resteFlux(reste);
    istringstream curCommandeFlux;
    
    // Tant qu'il y a du contenu
    while(!resteFlux.eof() && idCurFils < 2) // Pour toute la ligne en cours
    {
        // on récupère la commande
        resteFlux >> cmd;
        
        cout  << "cmd : " << cmd<< endl;
        
        if( cmd == "LOADCOMP")
        {
            // On récupère le nom
            nomComp = nom+"_"+to_string(idCurFils);
            
            cout << "CompNom: "<< nomComp;
            
            // je lis sur ce nouveau flux
            curFig = LireComp(resteFlux);
            
            getline( resteFlux, reste);
            cout << "reste après comp "<<nomComp<<" : " << reste <<endl << endl;
        }
        
        /* string curCommande
         resteFlux
         istringstream curCommandeFlux;*/
        
        else if(cmd == "R")
        {
            getline(resteFlux,reste, '|');
            
            resteFlux >> bin; // on lit le nom
            string listePoint;
            
            getline(resteFlux, listePoint, '|');
            
            istringstream listePointFLux(listePoint);
            vector<Point> points = LireTabPoint(listePointFLux);
            // on instancie la figure correspondante
            curFig = new Rectangle("R",points);
            cout << "creation Rectangle" << endl << endl;
            
            string s = resteFlux.str();
            cout << endl << "s1 : " <<s <<endl<<"pipe" <<(s.find('|') != std::string::npos)<<endl;
            
            getline(resteFlux,reste, '|');
            /*
             if(s.find('|') != std::string::npos)
             {
             getline(resteFluxTMP,reste, '|');
             }
             else
             getline(resteFluxTMP,reste);
             */
            cout << "reste aprŽs rec "<< bin <<" : " << reste <<endl << endl;
        }
        
        else if(cmd == "S")
        {
            vector<Point> points = LireTabPoint(resteFlux);
            
            // on instancie la figure correspondante
            curFig = new Segment("S",points);
            cout << "creation Segment" << endl;
            getline(resteFlux,reste, '|');
        }
        idCurFils++;
        
        // On ajoute la figure courante a la liste de figure
        figures.push_back(curFig);
    }
    
    Composite * c = new Composite("C", intersection, figures);
    
    return c;
    
}

void ParserEntre::Load(std::string nomFic)
{
    ifstream flux;
    flux.open(nomFic);
    
    if(flux)
    {
        
        while(!flux.eof())
        {
            LireLigne(flux,1);
        }
    }
}

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

