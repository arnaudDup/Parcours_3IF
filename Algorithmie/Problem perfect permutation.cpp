#include <iostream>
# include <utility>
using namespace std;
int Tableau [101];
int main ()
{
    int NombreEntier;
    int DEJAFAIT = 0;
    
    
    cin >> NombreEntier;
    
  
    
    for (int i = 0; i < NombreEntier ; i++)
    {
        Tableau[i] = i+1;
        
    }
    

    if ( NombreEntier % 2 == 0)
    {
        for (int i = 0; i < NombreEntier ; i++)
        {
            swap(Tableau[i],Tableau[i+1]);
            i++;
        }
        DEJAFAIT ++;
    }
    else if ( NombreEntier % 3 == 2 )
    {
        for (int i = 0; i < NombreEntier - 2 ; i++)
        {
            swap(Tableau[i],Tableau[i+1]);
            swap(Tableau[i+1],Tableau[i+2]);
            i= i+2;
        }
        swap(Tableau[NombreEntier-2],Tableau[NombreEntier-1]);
    }
    else if ( NombreEntier % 3 == 0  && DEJAFAIT == 0)
    {
        for (int i = 0; i < NombreEntier - 2 ; i++)
        {
            swap(Tableau[i],Tableau[i+1]);
            swap(Tableau[i+1],Tableau[i+2]);
            i= i+2;
        }
        
    }

    else
    {
       cout << -1;
       return 0;
    }

    for (int i = 0; i < NombreEntier ; i++)
    {
        cout << Tableau[i] << " ";
        
    }
    
    return 0;
}