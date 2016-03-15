#include <iostream>
using namespace std;

int main()
{
    int entier;
    cin >> entier;
    int tab [entier+1][entier+1];

    // initialisation du tableau réponse. 
    for ( int i = 0; i < entier+1; i++)
    {
        for ( int j = 0 ; j < entier+1; j++)
        {
            tab [i][j] = 0;
        }
    }

    // on passe par un graphe aplatie pour la sollution --> tableau 2D:
    // ligne = noeud 
    // colonne = arcss possibles a partir d'un arce du graphe. 
    // on représente toutes les chemins possibles. 
    for ( int i = 0; i < entier; i++)
    {
        for ( int j = i; j < entier; j++)
        {
            
            if (i == j || tab [i][j] != 0)
            {   
                // Le cas ou i = 0 il faut lui faire -1 et tester si celui ci est entier est divisible par 2 ou 3 pas traité par la suite.
                // on initialise la premiere ligne du tableau sur laquelle on va s'appuyer tous le programme.
                if ( i == 0 )
                {
                    tab [i+1][j+1] = 1;
                    if ( entier % 3 == 0)
                    {
                       tab [i+1][entier-entier/3] = 1;
                    }
                    if ( entier % 2 == 0)
                    {
                         tab [i+1][entier-entier/2] = 1;
                    }
                }

                else
                {
                    // toujours vrai car l'opération -1 est toujours possible.
                    tab [i+1][j+1] = tab[i][j]+1;
                }
            }

            // on construit le tableau en fonction de la premiere ligne construite. 
            if (tab[i][j] != 0 )
            {
                // Je simule le % 2
                if ((entier - j) % 2 == 0)
                {
                       tab [i+1][entier-(entier-j)/2] = i+1;
                }

                // Je simule % 3
                if ( (entier - j) % 3 == 0)
                {
                       tab [i+1][entier-(entier-j)/3] = i+1;
                }
             }
        }
    }

    for ( int i = 0; i < entier+1; i++)
    {
        for ( int j = 0; j < entier+1; j++)
        {
            cout << tab[i][j] << " | " ;
        }
        cout << endl; 
    }

    // recherche et affichage de la sollution.
    for ( int i = 0; i < entier+1 ; i++ )
    {
        if (tab [i][entier] != 0)
        {
            cout << tab [i][entier] << endl << endl << endl ;
            return 0;
        }
    }
}
