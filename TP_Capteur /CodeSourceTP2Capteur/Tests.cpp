# include <bits/stdc++.h>
 using namespace std ;

// Ceci est un exemple de programme utilisé pour généré des fichiers tests.
// Pour chaque nouveau tests nous implementons d'autres fichier .in permettant de verifier le bon fonctionnement du programme.

int main ()
{

    // On ouvre un fichier ou l'on redirige la sortie standard cout
    freopen("TestPerformance.in", "w+", stdout);

    for ( int j = 1; j < 20000000 ; j ++ )
    {

        cout << "ADD " << 1 << " "<< "2015 " << 7  << " "
         << 1 << " " <<  10 <<" "<< 1 <<" "
         << 1 <<" "<< 'N' << endl;
    }

    cout << "STATS_C"  << " " << 1 << endl;
    cout << "JAM_DH"   << " " << 1 << endl;
    cout << "STATS_D7" << " " << 1 << endl;
    cout << "EXIT"<< endl;
    fclose(stdout);
    return 0;
}
