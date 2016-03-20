# include <iostream>
# include <time.h>
using namespace std; 


// L'idée est de parcourir le tableau et trouve le plus petit element et 
// le mettre à l'indice d'avant et de se déplacer comme sa! 
// temps N^2 a eviter de préférence 
void TriParSelection (int longueur, int tab [])
{
	for ( int i = 0; i < longueur ; i++)
	{	
		int minimum = tab[i]; 
		int indice = i;

		// on trouve l'indice minimal, puis on échange 
		for ( int j = i; j < longueur ; j++)
		{
			if ( tab[j] < minimum)
			{
				indice = j; 
			}
		}

		// on échange à l'aide d'une valeur tampon. 
		int tampon = 0 ; 
		tampon = tab[i];
		tab [i] = tab[indice];
		tab[indice] = tampon; 
	}
}

// Identique a un joueur de carte.
// L'idée est de comparer une carte a inserer avec tous le reste du tableau.
void TriParInsertion (int longueur, int tab [])
{
	for ( int i = 1; i < longueur ; i++)
	{
		// on trouve l'indice minimal, puis on échange 
		for ( int j = i;  j > 0 ; j--)
		{
			if ( tab[j] < tab[j-1])
			{
				// alors j'échange
				int tampon = 0 ; 
				tampon = tab[j];
				tab[j] = tab[j-1];
				tab[j-1] = tampon; 
			}
		}
	}
}

// objectif : faire remonter les valeurs les plus grandes
// comme des bulles d'air.
void TriABulle (int longueur, int tab [])
{
 	for ( int i = 1; i < longueur ; i++)
	{
		// On trouve l'indice minimal, puis on échange 
		for ( int j = longueur - 1 ;  j >= i ; j--)
		{
			if ( tab[j] < tab[j-1])
			{
				int tampon = 0 ; 
				tampon = tab[j];
				tab[j] = tab[j-1];
				tab[j-1] = tampon; 
			}
		}
	} 
}


// QuickSort prendre les deux fonctions. 
// possible car passage de notre tableau par référence. 
int  partionner ( int debut, int longueur, int tab [])
{
	int pivot = tab [debut];
	int  i = debut -1 ;
	int  j = longueur ;
    int temp;

    // on part dans une boucle infini.
    while (1) 
    {
    		cout << j << "   " << i << endl;  
       		do
       		{
	            j--;
            } while (tab[j] > pivot);
	        
	        do{
	        	i++;
	        } while (tab[i] < pivot);
	        //cout << j << "   " << i << endl;
	        if (i < j) 
	        {
	            temp   = tab[i];
	            tab[i] = tab[j];
	            tab[j] = temp;
	        }

	        else
	        {
	            return j;
	        }
    }		
}

// condition d'arret de la récurence dés qu'il y a une seule case dans le tableau a traiter.  
void echanger(int tableau[], int a, int b)
{
    int temp = tableau[a];
    tableau[a] = tableau[b];
    tableau[b] = temp;
}

void quickSort(int tableau[], int debut, int fin)
{
    int gauche = debut-1;
    int droite = fin+1;
    const int pivot = tableau[debut];

    /* Si le tableau est de longueur nulle, il n'y a rien à faire. */
    if(debut >= fin)
        return;

    /* Sinon, on parcourt le tableau, une fois de droite à gauche, et une
       autre de gauche à droite, à la recherche d'éléments mal placés,
       que l'on permute. Si les deux parcours se croisent, on arrête. */
    while(1)
    {
        do droite--; while(tableau[droite] > pivot);
        do gauche++; while(tableau[gauche] < pivot);

        if(gauche < droite)
            echanger(tableau, gauche, droite);
        else break;
    }

    /* Maintenant, tous les éléments inférieurs au pivot sont avant ceux
       supérieurs au pivot. On a donc deux groupes de cases à trier. On utilise
       pour cela... la méthode quickSort elle-même ! */
    quickSort(tableau, debut, droite);
    quickSort(tableau, droite+1, fin);
}

void affichageTableau (int longueur, int tab[])
{
	for ( int i = 0; i < longueur ; i++)
	{
		cout << tab[i] << " " ;
	}
}

void remiseAuBonneValeur(int longueur, int tab[], int tampon[])
{
	for (int i = 0; i< longueur ; i++)
	{
		tab[i] = tampon[i];
	}
}

int main()
{	int longueur;
	cin >> longueur;
	int tab [longueur];
	int tampon [longueur];
	float temps;
    clock_t t1, t2;

	// on remplit le tableau avec le données en entrées. 
	for (int i = 0; i < longueur ; i ++ )
	{
		cin >> tab[i];
		tampon[i] = tab [i];
	}
 	
    t1 = clock();
    cout << "Résutlat du tri par Selection: " << endl; 
	TriParSelection (longueur,tab);
    t2 = clock();
    affichageTableau (longueur,tab);

    remiseAuBonneValeur( longueur,tab,tampon);

    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  	cout << endl  << "le temps d'éxecution de la méthode de tri par selection est de :" << endl;
  	cout << temps << endl;

  	t1 = clock();
    cout << "Résutlat du tri par Insertion: " << endl; 
	TriParInsertion (longueur,tab);
    t2 = clock();
    affichageTableau (longueur,tab);

    remiseAuBonneValeur( longueur,tab,tampon);

    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  	cout << endl  << "le temps d'éxecution de la méthode de tri par insertion est de :" << endl;
  	cout << temps << endl;

  	t1 = clock();
    cout << "Résutlat du tri à bulle: " << endl; 
	TriABulle (longueur,tab);
    t2 = clock();
    affichageTableau (longueur,tab);

    remiseAuBonneValeur( longueur,tab,tampon);

    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  	cout << endl  << "le temps d'éxecution de la méthode de tri à bulle est de :" << endl;
  	cout << temps << endl;

  	t1 = clock();
    cout << "Résutlat du tri QuickSort: " << endl; 
	quickSort (tab,0,longueur-1);
    t2 = clock();
    affichageTableau (longueur,tab);

    remiseAuBonneValeur( longueur,tab,tampon);

    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  	cout << endl  << "le temps d'éxecution de la méthode de tri QuickSort est de :" << endl;
  	cout << temps << endl;

	return 0;
}