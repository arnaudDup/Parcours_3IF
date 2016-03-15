//------------------------------------------------------------------------------//
//        "ChainedMatrix.cpp"
//
// Programme montrant l'application de la programmation dynamique.
// Problème de la multiplication matricielle enchaînée. Il faut trouver le 
// parenthésage optimal qui multiplie les matrices [A1 x A2 x...x An] de manière 
// à nous donner un coût optimal. C'est à dire minimisant le nombre de produits
// scalaires.
//------------------------------------------------------------------------------//

// Rappel Mathématique :
//
// [0]
// Par convention dans notre produit matricielle enchaîné
// on dira qu'une matrice Ai est de dimension pi-1 x pi
//
// [1]
// Multiplier une matrice A de dimension p x q 
// avec une matrice B de dimension q x r 
// donne une matrice C de dimension p x r
//
// [2]
// Le temps de calcul de C (= le coût) est déterminé par le nombre 
// de multiplications scalaires nécessaires pour 'remplir' C 
// = p x q x r

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

void PrintArray(int* * tabToPrint,int size);
void RemplirTableau(int* dim, int size);
void Afficher_Parenthesage_Optimal(int * * S, int i, int j);

//-----------------------------------------------------------------------------
// Name : RemplirTableau
// Parameter : Les dimensions des matrices
// Desc : Cette fonction va déterminer le nombre optimal de multiplications
// scalaires nécessaires pour calculer le produit d'une suite de matrices.
// On se base sur la fonction récursive suivante
//
//          | 0     si i=j
// m[i,j] = |
//          | min { m[i,k] + m[k+1,j] + pi-1 x pk x pj 
// 
// On remplit le tableau M des valeurs optimales. Le tableau S, contient 
// la valeur de k tel que le produit est optimal. 
// ( k = ou placer les parenthéses)
//-----------------------------------------------------------------------------
void RemplirTableau(int* * S, int* * M, int* dim, int size)
{
   int n = size;
   int j = 0; int q=0;
   for(int i2=0; i2<n; i2++)
   {
      // On remplit la diagonale de 0
    M[i2][i2] = 0;
   }

   // l correspond aux sous-chaines de matrices a multiplier
   // On commence par calculer les sous chaines de 2, puis 3, et
   // pour finir on obtiendra la valeur optimale pour la chaine entière

   for(int l=2; l<=n; l++)
   {
     for(int i=0; i<=n-l; i++)
     {
          j = i+l-1;
          M[i][j] = 10000000;
     
      // On essaye toutes les valeurs de k afin de trouver le k optimal
      // qui va donner le meilleur coût pour le produit

      for(int k=i; k<j; k++)
      {
         // formule de récurrence
       q = M[i][k] + M[k+1][j] + (dim[i] * dim[k+1] * dim[j+1]);

       // si le q est meilleur celui calculé précedemment
       // on le garde ainsi que la valeur k

       if (q < M[i][j] )
       {
          M[i][j] = q;
        S[i][j] = k;
       }
      }//for k
     }
   }//for l

}
//-----------------------------------------------------------------------------
// Name : Afficher_Parenthesage_Optimal
// Desc : Affiche le parenthesage optimal des matrices en se basant sur le 
//             tableau S
//-----------------------------------------------------------------------------
void Afficher_Parenthesage_Optimal(int * * S, int i, int j)
{
   if(i==j) cout << "A" << i+1;
   else 
   {
   cout << "( ";
     Afficher_Parenthesage_Optimal(S, i, S[i][j]);
   Afficher_Parenthesage_Optimal(S, S[i][j]+1, j);
   cout << " )";
  }
   
}
//-----------------------------------------------------------------------------
// Name : PrintArray
// Desc : Imprime un tableau a 2 dimensions 
//-----------------------------------------------------------------------------
void PrintArray(int* * tabToPrint,int size)
{
   for(int i=0;i<size;i++)
   {
      for(int j=0;j<size;j++)
    {
         cout << tabToPrint[i][j] << " ,"; 
      }
    cout << endl;
   }
}

int main()
{
   
   int n; int b;
   int indice=0;
   cout << "Entrez le nombre de matrices a multiplier" << endl;
   cin  >> n;
   
   // Tableau qui va contenir les dimensions des lignes des n matrices 
   // + le nombre de colonne de la dernière matrice
   int* dimMatrix = new int[n+1];
   
   // Tableau a remplir par notre algo dynamique
   // Ex M[2][4] = coût optimal du calcul A2 x A3 x A4
   
   // dimension 1 : tableau de 10 pointeurs vers des tableaux d'entiers
   int* *M = new int* [n];
   
   // initialiser les 10 pointeurs à 0 (NULL)
   fill_n( M, n, static_cast<int*>(0));
   
   // dimension 2 : les tableaux d'entiers
    for ( int i = 0; i < n; ++i)
    {
        M[i] = new int[n];
    }

   // Tableau contenant le k optimal
   // Ex S[2][4] = k optimal pour parentheser A2 x A3 x A4 
   
   // dimension 1 : tableau de 10 pointeurs vers des tableaux d'entiers
   int* *S = new int* [n];
   
   // initialiser les 10 pointeurs à 0 (NULL)
   fill_n(S, n, static_cast<int*>(0));
   
   // dimension 2 : les tableaux d'entiers
    for ( int i = 0; i < n; ++i)
    {
        S[i] = new int[n];
    }
   
   // Initialisation des tableaux
   for(int i=0;i<n;i++){
     for(int j=0;j<n;j++){
       M[i][j] = 0;
       S[i][j] = 0;
     }
   }
   // On remplit le tableau des dimensions correspondantes
   for(b=0; b<n; b++)
   {
    cout << "Entrer le nombre de lignes de la matrice " << b+1 <<endl;
    cin  >> indice;
    dimMatrix[b] = indice;
   }
   cout << "Entrez le nombre de colonnes pour la matrice " << n << endl;
   cin  >> indice;

   RemplirTableau(S,M,dimMatrix, n);
   //PrintArray(M,n);
   //cout << endl;
   //PrintArray(S,n);
   cout << " Le meilleur choix des parentheses est le suivant ==>   ";
   cout << endl;
   Afficher_Parenthesage_Optimal(S, 0, n-1);
   cout << endl;
   delete[] S;
   delete[] M;
   system("PAUSE");
   return 0;

}