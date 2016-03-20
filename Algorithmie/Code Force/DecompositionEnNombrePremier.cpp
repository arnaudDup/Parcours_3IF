/* # include <iostream>
using namespace std;


int main ()
{
    int tableau2 [1000][2];
    long int compteur = 0;
    long long NBelements;
    cin >> NBelements;
    
    
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
            if (k % 2 == 0 || k % 3 == 0 || k % 7 == 0)
                k++;
        }
        compteur = k ;
        
    }
    
    
    for ( int i = 0 ; i > compteur ; i++)
    {
        cout << tableau2[i][0] << " ";
        cout << tableau2[i][1] << endl;
    }
    return 0;
} */