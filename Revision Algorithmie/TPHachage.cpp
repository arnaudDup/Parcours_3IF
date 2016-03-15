#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;
/* mettez ici vos définitions de fonctions et types */

struct Cellule
{
    int etat;
    char * cle;
    char * valeur;
};
typedef struct Cellule Cellule;

struct Table
{
    Cellule * tab;
    int taille;
};
typedef struct Table Table;

Table Initialiser (Table table, int taille);
int CalculCle(char*cle);
void Afficher(char* message);
void Ajouter (Table table, char* cle, char * valeur);
void Supprimer (Table table, char* cle);
void Requete (Table table, char* cle);
void Stats (Table table);
void Liberer (Table table);

void error(void);

int main(void)
{
   int size;
   char lecture[100];
   char * key;
   char * val;
   Table hasch;

   if (fscanf(stdin,"%99s",lecture)!=1)
      error();
   while (strcmp(lecture,"bye")!=0)
   {
      if (strcmp(lecture,"init")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         size = atoi(lecture);
         /* mettre le code d'initialisation ici */
         hasch = Initialiser(hasch, size);
      }
      else if (strcmp(lecture,"insert")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         key = strdup(lecture);
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         val = strdup(lecture);
         /* mettre ici le code d'insertion */
         Ajouter(hasch,key,val);
      }
      else if (strcmp(lecture,"delete")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         key = strdup(lecture);
         /* mettre ici le code de suppression */
         Supprimer(hasch,key);
      }
      else if (strcmp(lecture,"query")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
        key = strdup(lecture);
         /* mettre ici le code de recherche et traitement/affichage du résultat */
         Requete(hasch,key);
      }
      else if (strcmp(lecture,"destroy")==0)
      {
         /* mettre ici le code de destruction */
         Liberer(hasch);
      }
      else if (strcmp(lecture,"stats")==0)
      {
         /* mettre ici le code de statistiques */
         Stats(hasch);
      }

      if (fscanf(stdin,"%99s",lecture)!=1)
         error();
   }
   return 0;
}

/* placer ici vos définitions de fonctions ou procédures */
Table Initialiser (Table table, int taille)
{
    table.taille = taille;
    table.tab = (Cellule *) malloc(sizeof(Cellule)*taille);
    int i;
    for(i=0;i<taille;i++)
    {
        table.tab[i].etat=0;
    }
    return table;
}

// Calcule de la cle de hachage. 
int CalculCle(char*cle)
{
    int i = 0;
    int clef=0;
    while(cle[i]!='\0')
    {
        clef+= (int)cle[i]*pow(256,i);
        i++;
    }
    return clef;
}


void Ajouter (Table table, char* cle, char * valeur)
{
    int clef = CalculCle(cle)%(table.taille);
    while(table.tab[clef].etat!=0 && strcmp(table.tab[clef].cle,cle))
    {
        clef++;
    }
    table.tab[clef].etat = 1;
    table.tab[clef].cle = cle;
    table.tab[clef].valeur = valeur;
}

void Supprimer (Table table, char* cle)
{
    int clef = CalculCle(cle)%(table.taille);
    while(table.tab[clef].etat!=0 && strcmp(table.tab[clef].cle,cle))
    {
        clef++;
    }
    if(table.tab[clef].etat==1)
    {
        table.tab[clef].etat = 2;
    }
}

void Requete (Table table, char* cle)
{
    int clef = CalculCle(cle)%(table.taille);
    while(table.tab[clef].etat!=0 && strcmp(table.tab[clef].cle, cle))
    {
        clef++;
    }
    if(table.tab[clef].etat==1)
    {
        cout << table.tab[clef].valeur << endl;
        printf("\r\n");
    } else {
        printf("Not found\r\n");
    }
}

void Stats (Table table)
{
    int i;
    int vide = 0;
    int supprime = 0;
    int occupe = 0;
    for(i=0;i<table.taille;i++)
    {
        if(table.tab[i].etat == 0) vide++;
        if(table.tab[i].etat == 1)
        {
            occupe++;
        }
        if(table.tab[i].etat == 2) supprime++;
    }
    printf("size    : %d\r\n",table.taille);
    printf("empty   : %d\r\n",vide);
    printf("deleted : %d\r\n",supprime);
    printf("occupied: %d\r\n",occupe);
}

void Liberer (Table table)
{
    free(table.tab);
}


void error(void)
{
   printf("input error\r\n");
   exit(0);
}
