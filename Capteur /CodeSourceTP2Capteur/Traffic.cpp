/*************************************************************************
 Traffic.cpp  -  description
 -------------------
 début                : 23/10/2014
 copyright            : (C) 2015 par Jacques Folléas et Arnaud dupeyrat
 *************************************************************************/

//---------- Réalisation de la classe Traffic (fichier Traffic.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systéme
#include <iostream>
using namespace std;
#include "Traffic.h"
#include "Capteur.h"
//# define MAP
//------------------------------------------------------ Include personnel

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privÈs


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- MÈthodes publiques
bool Traffic :: AjouterElement ( int IDParametre, int jour, int heure, int minute, int couleur)
{
    bool ajouter = false; // parametre permettant de verifier que l'insertion c'est correctement effectué
    Element * courant; // pointeur permettant de se déplacer dans l'arbre, indique la position du noeud étudié
    
    // La fonction etant membre, il nous est possible d'acceder directement à la racine de l'arbre.
    if (traffic == NULL)
    {
        traffic = CreationElement (IDParametre);
        (*traffic->capteur).InserTableau( jour, heure, minute, couleur);
         (*this).trafficRemplirTableau (jour,heure,minute,couleur );
        ajouter = true;

    }
    
    //  si le traffic n'a encore aucun resultat de capteur alors il est necessaire de creer
    //  la racine de l'arbre, on fait pointer vers la racine.
    else
    {
        courant = traffic; // nous partons de la racine
        while ( courant != NULL)
        {
            // si le capteur est deja present alors, nous completons le tableau si necessaire
            if ( IDParametre == (*courant->capteur).getIDParametre())
            {
                (*courant->capteur).InserTableau( jour, heure, minute, couleur);
                (*this).trafficRemplirTableau (jour,heure,minute,couleur );
                ajouter = true;          
                break ;
            }
            
            // Nous testons la branche droite de l'arbre, en inserant le capteur si necessaire.
            else if (IDParametre > (*courant->capteur).getIDParametre())
            {
                if (courant->droite  == NULL)
                {
                    courant->droite  = CreationElement (IDParametre);
                    (*courant-> droite -> capteur).InserTableau( jour, heure, minute, couleur);
                    (*this).trafficRemplirTableau (jour,heure,minute,couleur );
                    ajouter = true;
                    break;
                }
                else
                {
                    courant =  courant->droite ;
                }
            }
            
            // Nous testons la branche gauche de l'arbre.
            else  if (IDParametre < (*courant->capteur).getIDParametre())
            {
                if (courant->gauche  == NULL)
                {
                    courant -> gauche  = CreationElement (IDParametre);
                    ajouter = true;
                    (*courant-> gauche-> capteur).InserTableau( jour, heure, minute, couleur);
                    (*this).trafficRemplirTableau (jour,heure,minute,couleur );
                    break;
                }
                else
                {
                    courant =  courant->gauche ;
                }
                
            }
            
        }
        
    }

    courant = NULL;
    return ajouter;
    
}
void Traffic::AffichageArbre (Element * traffic)
{
    if(!traffic)
    {
        return;
    }
    // on affiche d'abbord tous les élements a gauche plus petit que ceux de droite
    if( traffic -> gauche != NULL)
        AffichageArbre(traffic -> gauche);
    
    cout << (* traffic->capteur).getIDParametre() << endl;
    
    if( traffic -> droite)
        AffichageArbre(traffic -> droite);
}

