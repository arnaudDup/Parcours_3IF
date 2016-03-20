#include "controleur.h"
#include "Modele.h"
#include "IFigure.h"
#include "Point.h"
#include "Composite.h"
#include <vector>

using namespace std;

// instanciation de l'unique controleur du programme
// Utilisation du design pattern singleton.

Controleur* Controleur :: uniqueInstance = new Controleur();
int main(int argc, char *argv[])
{
    Controleur* controleur = Controleur::getInstance();
	Controleur :: getInstance()->DebuterLecture();
    delete controleur;
    return 0;
}
