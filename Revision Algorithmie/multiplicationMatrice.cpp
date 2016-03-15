# include <iostream>
using namespace std; 

int main()
{
	// récupération matrice
	int longueur = 0;
	int largeur = 0;
	cout << "veuillez rentrer les valeurs de longueur et largeur de votre premiére matrice" << endl; 
  	cin >> longueur >> largeur ; 
  	int tab1[longueur][largeur];

  	cout << "commencez a rentrer les valeurs de la premiere matrice" << endl;
  	for (int i = 0; i< longueur ; i++)
  	{
  		for (int j = 0; j< largeur; j++)
  		{
  			cin >> tab1[i][j];
  		}
  	}

  	cout << "la premiere matrice est fini, nous commençons la seconde" << endl; 

  	int tab2[largeur][longueur];

  	for (int i = 0; i< largeur; i++)
  	{
  		for (int j = 0; j< longueur; j++)
  		{
  			cin >> tab2[i][j];
  		}
  	}

  	// Affichage des deux tableaux 2D

  	cout << "affichage de la premiere matrice " << endl;
	for ( int i= 0 ; i < longueur ; i++)
	{
		for( int j = 0 ; j < largeur; j++)
		{
			cout << tab1[i][j] << "| ";
		}
		cout << endl;
	}

	cout << "affichage de la seconde matrice " << endl;
	
	for ( int i= 0 ; i < largeur; i++)
	{
		for( int j = 0 ; j < longueur; j++)
		{
			cout << tab2[i][j] << "| ";
		}
		cout << endl;
	}

	// mutiplication des matrices
	int tableauRéponse[largeur][largeur];
	for (int i = 0; i < largeur; i++)
	{
		for (int k =0; k < largeur; k++)
		{
			int somme = 0;
			for (int j = 0; j < largeur; j++)
			{
				somme += tab1[i][j]*tab2[j][k];
				cout << "tab1[i][j]*tab2[j][i]:  " << tab1[i][j]*tab2[j][i] <<" pour i  "  << i << endl;
			}
			tableauRéponse[i][k] = somme;
		}
	}

	cout << "la solution au produit des matrices est la suivante "  << endl;

	// affichage de la sollution 
	for ( int i= 0 ; i < largeur; i++)
	{
		for( int j = 0 ; j < largeurq; j++)
		{
			cout << tableauRéponse[i][j] << "| ";
		}
		cout << endl;
	}


	return 0;
}
