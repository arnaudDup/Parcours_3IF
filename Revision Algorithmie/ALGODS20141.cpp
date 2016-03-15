#include <iostream>
using namespace std; 

int main() {
    
    int nbEntierAtraiter = 0;
    cin >> nbEntierAtraiter;
    int nbEntierNegatif = 0;
    // Au maximum il y aura autant de nombre negatif
    int tableauEntier[nbEntierAtraiter];

    // on récupére seulement les nombre négatif dans un tableau
    for ( int i = 0; i< nbEntierAtraiter; i++)
    {
        int nbTraitrer = 0;
        cin >> nbTraitrer;

        if (nbTraitrer <= 0)
        {	
        	tableauEntier[nbEntierNegatif] = nbTraitrer;
        	nbEntierNegatif++ ;

        }
    }

    // il nous reste à traiter le tableau afin d'obtenir les resultats voulus. 
    if (nbEntierNegatif == 0)
    {
    	cout << "-" << endl;
        return 0;
    }

    else 
    {
    	int somme = 0; 
    	for ( int i = 0; i < nbEntierNegatif ; i++)
    	{
    		somme += tableauEntier[i];
    	}
    	// on affiche la moyenne.
    	cout << somme / nbEntierNegatif << endl;
    }

    return 0;
}