void Traffic::OPT(int jour, int heureDepartMin, int heureArriveeMax, int nombreDeSegment, int * Seg)
{	
    //On calcule a quel heure on peut partire au maximum
	Capteur * ptcapteur;
	int tableauTempsParCouleur[4]={1,2,4,10}; //Ce tableau contient les temps moyens qu'il faut 
	//pour parcourir un segement en fonctionde la couleur enregistré par le capteur présent sur le segement.
	int i; // iterrateur pour la boucle for qui parcour dans l'ordre les segements.
	

	float tempsmoyen; // temps qu'il faut statistiquement pour parcourir un segment, il sera calculer
			// au cour du temps en foncion des statistique de couleur pour chque minute et 
			//du tableau tableauTempsParCouleur.
	float restant; // restant représente la portion de segment qu'il reste à parcourir.
	int minuteDepartMin =0; // représente les minutes du départ le plus tôt.
	int minuteArriveeMax =0;// représente les minutes de l'arrivée la plus tarde.
	int heureOpt = heureDepartMin; //représente l'heure du départ le plus tôt permettant un temps de trajet minimum.
	int minuteOpt = minuteDepartMin; //représente les minutes du départ le plus tôt permettant un temps de trajet minimum.
	int heureDep = heureDepartMin;// représente l'heure du départ à tester.
	int minuteDep = 0; // représente les minutes du départ à tester.
	int tempsPossible= 0; //représente le temps de trajet pour le départ testé.
	int heureCourant = heureDep; // heure de l'iterateur de temps qui servira à faire les tests.
	int minuteCourant =0 ; // minutes de l'iterateur de temps qui servira à faire les tests.
		
		int tempsOpt = (heureArriveeMax-heureDepartMin)*60+1; // temps forcement suppérieur à la valeur optimal
			

		while( (heureDep != heureArriveeMax) || (minuteDep !=minuteArriveeMax))// on teste pour chaque minute entre heure de 
			//départ et l'heure de dernière arrivée quel est le durée du trajet.
		{
			//on calcul le temps du trajet si on part a l'heure depart qui va parcourir totue la plage horaire.
			heureCourant=heureDep;
			minuteCourant=minuteDep;
			// On initialise heure courante et minutes courante.
			
			for (i=0;i<nombreDeSegment;i++) // On parcour tout les segement dans l'ordre.
            {	ptcapteur = RechercheElement (Seg[i]);
				restant=1;
				//tan que l'on a pas completement passer un semgent on calcul le temps moyen de parcour
				// à la minute donnée et on regarde combine de ditance on été parcouru en une minute et
				// ce jusqu'a avoir parcouru cimpletement le segement.
				while(restant>0)
				{	

					// On incrémente le temps 
					// Le premier est annulé par la decrémentation precédente
					tempsmoyen=0;
					//On calcul le temps moyen pour traveser le segment 
				if (ptcapteur->tableauCapteur[jour*CHOIXJOUR +heureCourant * CHOIXHEURE +minuteCourant* CHOIXMINUTE +COULEURS]==0) //Si on a pas d'information sur un segemetn on considère qu'il a eu vert 100% du temps.
				{tempsmoyen=1;
				}
				else //sinon on calcul le temps moyne de parcour pour calculer notre vitesse
				{
					for (int couleur=0; couleur<4;couleur++)
					{	tempsmoyen+=(ptcapteur->tableauCapteur[jour*CHOIXJOUR +heureCourant * CHOIXHEURE +minuteCourant* CHOIXMINUTE +couleur]*tableauTempsParCouleur[couleur]);
					}
					tempsmoyen/=ptcapteur->tableauCapteur[jour*CHOIXJOUR +heureCourant * CHOIXHEURE +minuteCourant* CHOIXMINUTE +COULEURS];
				}	
					// pour ce faire on fait une moyen pondéré. 
								
					//on calcul le parcour restant avec restant-=1/tempsmoyen.
					restant-=1/tempsmoyen;
					//incrementation de l'heure 
					if (minuteCourant==59)
					{	heureCourant++;
						minuteCourant=00;
					}
					else
					{	minuteCourant++;
					}
				}
			
			}
			// Une fois que tous les segments ont été parcourus on calcule le temps du trajet en minutes.			
			tempsPossible=(heureCourant-heureDep)*60+(minuteCourant-minuteDep);
			// On verifie qu'on est bien arrivé avant l'heure d'arrivée indiquée en paramètre.
			if ((heureCourant*60+minuteCourant)>heureArriveeMax*60)
			{	tempsPossible=(heureArriveeMax-heureDepartMin)*60+1;
			}

			// On le compare au temps optimal jusqu'à présent, et si besoin est on enregistre
			// le départ et le temps de trajet qui deviennent optimaux.

			if(tempsPossible<tempsOpt)
			{
				tempsOpt=tempsPossible;
				heureOpt=heureDep;
				minuteOpt=minuteDep;
			}
			//On incrémente l'heure de départ à tester.
			if (minuteDep==59)
			{	heureDep++;
				minuteDep=00;
			}
			else
			{	minuteDep++;
			}	
		}
		// Une fois toutes les possibilités testées on affiche le resultat:
	if (tempsOpt < (heureArriveeMax-heureDepartMin)*60+1)	
	{	
        cout <<jour+1<<" "<< heureOpt<<" "<<minuteOpt<<" "<<tempsOpt<<endl;
	}
	else // Si il est impossible d'arriver à l'heure on l'affiche. 
	{ cout<<"impossible d'arriver à l'heure"<<endl;
	}
}


Capteur * Traffic::RechercheElement (int IDParametre)
{

    Element * courant;
    courant = traffic;            // pointeur sur un noeud de l'arbre permet de se deplacer au sein de celui-ci
                                  // qu'on initialise sur la racine de l'arbre.
    while ( courant != NULL )
    {
        if ( IDParametre == (*courant-> capteur).getIDParametre())
        {
            return courant-> capteur;
        }
        else if (IDParametre > (*courant-> capteur).getIDParametre())
        {
                courant =  courant-> droite ;
            
        }
        else  if (IDParametre < (*courant-> capteur).getIDParametre())
        {
           
                courant =  courant-> gauche ;
        }
        
    }
	return NULL;
}

