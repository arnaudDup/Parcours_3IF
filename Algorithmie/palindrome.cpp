#include <iostream>
using namespace std; 

int  tableau [1000];

bool TestPalindrome (int compteur) 
{
	bool verif = true; 
	for ( int i = 0 ; i < (compteur/2) +1; i++)
	{	
		if (tableau[i] != tableau[compteur-1-i])
		{
			verif = false; 
			return verif; 
		}

	}

	
	return verif;
}

int main () 
{
	int compteur = 0; 
	// on remplit le tableau
	for (int i = 0; i < 1000; i++)
	{
		compteur = i ; 
		int entier = 0; 
		cin >> entier; 
		if ( entier == -1)
		{
			// le tableau est rempli 
			break; 
		}
		else
		{
			tableau[i] = entier; 
		}

	}

	cout << (TestPalindrome(compteur) == true ?"1":"0") << endl;

	return 0;
}