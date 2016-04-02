#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;


int main ()
{
    vector<double> a;
    
    // getting data useful for the application.
    int longueur = 0;
    cin >> longueur;
    double res = 0;
    
    for (int i = 0; i < longueur; i ++ )
    {
        double entier;
        cin >> entier;
        a.push_back (entier);
        res += (entier/100);
    }
    
    cout << setprecision(16) << ((res / a.size())*100) << endl;
    
    
    return 0;
}