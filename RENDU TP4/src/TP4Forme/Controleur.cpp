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
#include "controleur.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques
Controleur* & Controleur ::  getInstance()
{
    return uniqueInstance;
}

// Ajout d'une action a la liste d'actions
void Controleur :: AjouterAction(IAction* &a)
{
    
    // Si on essaie de modifié le modéle alors que l'on est en undo
    // On supprime toutes les actions qui sont après l'action courante.
    if(currentAction< actions.size() )
    {
        actions.resize(currentAction);
        actions.push_back(a);
    }
    
    else
    {
        // L'action est ajoutée a son indice courant
        actions.push_back(a);
    }
    currentAction++;
}

// Défait laction en cours. Le boolean de retour est vrai si l'undo a marché. L'undo peut ne pas marcher si :
//      - l'action courante est la première action
bool Controleur:: undo()
{
    // si on est a la première action on ne peut effectuer des undos
    if(currentAction == 0)
    {
        return false;
    }
    
    // Si non on annule l'action actuelle et on recule
    IAction* action = actions.at(currentAction-1);
    action->undo();
    currentAction --;
    
    return true;
}

// Effectue l'action suivante. Le boolean de retour est vrai si le redo a marché. redo peut ne pas marcher si :
//      - l'action courante est la dernière

bool Controleur:: redo()
{
    // si on est a la dernière action
    if(currentAction == actions.size())
    {
        return false;
    }
    
    // on execute l'action suivante
    IAction * ActionCourante = actions[currentAction];
    currentAction++;
    ActionCourante->redo();
    
    return true;
}

void Controleur :: afficherActions()
{
    for(int i =0; i< actions.size();i++)
    {
        cout <<i<<": ";
        IAction* cur = actions[i];
        cur->disp();
    }
}

// Ajout d'une action a la liste d'actions
void Controleur::DebuterLecture()
{
    parser->DebuterLecture();
}


//-------------------------------------------- Constructeurs - destructeur

Controleur::Controleur()
{
    currentAction = 0;
    actions;
    parser = new ParserEntre;
    modele = new Modele();
    vue = new Vue();
}

Controleur :: ~Controleur()
{
    for(int i =0; i< actions.size();i++)
    {
        delete actions[i];
    }
    delete vue;
    delete modele;
    delete parser;
}
//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
