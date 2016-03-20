/* #include <iostream>
using namespace std;
int main ()
{
    int PrixBannane;
    int Monnaie;
    int cbBannes;
    
    
    cin >> PrixBannane >> Monnaie >> cbBannes;
    int decompte = PrixBannane;
    for (int i = 2; i <= cbBannes ; i++)
    {
        PrixBannane += i*decompte;
        
    }
    
    
    if ( PrixBannane > Monnaie)
        cout << (PrixBannane-Monnaie);
    else
        cout << 0 ;
    
    return 0;
} */