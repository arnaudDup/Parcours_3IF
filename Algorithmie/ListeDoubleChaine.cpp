#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* placer ici vos déclarations de structure */

struct Liste{
	int valeur;
	struct Liste * suivant;
	struct Liste * precedent;
};

/* placer ici vos déclarations de fonctions ou procédures */

struct Liste * Initialisation (void);

void AjouterValeur(int val, struct Liste * sentinelle);

void SupprimerValeur(int val, struct Liste * sentinelle);

void Afficher (struct Liste * sentinelle);

void Compress (struct Liste * sentinelle);

void Liberer(struct Liste * sentinelle);

int main(void) 
{
   int val;
   char lecture[100];

   /* placer ici la déclaration de votre liste ainsi que 
    * son initialisation */
    
    struct Liste * test;
    test = Initialisation();

   fscanf(stdin,"%99s",lecture);
   while (strcmp(lecture,"bye")!=0) {
      if (strcmp(lecture,"insert")==0) {
         fscanf(stdin,"%99s",lecture);
         val = strtol(lecture,NULL,10);
         /* mettez votre code pour l'insertion dans la liste de val */
         AjouterValeur(val, test);   
      } else if (strcmp(lecture,"print")==0) {
         /* mettez ici votre code pour l'affichage de la liste */
         Afficher(test);
         }else if (strcmp(lecture,"compress")==0) {
         /* mettez ici votre code pour l'affichage de la liste */
         Compress(test);
      
      } else if (strcmp(lecture,"remove")==0) {
         fscanf(stdin,"%99s",lecture);
         val = strtol(lecture,NULL,10);
         /* mettez ici votre code pour enlever la valeur val de la liste */
         SupprimerValeur(val, test);
      }
      fscanf(stdin,"%99s",lecture);
   }
   /* placer ici la libération de la liste */
   Liberer(test);
   return 0;
}

/* placer ici vos définitions de fonctions ou procédures */

struct Liste * Initialisation (void)
{  
	struct Liste * sentinelle = malloc(sizeof(struct Liste));
	sentinelle->suivant= sentinelle;
	sentinelle->precedent=sentinelle;
	
	
	return sentinelle;
}

void AjouterValeur(int val, struct Liste * sentinelle)
{
struct Liste * courant= sentinelle->suivant;
struct Liste * nouveau = malloc (sizeof(struct Liste));

nouveau->valeur = val;

while (courant != sentinelle && val > courant->valeur)

	{
		courant=courant->suivant;
	}
	
	nouveau->suivant=courant;
	nouveau->precedent=courant->precedent;
	
	courant->precedent->suivant=nouveau;
	courant->precedent=nouveau;

}

void SupprimerValeur(int val,  struct Liste * sentinelle)
{
struct Liste * courant=sentinelle->suivant;

	while (courant != sentinelle)
	{
		
		if (courant->valeur==val)
		{
			courant ->precedent->suivant = courant->suivant;
			courant ->suivant->precedent = courant->precedent;
			break;
		}
		
		else
		{
			courant= courant->suivant;
		}
	}
}

void Afficher (struct Liste * sentinelle)
{
	struct Liste * courant=sentinelle->suivant;
	while (courant != sentinelle)
	{
		printf("%d\r\n", courant->valeur);
		courant=courant->suivant;
	}
	printf("\r\n");
}

void Liberer( struct Liste * sentinelle)
{
	
	struct Liste * courant= sentinelle;
	
	while (courant->suivant != sentinelle)
	{
		courant=courant->suivant;
		free (courant->precedent);
		
	}
	
	
	
}

void Compress (struct Liste * sentinelle)
{
	struct Liste * courant=sentinelle->suivant;
	
	while (courant != sentinelle)
	{
		if(courant->valeur==courant->suivant->valeur)
		{
		SupprimerValeur(courant->valeur, sentinelle);
		}	
		courant=courant->suivant;
	}
}
