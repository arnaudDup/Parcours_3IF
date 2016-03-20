# include <iostream>
# include <string>
# include <algorithm>

using namespace std;

//const int TAILLE = 10;

class Personne
{
    public :
    void afficher () const
    {
        cout << "nom = " << nom << endl;
    }
    
    Personne (char* Lenom)
    {
        nom = Lenom;
    }
    
protected:
    char* nom;
};

int main ()
{
    int * UnNom = new int [];
    int a = 40;
    * UnNom = 2;
    cout << *UnNom << endl;
    return 0;
}


