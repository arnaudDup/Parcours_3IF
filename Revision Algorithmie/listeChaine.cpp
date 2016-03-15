#include <iostream>
using namespace std;


// la classe est un template.
template <class T>
class File
{

	public:

	// méthode 
	bool insererValeur (T element)
	{	
			bool verif = false;

			// Je créer mon nouveau noeud a insérer 
			Noeud noeud = new Noeud();
			noeud -> element = element;
			noeud -> suivant = NULL;

			// Je l'insére dans notre liste chainé.
			queue -> suivant = noeud;
			queue = noeud;
			nbElement++;  
			verif = true;

		return verif;
	} 

	bool retraitValeur()
	{
			Noeud* noeudAenlever;
			noeudAenlever = tete->suivant;
		// il est necessaire de tester si la liste contient un seul élement
		if (queue == tete->suivant)
		{

		}
		else 
		{
			tete->suivant = noeudAenlever->suivant;
		}


	}
	// constructeur avec un element.
	File <T> ()
	{
		// création de l'élement factice 
		Noeud noeud = new Noeud();
		T elementFactice = new T();
		noeud -> element = elementFactice;
		noeud -> suivant = NULL;

		// Puis on fait pointer les bonnes référence.
		this -> tete = noeud;
		this -> queue = noeud;
		nbElement = 0;
	}

	//affichage
	friend ostream & operator << <T> (ostream & fichierDeSortie, const File <T> & fileAafficher);

	protected: 
	class Noeud
	{
		public:
			T element;
			Noeud * suivant; 
	}; 

	Noeud* tete;
	Noeud* queue;
	int nbElement;

};

int main ()
{
	return 0; 
}