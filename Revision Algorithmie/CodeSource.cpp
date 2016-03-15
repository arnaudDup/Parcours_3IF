#include <iostream>
using namespace std; 


// fonction permettant d'afficher les valeurs dans un tableau. 
void afficherTableau (int* tab, int longueur)
{
	for(int i = 0; i < longueur ; i++)
	{
		cout << tab[i] << " | " ;
	}
}

// fonction permettant d'inserer  des valeurs en cin dans un tableau.
void inserervaleur ( int* tab, int longueur)
{
	// on lis les différents tableau pour obtenir 
	for(int i = 0; i < longueur; i++)
	{ 
		cin >> tab[i] ;
	}
}


// méthode permettant d'afficher un tableau 2D. 
const int longueur = 21;
int tab[longueur][longueur];
void affichertableau2D ()
{
	for(int i = 0; i < longueur; i++)
	{ 
		for(int j = 0; j < longueur; j++)
		{ 
			cout << tab[i][j] << "| ";
		}
		cout << endl; 
	}
}


int main () 
{
	int longueur; 
	cin >> longueur; 
	int tab [longueur]; 

	inserervaleur(tab,longueur);
	afficherTableau(tab,longueur);
	affichertableau2D(); 

	return 0;
}