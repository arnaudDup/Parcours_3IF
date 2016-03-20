/*************************************************************************
 Capteur.cpp -  description
 -------------------
 dÈbut                : 23/10/2014
 copyright            : (C) 2015 par Jacques Folléas et Arnaud Dupeyrat
 *************************************************************************/

//---------- Réalisation de la classe Capteur (fichier Capteur.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "Capteur.h"
//------------------------------------------------------------- Constantes


//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés



//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques

void Capteur::STAT_C ()
{       if(tableauCapteur[JOURS*CHOIXJOUR + 0*CHOIXHEURE+0*CHOIXMINUTE+4] == 0) 
// Si aucune mesure n'a été prise par le capteur alors on affiche 0% pour toutes les couleurs. 
	{	cout<<"V "<<0<<"%"<<endl;
		cout<<"J "<<0<<"%"<<endl;
		cout<<"R "<<0<<"%"<<endl;
	        cout<<"N "<<0<<"%"<<endl;
	}
	else
        {   // Sinon on affiche le pourcentage de fois qu'a été mesuré une couleur sur le nombre
            // total de couleurs mesurées par le capteur appelant la fonction.
        cout<<"V "<<(int)(((float)tableauCapteur[JOURS*CHOIXJOUR +0 * CHOIXHEURE +0* CHOIXMINUTE +0]/tableauCapteur[JOURS*CHOIXJOUR +0 * CHOIXHEURE +0* CHOIXMINUTE +4])*100)<<"%"<<endl;
        cout<<"J "<<(int)(((float)tableauCapteur[JOURS*CHOIXJOUR +0 * CHOIXHEURE +0* CHOIXMINUTE +1]/tableauCapteur[JOURS*CHOIXJOUR +0 * CHOIXHEURE +0* CHOIXMINUTE +4])*100)<<"%"<<endl;
        cout<<"R "<<(int)(((float)tableauCapteur[JOURS*CHOIXJOUR +0 * CHOIXHEURE +0* CHOIXMINUTE +2]/tableauCapteur[JOURS*CHOIXJOUR +0 * CHOIXHEURE +0* CHOIXMINUTE +4])*100)<<"%"<<endl;
        cout<<"N "<<(int)(((float)tableauCapteur[JOURS*CHOIXJOUR +0 * CHOIXHEURE +0* CHOIXMINUTE +3]/tableauCapteur[JOURS*CHOIXJOUR +0 * CHOIXHEURE +0* CHOIXMINUTE +4])*100)<<"%"<<endl;
	}
}//----------Fin de STAT_C


void Capteur::InserTableau ( int jour, int heure, int minute, int couleur )

{
    tableauCapteur[JOURS*CHOIXJOUR +0 * CHOIXHEURE +0* CHOIXMINUTE + couleur]++;
    tableauCapteur[JOURS*CHOIXJOUR +0* CHOIXHEURE +0* CHOIXMINUTE + COULEURS]++;
    tableauCapteur[jour*CHOIXJOUR +HEURES * CHOIXHEURE +0* CHOIXMINUTE + couleur]++;
    tableauCapteur[jour*CHOIXJOUR +HEURES * CHOIXHEURE +0* CHOIXMINUTE + COULEURS]++;
    tableauCapteur[jour*CHOIXJOUR +heure * CHOIXHEURE + MINUTES* CHOIXMINUTE + couleur]++;
    tableauCapteur[jour*CHOIXJOUR +heure * CHOIXHEURE + MINUTES* CHOIXMINUTE + COULEURS]++;
    tableauCapteur[jour*CHOIXJOUR +heure * CHOIXHEURE + minute* CHOIXMINUTE + couleur]++;
    tableauCapteur[jour*CHOIXJOUR +heure * CHOIXHEURE + minute* CHOIXMINUTE + COULEURS]++;
// On incrémente dans le tableau contenant les prises de mesures effectuées par le capteur appelant la fonction.
	
} //-----InserTable




//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    
    
    Capteur :: Capteur (int IDParametre)
    {
        #ifdef MAP
        cout << "Appel au constructeur de Capteur" << IDParametre << endl;
        #endif
        ID = IDParametre;
        // L'identifiant du capteur va permetre de le retrouver dans la structure de données
        // du traffic et de spécifier un capteur lors de l'utilisation d'une commande.
        tableauCapteur= new int [(JOURS+1)*(HEURES+1)*(MINUTES+1)*(COULEURS+1)];
        // le tableau d'entier alloué va contenir le nombre de fois qu'une couleur a été mesuré à une heure, et
        // une minute par semaine. Il va également compter les sommes par heure et par jour ainsi
        // que la somme sur l'ensemble des couleurs à tous les étages.
        for (int u; u<(JOURS+1)*(HEURES+1)*(MINUTES+1)*(COULEURS+1); u++)
        {
            tableauCapteur[u]=0;
        }
        // Initialise le tableau, contenant toutes les mesures, à zéro.
        
        
    } //----- Fin de Capteur
    

    
    Capteur :: ~ Capteur ( )

    {
        #ifdef MAP
        cout << "Appel au destructeur de Capteur" <<  endl;
        #endif
        delete [] tableauCapteur;
    // On désaloue le tableau contenant les informations receuillies sur le traffic par le capteur detruie.
        
    } //----- Fin de ~Capteur
    
    
    //------------------------------------------------------------------ PRIVE
    
    //----------------------------------------------------- Méthodes protégées
    
    //------------------------------------------------------- Méthodes privées
