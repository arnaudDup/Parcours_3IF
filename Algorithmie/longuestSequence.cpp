#include <iostream>
using namespace std;



void affichageTableau (int longueur, int tab[])
{
	for ( int i = 0; i < longueur ; i++)
	{
		cout << tab[i] << " " ;
	}
}


int longuestSequence (int longueur, int tab[])
{
	int sequence = 0;
	int tampon ; 
	// On construit la graphe avec un tableau 2D représentatn le graphe. 
	int tabReponse [longueur][longueur];

	// initialisation du tabeleau 2D.
	for ( int i= 0 ; i < longueur ; i++)
	{
		for( int j = 0 ; j < longueur; j++)
		{
			tabReponse[i][j] = 0;
		}
	}

	for ( int k = 0; k < longueur; k++)
	{
		tabReponse[k][longueur-1] = 1;
	}

	// Remplisage du tableau 
	for ( int i = 0; i < longueur ; i++)
	{
		tampon = 1;
		for( int j = i ; j >= 0; j-- )
		{
			if (tab[i] > tab[j])
			{
				tabReponse[i][j] = j+1;
				if (tampon <= tabReponse[j][longueur-1])
				{
					tabReponse[i][longueur-1] = tabReponse[j][longueur-1] + 1 ;
					tampon =  tabReponse[j][longueur-1] + 1 ;
				}
			}
		}	
	}
	
	// Affichage tableau 2D
	for ( int i= 0 ; i < longueur ; i++)
	{
		for( int j = 0 ; j < longueur; j++)
		{
			cout << tabReponse[i][j] << "| ";
		}
		cout << endl;
	}
	

	// recherche de la réponse au probleme. 
	for (int k = 0; k < longueur ; k++)
	{
	 	// en supposant ue les valeurs sont positives
		if (tabReponse[longueur-1][k] > sequence)
	 	{
	 		sequence = tabReponse[longueur-1][k];
	 	}

	}
	return sequence;

}
int main()
{
	int longueur;
	cin >> longueur;
	int tab [longueur];
	int tampon [longueur];
	float temps;
    clock_t t1, t2;

	// on remplit le tableau avec le données en entrées. 
	for (int i = 0; i < longueur ; i ++ )
	{
		cin >> tab[i];
		tampon[i] = tab [i];
	}

	affichageTableau(longueur, tab);
	cout << endl;
	cout << longuestSequence(longueur,tab) ;

	return 0;
}