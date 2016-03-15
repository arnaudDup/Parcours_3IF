/*# include <iostream>
using namespace std;


int main ()
{
    int tableau1 [1000000];
    int tableau2 [1000][2];
    long int compteur = 0;
    long long NBelements;
    cin >> NBelements;
    if (NBelements == 1)
    {
        cout << 1;
        return 0;
    }
    tableau1 [0] = 1;
    int k = 2;
    int puissance = 1;
    while (k < NBelements)
    {
        
        if (NBelements % k == 0)
        {
            tableau2 [compteur][0] = k;
            tableau2 [compteur][1] = puissance;
            puissance ++;
            NBelements = NBelements / k ;
        }
        else
        {
            k++;
            puissance = 1;
        }
        compteur = k ;
        
    }
    for ( int i = 0 ; i > compteur ; i++)
    {
        cout << tableau2[i][0] << " ";
        cout << tableau2[i][1] << endl;
    }


    
    int testSortie = 0;
    compteur --;
    
    
    for ( long int i = compteur ; i > 0 ; i--)
    {
        testSortie = 0;
        int nbetudie = tableau [i] ;
        int diviseur = 0;
        for ( long int j = 1; j <= i ; j++)
        {
            diviseur = tableau[j] * tableau[j];
            if (diviseur <= nbetudie)
            {
            
                if ( nbetudie % diviseur  == 0 )
                {
                    testSortie++;
                    break;
                
                }
            }
        }
        
        if (testSortie == 0)
        {
            cout << tableau[i];
            break;
        }
    }
 
    
    return 0;
}*/