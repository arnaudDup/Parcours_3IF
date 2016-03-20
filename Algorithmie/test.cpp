#include <iostream>
#include <stdlib.h>
using namespace std; 

float compare (float a, float b)
{
    if ((a - b) > 0)
        return (a - b);
    else 
        return (b - a);

}

float lisage ( float *tab, int longueur)
{
    float diff = 0;
    float entier; 
    for (int i=0; i< longueur; i++ )
    {
        float entier = tab[0];
        float moyenne = 0;
        if( i != 0 && i != longueur-1)
        {
            moyenne = (entier + tab[longueur-1])/2 ;
            entier = tab[i];
            tab[i] = moyenne; 
            if (compare(tab[i-1],tab[i]) > diff )
            {
                diff = abs(tab[i-1]-tab[i]);
            }
        } 
    }
    return diff;
}

void affichage ( int *tab, int longueur)
{
    for (int i=0; i<longueur; i++)
    {
        cout << tab[i] << "| " ;
    }
}
int main ()
{
    int mesure;
    float diff; 
    int nbtours = 0;
    float delta = diff + 1;
    cin >> mesure >> diff; 
    cout << mesure << diff << endl; 
    float tab1[mesure]; 
     
    
    for (int i=0; i< mesure; i++ )
    {
        float temp; 
        cin >> temp; 
        tab1[i] = temp; 
    }
     affichage(tab1, mesure);
    while (delta > diff )
    {
        nbtours++;
        delta = lisage(tab1, mesure);
        //affichage(tab1, mesure);
    }

    cout << nbtours << endl;

    return 0; 
}