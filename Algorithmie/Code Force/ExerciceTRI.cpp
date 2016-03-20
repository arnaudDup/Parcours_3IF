# include <iostream>
using namespace std;

int tableau2 [9];
void tri (int longueur);
int Tampon [100];
int main ()
{
    int * tab = new int [9];
    for (int i = 0; i < 9; i++)
    {
        int entier;
        cin >> entier;
        tab[i] = entier;
    }
    tri (*tab);
    return 0;
}
void tri (int * tab)
{
    int somme = 0;

    for (int v = 0; v < 3; v++ )
    {
        int max = 0;
        int indice = 0; ;
        char * reponse = new char [9];
        for (int i = 0; i < 9; i++)
        {
            if( tab[i] > max )
            {
                max = tab[i];
                indice = i;
            }
        }
        int quelleCouleur = indice % 3;
        if (quelleCouleur == 0)
            reponse[indice] = 'B';
        if (quelleCouleur == 1)
            reponse[indice] = 'G';
        if (quelleCouleur == 2)
            reponse[indice] = 'C';
    
        for (int i = 0; i < 9; i++)
        {
            if( i % indice ==  quelleCouleur )
            {
                if (i != indice )
                {
                    somme += tab[i];
                    tab[i] = 0;
                }
                else
                tab[i] = 0;
            }
        }
    }
    
}