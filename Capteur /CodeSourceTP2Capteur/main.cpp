# include <iostream>
# include <string>
# include "Traffic.h"
# include "Capteur.h"
#include <time.h>
using namespace std ;


int main ()
{

    /*float temps;
    clock_t t1, t2;
    t1 = clock();*/


    Traffic traffic;
    int ID,annee,mois,jour,heure,minute,d7 = 0;
    char couleur = ' ';
    int H_Start, H_end, NBSeg = 0;
    string nomCommande;
    cin >> nomCommande;

    // On gere les entrées et les sortie de notre programme, tant que l'entrée est differentes
    // de EXIT

    while (nomCommande != "EXIT")
    {
            if (nomCommande == "ADD")
            {
                int codeCouleur = 0;
                cin >> ID >> annee >> mois >> jour >> heure >> minute >> d7 >> couleur;
                codeCouleur = (couleur=='V') ? 0:codeCouleur ;
                codeCouleur = (couleur=='J') ? 1:codeCouleur ;
                codeCouleur = (couleur=='R') ? 2:codeCouleur ;
                codeCouleur = (couleur=='N') ? 3:codeCouleur ;
                traffic.AjouterElement ( ID, --d7, heure, minute, codeCouleur);

            }
            else if (nomCommande == "STATS_C")
            {
                cin >> ID;
                 //on recupere le capteur associé a l'ID
		if (traffic.RechercheElement(ID)!=NULL)
                {	(*traffic.RechercheElement(ID)).STAT_C();
		}
		else
		{	Capteur capteurtempo (-1);
			capteurtempo.STAT_C();
		}
            }
            else if (nomCommande == "JAM_DH")
            {
                cin >> d7;
                traffic.JAM_DH (d7-1);
            }
            else if (nomCommande == "STATS_D7")
            {
                cin >> d7;
                traffic.STATS_D7(d7-1);
            }
            else if (nomCommande == "OPT")
            {
                cin >> d7 >> H_Start >> H_end >> NBSeg;
                int seg [NBSeg];

                // On récupere dans un tableau les segments qui doivent étre traités pour résoudre le probleme du temps de trajet optimal
                for ( int i; i< NBSeg; i++)
                {
                    cin >> seg [i];
                }

                traffic.OPT(d7-1, H_Start, H_end, NBSeg, seg);
            }

       cin >> nomCommande;
      }


    /* t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    cout << "---------------------------------" << endl;
    cout <<  temps << endl;
    cout << "---------------------------------" << endl;
    */
	return 0;
}
