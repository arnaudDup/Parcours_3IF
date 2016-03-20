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
#include "Vue.h"
#include <string.h>
//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques

//------------------------------------------------- Surcharge d'opÈrat

//-------------------------------------------- Constructeurs - destructeur
void Vue :: AfficherErreur()
{
    cout << "ERR" << endl;
}
void Vue :: AfficherOK()
{
    cout << "OK" << endl;
}
void Vue :: AfficherMessageFigureNonPresente()
{
    cout << "# la figure recherché n'est pas présente dans le modéle actuellement" << endl;
}
void Vue :: AfficherMessagePointDedans()
{
    cout << "YES" << endl;
}
void Vue :: AfficherMessagePointNONDedans()
{
    cout << "NO" << endl;
}
void Vue :: AfficherSuppressionImpossible()
{
    cout << "Figures non presentes, imposssible" << endl;
}
void Vue :: AfficherActionImpossible()
{
    cout << "Action impossible à réaliser" << endl;
}
void Vue :: AfficherCommandeNonDispo()
{
    cout << "Commande non reconnue" << endl;
}
void Vue :: AfficherNbdispo()
{
    cout << "Attention pas d'élements" << endl;
}
void Vue :: SauvegardeNonFaite ()
{
    cout << "Sauvegarde Non effectué" << endl;
}
void Vue :: AfficherFinLoad()
{
    cout << "fin load" << endl;
}

Vue :: Vue ()
{
    
}
Vue :: ~Vue ()
{
    
} //----- Fin de ~Composite


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
