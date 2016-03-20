#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "von_neumann.h"
#include "aes.h"
#include "mersenne_twister.h"

#define ARRAY_MAX_SIZE 1000




// Structures ----------------------------------------------------
// cette structure modelise une file d'attente
typedef struct file_Attente
{
	double *arrivee;
	int taille_arrivee;
	double *depart;
    double * departNONtrie;
	int taille_depart;
    
}file_attente;


// cette structure modélise une évolution au cours du temps
typedef struct evolution
{
	double *temps;
	double *nombre;
} evolution;


// Définitions  -------------------------------------------------
file_attente FileMM1 (double lambda, double mu, double D);
evolution showEvolution(file_attente file);
double Exponentielle (double lambda);
void quickSort(double tableau[], int debut, int fin);
double fmax  (double x, double y);
double fmin  (double x, double y);
double erfc  (double x);
void displayArray(double * tab, int tailleTab, char * filename);
double MoyennePersonne(double tab [] , double temps [], int taillMax );
double MoyenneTemps(double tabarrive [] , double tabDepart [], int taillMax, double Numerateur );

// Réalisations -------------------------------------------------

// Question 7 
evolution showEvolution(file_attente file)
{	
	// initialisation de la structure 
	evolution evo;	
	evo.nombre = (double*) malloc(sizeof(double)*ARRAY_MAX_SIZE);
	evo.temps = (double*) malloc(sizeof(double)*ARRAY_MAX_SIZE);
	
	// indice courants des deux tableaux
	int i =0; // cpt arrive
	int j =0; // cpt depart
	int cpt = 0;
	int nbCourantClient = 0;
    
	
	// quick sort du tab départ
	quickSort(file.depart, 0, file.taille_depart-1);
	
	// on itère jusqu'a la fin du tableau des arrivées
	while(i < file.taille_arrivee) // jusqua la dernière date
	{		
		double min = fmin(file.arrivee[i], file.depart[j]);
		
		if(file.arrivee[i] <= file.depart[j])
		{
			nbCourantClient++;
			i++;
		}
		else
		{
			nbCourantClient--;
			j++;
		}	
		
		// On ajoute les valeures courantes 
		evo.temps[cpt] = min;
		evo.nombre[cpt++] = nbCourantClient;
	}

	// on ajoutes les valeurs restantes du tableau de départ
	for(; j < file.taille_depart; j++)
	{
		// on décrémentes l'arrivée 
		nbCourantClient--;
				
		// On ajoute les valeures courantes 
		evo.temps[cpt] = file.depart[j];		
		evo.nombre[cpt++] = nbCourantClient;
	}
	
	return evo;
}

// Utile pour quicksort (tri)
void echanger(double tableau[], int a, int b)
{
    double temp = tableau[a];
    tableau[a] = tableau[b];
    tableau[b] = temp;
}

