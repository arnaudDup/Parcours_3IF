#include <iostream>
#include <string>
using namespace std; 

int main()
{
	string stringAtraiter;
	cin >> stringAtraiter;

	// on créer le tableau qui va nous servir pour comparer les diférentes chaine de caratére.
	string tablauDeChaine [24];
	// tableau nous servant a connaitre le nombre d'itérations 
	int tableauDeReference [24];
	// entier nous servant a connaitre la nombre d'itérations 
	int nbIterations = 0; 

	if (stringAtraiter == " ")
	{
		cout << " " << endl;  
	}
	// on boucle pour le traitement de la chaine de caractére. 
	for (int i = 0; i < stringAtraiter.size() ; i += 3 )
	{
		if (i != 0)
		{
			// on évite le traitement du tiret. 
			i++;
		}

		string ChaineAinserer = ""; 
		ChaineAinserer += stringAtraiter[i];
		ChaineAinserer += stringAtraiter[i+1];
		ChaineAinserer += stringAtraiter[i+2];

		for ( int j = 0; j < nbIterations ; j++ )
		{
			if (ChaineAinserer.compare(tablauDeChaine[j]) == 0)
			{	
				tableauDeReference[j] ++;
				break; 
			}
		}

		// si la chaine n'existe pas alors nous l'insérons dans notre tableau que nous allons de chaine a traiter
		tablauDeChaine[nbIterations] = ChaineAinserer;
		tableauDeReference[nbIterations] = 1;
		nbIterations++; 
	}	

	// onrecherche le maximu de notre tableau et on affcihe le resultat 
	int maximum = -1;
	int nbdemax = 0;
	int indice [24];
	for (int i = 0; i < 24; i++)
	{
		if (tableauDeReference[i] > maximum)
		{
			for (int j = 0; j < nbdemax ; j++ )
			{
				indice[j] = 0; 
			}
			nbdemax = 0;
			indice[nbdemax] = i; 
			maximum = tableauDeReference[i];
			nbdemax ++;
			
		}

		else if( tableauDeReference[i] == maximum )
		{	
			indice[nbdemax] = i;
			nbdemax ++;

		}
	}
	cout << maximum << "\r\n";

    // Il nous reste à trier et construire le tableau de réponse par ordre alphabetique.
    // 
    string tableauReponse [24];
    for (int k = 0; k < nbdemax ; k++)
    {
        tableauReponse[k] = tablauDeChaine[indice[k]];
    }

    // effectuons un trie à bulle.
    for ( int i = 1; i < nbdemax ; i++)
    {
        // On trouve l'indice minimal, puis on échange
        for ( int j = nbdemax - 1 ;  j >= i ; j--)
        {
            if ( tableauReponse[j] < tableauReponse[j-1])
            {
                string tampon = " ";
                tampon = tableauReponse[j];
                tableauReponse[j] = tableauReponse[j-1];
                tableauReponse[j-1] = tampon;
            }
        }
    }
	for (int i = 0; i < nbdemax ; i++)
	{
		cout << tableauReponse[i] << "\r\n"; 
	}
	return 0;  
}