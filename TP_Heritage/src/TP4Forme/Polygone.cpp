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
#include "Polygone.h"
#include "Vecteur.h"
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques

bool Polygone ::  Deplacer (double differenceX, double differenceY)
{
    vector <Point> :: iterator it;
    for( it = ensembleDePoint.begin(); it != ensembleDePoint.end(); it++ )
    {
        it->DeplacerPoint(differenceX,differenceY);
    }
    return true;
}
// fin de deplacer


// Ici on aurait tres bien pu retourner dans le package vue, mais la fonction nous est utile seulement
// pour vérifier que le programme fonctionne correctement.
void Polygone:: Afficher (ostream & fichierSortie)
{
    fichierSortie << " Polygone convexe {" ;
    vector <Point> :: iterator it;
    for( it = ensembleDePoint.begin(); it != ensembleDePoint.end(); it++ )
    {
        it->afficherPoint(fichierSortie);
        if (it != ensembleDePoint.end()-1)
        {
            fichierSortie << ",";
        }
    }
    fichierSortie << "}" << endl;

}

// Fin de afficherRectangle


bool Polygone :: EstDedans (Point pointATraiter)
{
        unsigned long longueur = ensembleDePoint.size();
        bool verif = true ;
        int compteur = 0;
    
        // premiérement on vérifie que le point ne se situe pas sur une arrete du polygone.
        for ( int i = 0; i < ensembleDePoint.size()-1; i++)
        {
            Vecteur vectorCourant (ensembleDePoint[i],ensembleDePoint[i+1]);
            Vecteur vectorTest1 (pointATraiter,ensembleDePoint[i+1]);
            Vecteur vectorTest2 (pointATraiter,ensembleDePoint[i]);
            
            // alors le point est considéré comme faisant partie du polygone. 
            if ((vectorTest1.Norme()+vectorTest2.Norme()) == vectorCourant.Norme())
            {
                return verif;
            }
        }
    
        // puis nous testons si le point si situe dans le polygone.
        double PointAbscisse = pointATraiter.getAbscisse();
        double PointOrdonne = pointATraiter.getOrdonne();
    
        // Nous testons sur l'ensemble des point en prenant comme référence une droite horizontale et nous comptons le nombre de fois
        // que le droite croise une arrete du polygone testé.
        for(int i = 0; i < longueur - 1 ; i++)
        {
            // on récupére les abscisse et les ordonnées
            double ordonne1 = ensembleDePoint[i].getOrdonne();
            double abscisse1 = ensembleDePoint[i].getAbscisse();
            double ordonne = ensembleDePoint[i+1].getOrdonne();
            double abscisse = ensembleDePoint[i+1].getAbscisse();
            
            // on selectionne les segments se situant dans le tube creer par les ordonnées
            if( ((ordonne1 <= PointOrdonne ) && (ordonne >= PointOrdonne)) ||
                ((ordonne1 >= PointOrdonne ) && (ordonne <= PointOrdonne))
              )
            {
                // on verifie que le point se situe du bon coté du segment créer
                double temp = (double) (PointOrdonne - ordonne1) / (ordonne - ordonne1);
                if ( PointAbscisse < (abscisse1 + temp * (abscisse - abscisse1)))
                {
                    // on compte combien de fois la doite croise l'arrete du polygone.
                    compteur++ ;
                }
            }
        }
    
        // si le nombre de croisement est paire alors le point est forcement en dehors du polygone.
        if (compteur % 2 == 0)
        {
            verif = false;
        }
        return verif;

}

string  Polygone :: toWrite (string nom)
{
    string res = "PC "+ nom;
    for(int i = 0; i<ensembleDePoint.size(); i++)
    {
        res += " "+ ensembleDePoint[i].toWrite();
    }
    
    return res;
}

IFigure* & Polygone :: Copie ()
{
    IFigure * figure;
    std::vector<Point> Points (ensembleDePoint.begin(),ensembleDePoint.end());
    figure = new Polygone ("PC",Points);
    return figure;
}

//------------------------------------------------- Surcharge d'opÈrat

//-------------------------------------------- Constructeurs - destructeur

Polygone :: Polygone (std::string unType,std::vector<Point> ensembleDePoint)
{
    IFigure::type = unType;
    this->ensembleDePoint = ensembleDePoint;
} //----- Fin de Rectangle



Polygone :: ~Polygone ()
{
    
} //----- Fin de ~Rectangle



//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