void quickSort(double tableau[], int debut, int fin)
{
    int gauche = debut-1;
    int droite = fin+1;
    const double pivot = tableau[debut];

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

// Question 6 lambda et mu correspondent respectivements aux nombres moyens d'arrivées et de départs par unité de temps
file_attente FileMM1 (double lambda, double mu, double D) // D = temps d'obeservation d'une chaîne
{
	// temps écoulé entre deux clients suit E(lambda), durée de réponse du serveur suis E(mu)
	file_attente resultat;
	
	// On crée deux tableaux
	resultat.arrivee = (double*) malloc(sizeof(double) * ARRAY_MAX_SIZE); // temps auquels arrive les clients
	resultat.depart = (double*) malloc(sizeof(double) * ARRAY_MAX_SIZE);  // temps auquels partent les clients
    resultat.departNONtrie = (double*) malloc(sizeof(double) * ARRAY_MAX_SIZE);  // temps auquels partent les clients
	resultat.taille_arrivee = 0;
	resultat.taille_depart = 0;
	
	// Gestion des arrivés -----
	double dateCourante = 0;
	double next;
	
	while (dateCourante <= D)
	{
		next = Exponentielle(lambda);
		dateCourante += next;
		resultat.arrivee[resultat.taille_arrivee] = dateCourante;
		resultat.taille_arrivee++;
	}
	
	// Calcul des départs ------
	
	// en partant du premier arrivé
	resultat.depart[0] = resultat.arrivee[0] + Exponentielle(mu); 
	resultat.taille_depart++;
	
	dateCourante = resultat.arrivee[0];
	
	int i;
	for(i = 1; i< resultat.taille_arrivee; i++)
	{
		if (resultat.depart[i-1] < resultat.arrivee[i]) // si 1 est parti
		{
			resultat.depart[i] = resultat.arrivee[i] + Exponentielle(mu); 
		}
		else // Si 1 est encore la
		{
			resultat.depart[i] = resultat.depart[i-1] + Exponentielle(mu); 
		}
		
		resultat.taille_depart++;
		//dateCourante = resultat.depart[i];
	}
    
    int p;
    for(p=0; p< resultat.taille_depart;p++)
    {
        resultat.departNONtrie[i] = resultat.depart[i];
    }

	return resultat;
}


// Methode permettant de récuperer les 4 bits de poids faible  du nombre placé en paramétre
unsigned int poidsFaible( unsigned int alea)
{
    return alea & 0x0F;
}

// Methode permettant de récuperer les 4 bits de poids fort du nombre placé en paramétre
unsigned int poidsFort(unsigned int alea)
{
    alea = alea >> 27;  		// attention il faut dÈcaler de 27 bit car randMax est sur 31 bits.
    return alea & 0x0F;
}

// Méthode permettant d'obtenir la somme des mots, -1 si le bit vaut 0 et +1 si le bit vaut 1
int sommeBit(unsigned long n, int nbBit)
{
    int i = 0;
    int s = 0;
    
    for(i = 0; i < nbBit; i++) // j'effectue le décalage un nombre de fois = à nbBit
    {
        if(n % 2 == 1) // si n est impair <=> BPfai = 1
        {
            s = s +1;
        }
        else
        {
            s = s -1;
        }
        
        // décalage
        n = n >> 1;
    }
    
    return s;
}

// Réponse à la auestion 3.1    loi uniforme [0,1]
double Alea ()
{
    struct mt19937p mt;
    int tmp = rand();
    sgenrand(time(NULL)+(tmp), &mt);
    unsigned long nbAlea = genrand(&mt);    // Nous utilisons Mersenne-Twister pour générer une loi uniforme sur [0,N]
    double res = (double) nbAlea / (double) (pow(2,32) - 1); // Nous obtenon un nombre sur [0,1], le nombre maximale est de 15
    return res;
    
}

// Réponse à la question 3.2 Simultation de la loi exponentielle
double Exponentielle (double lambda)
{
    double u = Alea();
    
    //double res = 1 - exp(lambda * u);
    double res = - log (1-u)/lambda;
    return res;
}



// La méthode Reduction permet de ramener le nombre sur un intervalle de [0,1].
double Reduction (int nbdebit, unsigned int numerateur)
{
    
    double res = numerateur / ( pow(2,nbdebit) - 1); // nombre que l'on va diviser par le nombre maximal que l'on peut obtenir sur le nb de bit placé en paramétre.
    
    return res;
}


// La méthode ReductionLong permet de ramener le nombre sur un intervalle de [0,1].
double ReductionLong (int nbdebit, unsigned long numerateur)
{
    return numerateur / pow(2,nbdebit);
    
}


// Methode permettant de parcourir un tableau et de transformer l'ensemble des valeurs sur l'ensemble [0,1]
void Generation_uniforme_0_1 (int nbdebit, unsigned int tabARecuperer [1024], double tabARemplir [1024])
{
    for (int i = 0; i< 1024 ; i++)
    {
        tabARemplir [i] = Reduction (nbdebit,tabARecuperer[i]);
    }
    
}

// Methode permettant de parcourir un tableau et de transformer l'ensemble des valeurs sur l'ensemble [0,1]
void Generation_uniforme_long_0_1 (int nbdebit, unsigned long tabARecuperer [1024], double tabARemplir [1024])
{
    for (int i = 0; i< 1024 ; i++)
    {
        tabARemplir [i] = ReductionLong (nbdebit,tabARecuperer[i]);
    }
    
}

// Méthode permettant de sommer les bits d'une séquence placé en paramétre.
int SommeDesBitsRun(unsigned int n, int nbBit , int* indexCur, int* sequence)
{
    int i = 0;
    int somme = 0;
    int bitCur;
    
    for(i = 0; i < nbBit; i++)
    {
        
        if(n % 2 == 1) // si n est impair <=> BPfai = 1
        {
            somme += 1;
            bitCur = 1;
        }
        else          // si le nombre est paire alors son dernier bit est égale à 0.
        {
            bitCur = 0;
        }
        
        sequence[*indexCur] = bitCur;
        n = n >> 1;
        (*indexCur)++;
    }
    
    return somme;
}

// Méthode permettant de sommer les bits d'une séquence placé en paramétre.
int SommeDesBitsRunLong(unsigned long nombre, int nbBit , int* indexCur, int* sequence)
{
    int i = 0;
    int somme = 0;
    int bitCur;
    
    for(i = 0; i < nbBit; i++)
    {
        
        if(nombre % 2 == 1) // si n est impair <=> BPfai = 1
        {
            somme += 1;
            bitCur = 1;
        }
        else                // si le nombre est paire alors son dernier bit est égale à 0.
        {
            bitCur = 0;
        }
        
        sequence[*indexCur] = bitCur;
        nombre = nombre >> 1;
        (*indexCur)++;
    }
    
    return somme;
}

int SommeRk(int * n, int nbBit);


// Permettant de répondre à la question 2.3
double Runs(int nbValeurs, unsigned int * tabValeurs, int nbDigit)
{
	int somme = 0;
	int i;	
	double Vn = 0;
    double temp = 0;
    
	int nbVal = (nbValeurs * nbDigit);
	int * sequence = (int*) malloc (nbVal*sizeof(int));
	int indiceCur = 0;
	
	// Somme des 1
	for(i = 0; i < nbValeurs; i++)
	{
		somme += SommeDesBitsRun(tabValeurs[i], nbDigit, &indiceCur, sequence);
	}
    
	double p = (double) somme / nbVal;          // création du nombre pi;
    
    
    temp = (p - 0.5); // attention 1/2 ne fonctionne pas.

    if( fabs( temp ) >= 2 / (double) sqrt(nbVal))
    {
		return 0.0;
    }
    
    // on cacule la séquence des différents Rk
	Vn = SommeRk(sequence, nbVal)+1;
	
	// On effectue la division donnée dans l'énoncé.
	double num =  (double) fabs( Vn-2*nbVal*p*(1-p) );
	double dem =  (double) 2*sqrt(2*nbVal) * p*(1-p) ;           
	double res =  (double) erfc(  num / dem ) ;
    
    free (sequence);                                             // libération de la mémoire.
    
	return res;
}




// Permettant de répondre à la question 2.3
double RunsLong(int nbValeurs, unsigned long * tabValeurs, int nbDigit)
{
    int somme = 0;
    int i;
    double Vn = 0;
    
    int nbVal = (nbValeurs*nbDigit);
    int * sequence = (int*) malloc (nbVal* sizeof(int));
    int indiceCur = 0;
    
    // Somme des 1
    for(i = 0; i < nbValeurs; i++)
    {
        somme += SommeDesBitsRunLong(tabValeurs[i], nbDigit, &indiceCur, sequence);

    }
    
    double p = (double) somme / (double) nbVal; // création du nombre p;
    
    double temp = p - 0.5;
    
    if( fabs(temp) >= 2/ (double) sqrt(nbVal))
    {
        return 0.0;
    }
    
    // on cacule la séquence des différents Rk
    Vn = SommeRk(sequence, nbVal)+1;
    
    // On effectue la division donnée dans l'énoncé.
    double num =  (double) fabs( Vn-2*nbVal*p*(1-p) );
    double dem =  (double) 2*sqrt(2*nbVal) * p*(1-p) ;            // nous obtenons 0,15 voir avec la prof pourquoi ?
    double res =  (double) erfc(  num / dem ) ;
    
    free (sequence);
    
    return res;
}

// Méthode permettant de calculer le Rk utile à la question 2.3
int SommeRk(int * n, int nbBit)
{
	//si cur = suivante, return 1
	int somme = 0;
	int i;
	int bitCur, bitSuiv;
				
	bitCur = n[0];
	
	for(i = 1; i < nbBit; i++)
	{
		// on récupère le bit suivant

		bitSuiv = n[i];  
        if( bitCur != bitSuiv) // on le compare avec le bit précedent. 
			somme += 1;
		
		bitCur = bitSuiv;		
	}
		
	return somme;	
}

// Méthode perttant l'affichage des resultats proprement. 
void testValeur(double valeur)
{
    if (valeur > 0.01)
    {
        printf("Le test est concluant\n\n");
    }
    
    else
    {
        printf("Le test est non concluant\n\n");
        
    }
}

// Méthode permettant de répondre à la question 2.2
double Frequency(int nbValeurs, unsigned int * tabValeurs, int nbDigit)
{
	int somme = 0;
	int i;
	
	for(i = 0; i < nbValeurs; i++)
	{
		somme += sommeBit(tabValeurs[i], nbDigit);        // calcule de la somme des bits
	}
	
	double res = fabs((double)somme) / (double)sqrt(nbValeurs*nbDigit);
	return (double) erfc(res/(double)sqrt(2));     // calcule de Pvaleur
}

// Méthode permettant de répondre à la question 2.2
double FrequencyLongInt (int nbValeurs, unsigned long * tabValeurs, int nbDigit)
{
    int somme = 0;
    int i;
    
    for(i = 0; i < nbValeurs; i++)
    {
        somme += sommeBit(tabValeurs[i], nbDigit);      // calcule de la somme des bits
    }
    
    double res = fabs((double)somme) / (double)sqrt(nbValeurs*nbDigit);
    return (double) erfc(res/(double)sqrt(2));  // calcule de Pvaleur
}


int rdtsc()
{
	// cette fonction cree un warning : c'est normal.
	__asm__ __volatile__("rdtsc");
	
	return 0;
}


int main()
{
	word16 x=1111; // nombre entre 1000 et 9999 pour Von Neumann
	struct mt19937p mt; // Pour Mersenne-Twister
	int tmp = rand(); // Pour Mersenne-Twister
	u32 Kx[NK], Kex[NB*NR], Px[NB]; // pour l'AES

	int output_rand; // sortie du rand du C
	

	// initialisation des graines des generateurs
	srand(rdtsc());  // rand du C 
	sgenrand(time(NULL)+(tmp), &mt); // Mersenne-Twister
	// Initialisation de la clé et du plaintext pour l'AES 
	// 45 est un paramètre qui doit changer à chaque initialisation
	init_rand(Kx, Px, NK, NB, 45);
	KeyExpansion(Kex,Kx); // AES : sous-clefs


	
	// Tableaux resultat suivant la loi uniforme sur [O,N] ou N est le nombre de bit
	unsigned int VN_Tab[1024];
	unsigned long Mersenne_Tab[1024];
    unsigned int rand_Pfaible[1024];
    unsigned int rand_Pfort[1024];
	unsigned int AES_Tab[1024];

    // Tableaux resultat suivant la loi uniforme sur [O,1]
    double VN_Tab_Uniforme_0_1[1024];
    double Mersenne_Tab_Uniforme_0_1[1024];
    double rand_Pfaible_Uniforme_0_1[1024];
    double rand_Pfort_Uniforme_0_1[1024];
    double AES_Tab_Uniforme_0_1[1024];


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// partie 2.1 Partie visuel

	// affichage et remplissage des tableaux
	//printf("- Generation de nombres aleatoires -\n");
	int i = 0;
	//FILE *fp;
	//fp = freopen("aes.txt", "w+", stdout);	// permet la redirection de flux permettant l'ouverture et l'écriture de fichier.
	for ( i = 0; i < 1024 ; i++)
	{
        output_rand = rand();
        
        //printf("hasard  = %d\n", output_rand);
        
        rand_Pfaible[i] = poidsFaible(output_rand);
        //printf("%u\t",rand_Pfaible[i]);
        
        rand_Pfort[i] = poidsFort(output_rand);
        //printf("%u\t",rand_Pfort[i]);
		
        VN_Tab[i] = Von_Neumann(&x);
		//printf("%u\t",VN_Tab[i]);
		
        Mersenne_Tab[i] = genrand(&mt);
		//printf("%lu\t",Mersenne_Tab[i]);
		
        AES_Tab[i] = AES(Px, Kex);
		//printf("%u\t",AES_Tab[i]);
	}

    //fclose(fp);
    
	
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// partie 2.2 frequence monobit
    
    printf("\n\n\nPartie 2.2 ----------------------------------\n");
	
    double Sobs_rand_Pfaible = Frequency(1024, rand_Pfaible, 4); // methode pour la methode rand de bit de poids faible.
    
    printf("Pvaleur rand Poids faible  = %f\n", Sobs_rand_Pfaible);
    
    double Sobs_rand_Pfort = Frequency(1024, rand_Pfort, 4); // méthode pour la méthode rand de bit de poids fort.
    
    printf("Pvaleur rand poids fort  = %f\n", Sobs_rand_Pfort );
    
    double Sobs_AES = Frequency(1024, AES_Tab, 32); // AES
    
    printf("Pvaleur AES = %f\n", Sobs_AES);
    
    double Sobs_VN = Frequency(1024, VN_Tab, 16); // VN
    
    printf("Pvaleur VN = %f\n", Sobs_VN);
    
    double Sobs_Mersenne = FrequencyLongInt(1024, Mersenne_Tab, 32 /* ( sizeof(unsigned long)*8 */ ) ; // MT
    
    printf("Pvaleur Mersenne = %f\n", Sobs_Mersenne);
    

    
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Partie 2.3 Runs
    
    printf("\n\nPartie 2.3 ----------------------------------\n");
	
    double Run_rand_Pfaible = Runs (1024, rand_Pfaible, 4); // methode pour la methode rand de bit de poids faible.
    
    printf("Run rand Poids faible  = %f\n", Run_rand_Pfaible);
    
    testValeur(Run_rand_Pfaible);
    
    double Run_rand_Pfort = Runs (1024, rand_Pfort, 4); // méthode pour la méthode rand de bit de poids fort.
    
    printf("Run rand poids fort  = %f\n", Run_rand_Pfort );
    
    testValeur(Run_rand_Pfort);
    
    double Run_AES = Runs (1024, AES_Tab, 32); // AES
    
    printf("Run AES = %f\n", Run_AES);
    
    testValeur(Run_AES);
    
    double Run_VN = Runs (1024, VN_Tab, 16); // VN
    
    printf("Run VN = %f\n", Run_VN);
    
    testValeur(Run_VN);
    
    double Run_Mersenne = RunsLong(1024, Mersenne_Tab, 32 /*(sizeof(unsigned long)*8) */); // MT
    
    printf("Run Mersenne = %f\n", Run_Mersenne);
    
    testValeur(Run_Mersenne);
    
    
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Partie 3.1 Loi uniforme
    
    printf("\n\nPartie 3.1 ----------------------------------\n");
    Generation_uniforme_0_1 (4, rand_Pfaible , rand_Pfaible_Uniforme_0_1);
    Generation_uniforme_0_1 (4, rand_Pfort, rand_Pfort_Uniforme_0_1);
    Generation_uniforme_long_0_1  (32 , Mersenne_Tab, Mersenne_Tab_Uniforme_0_1);
    Generation_uniforme_0_1 (32, AES_Tab, AES_Tab_Uniforme_0_1);
    Generation_uniforme_0_1 (16, VN_Tab,VN_Tab_Uniforme_0_1);
    
    printf ("nombre aleatoire générer par la méthode Alea() = %f  \n" , Alea () );
    
    
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Partie 3.2
    printf("\nPartie 3.2 ----------------------------------\n");
    printf ("nombre aleatoire générer par la méthode Exponentielle() = %f  \n" , Exponentielle(1) );
    
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Partie 3.3


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Partie 4 File d'attente MME

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Question 6/7

	printf("\n\nPartie 4 ----------------------------------\n");
 
	file_attente file = FileMM1 (0.2, (double) 1/3, 180);
	
	evolution evo = showEvolution(file);
	
	int taille = file.taille_arrivee*2;
		
	// ecriture sur les fichiers
	displayArray(evo.temps, taille, "temps.txt");
	displayArray(file.depart, taille/2, "dep.txt");
	displayArray(file.arrivee, taille/2, "arrivee.txt");
	displayArray(evo.nombre, taille, "nombre.txt");

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Question 8
	printf("la moyenne des personnes est de = %f \n",MoyennePersonne(evo.nombre,evo.temps,taille));
    
	printf("le temps d'attente = %f \n", MoyenneTemps (file.arrivee , file.departNONtrie, file.taille_arrivee , evo.temps[taille-1]));
	
	return 0;
}

void displayArray(double * tab, int tailleTab, char * filename)
{
	FILE * fic  = NULL;
	fic = fopen (filename, "w+");
	int i;
	
	for(i = 0; i< tailleTab; i++)
	{
		fprintf(fic, "%f\n",tab[i]);
	}
	
	fclose(fic);
}

double MoyennePersonne(double compte [] , double temps [], int taillMax )
{
	double somme = 0.0;
	double moyenne = 0.0;
	int i; 
	for ( i = 1; i < taillMax ;  i++)
	{
		somme += compte [i-1] * (temps[i]-temps[i-1]);	// on calcule la moyenne des personnes présentes dans les files d'attentes,
													// cette moyenne est une moyenne pondéré. 
	}
    
    moyenne = (double)somme / temps[taillMax-1];
	return moyenne; 
}

double MoyenneTemps(double tabarrive [] , double tabDepart [], int taillMax, double Numerateur)
{
	double res = 0.0;
	double moy = 0.0;
	int i; 
	for ( i = 0 ; i < taillMax ;  i++)
	{
		res += (tabarrive[i] - tabDepart[i] );	// on soustrait le temps passe dans la file d'attente.
	}

	moy = (double) res / Numerateur;			// on le divise par le temps totale passé dans les files d'attentes.
	return moy;
}