void Traffic::JAM_DH (int jour )
{
    for (int heure=0; heure<HEURES; heure++)
    {
        if (StableauCapteur[jour][heure][60][COULEURS] == 0)
        {	cout<<jour+1<<" "<<heure<<" "<<0<<"%"<<endl;
        }
        else
        {	cout<<jour+1<<" "<<heure<<" "<<(int)(( (float)(StableauCapteur[jour][heure][60][2]+StableauCapteur[jour][heure][60][3]))*100/ StableauCapteur[jour][heure][60][4])<<"%"<<endl;
        }
    }

}//-------Fin de JAM_DH

void Traffic::STATS_D7 (int jour)
{	if(StableauCapteur[jour][HEURES][0][COULEURS]==0)
    {	cout<<"V "<<0<<"%"<<endl;
        cout<<"J "<<0<<"%"<<endl;
        cout<<"R "<<0<<"%"<<endl;
        cout<<"N "<<0<<"%"<<endl;
    }
    else
    {	cout<<"V "<<(int)(((float)(StableauCapteur[jour][HEURES][0][0]+0.0)/ StableauCapteur[jour][HEURES][0][COULEURS])*100)<<"%"<<endl;
        cout<<"J "<<(int)(((float)(StableauCapteur[jour][HEURES][0][1]+0.0)/ StableauCapteur[jour][HEURES][0][COULEURS])*100)<<"%"<<endl;
        cout<<"R "<<(int)(((float)(StableauCapteur[jour][HEURES][0][2]+0.0)/ StableauCapteur[jour][HEURES][0][COULEURS])*100)<<"%"<<endl;
        cout<<"N "<<(int)(((float)(StableauCapteur[jour][HEURES][0][3]+0.0)/ StableauCapteur[jour][HEURES][0][COULEURS])*100)<<"%"<<endl;
//On transforme en float pour que la division ai lieu corectement.
    }
}//----------Fin de STATS_D7


//------------------------------------------------- Surcharge d'opÈrateurs


//-------------------------------------------- Constructeurs - destructeur


Traffic::Traffic( )

{
    #ifdef MAP
    cout << "Appel au constructeur de traffic" << endl;
    #endif
    NBCapteur = 0 ;
    traffic = NULL;

    // on initialise le tableau contenant les valeurs decrivant les differents capteurs à zéro.
    for (int J =0 ; J<=JOURS; J++)
    {
        for (int H =0;H<=HEURES ;H++)
        {
            for (int M =0;M<=MINUTES; M++)
            {
                for (int C =0 ;C<=COULEURS; C++)
                {

                    StableauCapteur[J][H][M][C] = 0;

                 }
            }
        }
      }
    
} //----- Fin de Traffic


Traffic :: ~Traffic ( )

{
    #ifdef MAP
    cout << "Appel au destructeur de traffic " << endl;
    #endif

    Desallocation (traffic);
    traffic = NULL;

} //----- Fin de ~Traffic


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- MÈthodes protÈgÈes

//------------------------------------------------------- MÈthodes privÈes
Element * Traffic::CreationElement (int IDParametre )
{
    Element * element = new Element;
    element -> droite = NULL;
    element -> gauche = NULL;
    element -> capteur = new Capteur (IDParametre) ;
    NBCapteur ++;
    
    return element;
}
void Traffic::Desallocation (Element * &Tree)
{
        // Si l'arbre est null alors la récurence s'arrête inutile de descendre plus loin dans l'arbre.
        if(Tree == NULL )
        {
            return;
        }

        // déplacement vers la gauche de l'arbre si l'élément est present dans l'arbre.
        if(Tree->gauche != NULL)
        {
            Desallocation (Tree->gauche );
        }

        // déplacement vers la droite de l'arbre si l'élément est présent dans l'arbre.
        if(Tree-> droite != NULL)
        {
            Desallocation (Tree->droite);
        }
        // une fois qu'on parcourt l'abre en ligne, il est nécessaire de liberer la mémoire contenue dans capteur.
        // d'autre part chaque élément de l'arbre possède un pointeur de capteur, nous devons effectuer la libération de mémoire
        // de capteur avant de libérer la mémoire de l'élément de l'arbre  concerné
        delete Tree->capteur;
        delete  Tree;

 }

void Traffic::trafficRemplirTableau (int jour, int heure, int minute, int couleur )
{
    StableauCapteur[JOURS][0][0][couleur]++;
    StableauCapteur[JOURS][0][0][COULEURS]++;
    StableauCapteur[jour][HEURES][0][couleur]++;
    StableauCapteur[jour][HEURES][0][COULEURS]++;
    StableauCapteur[jour][heure][MINUTES][couleur]++;
    StableauCapteur[jour][heure][MINUTES][COULEURS]++;
    StableauCapteur[jour][heure][minute][couleur]++;
    StableauCapteur[jour][heure][minute][COULEURS]++;
}






