Arnaud Dupeyrat et Antoine Breton
3 IF - TP4

Dans ce dossier :
	- Specification
	- Cahier des charges
	- Plan de test
	- Diagrammes de classe de l'application
	- les sources dans SRC, 
	- le makefile de SRC/build

Evolution (manque de temps) :

	- (LOAD) problème de gestion des flux récursifs lors de la lecture d'une figure composite, qui contient des composites.
	
	Notre idée etait de construire un composite a partir d'un flux d'un fichier respecant le formalisme suivant :
	LOADCOMP nom 0/* 0 si union 1 si inter */ <nom> R nom_0 12 13 14 15 | LOADCOMP nom_0 0 <nom_0> R nom_0_0 1 2 3 4 | R nom_0_1 2 3 4 5 </nom_0> | S nom_1 2 3 4 5 </nom>
	
	le contenu des balises <nom> <\nom> représente une liste des composants du composite "nom" séparé par des '|'. 
	
	Pour obtenir, le composite résultat nous avons fais un algorithme de parsing recursif (methode lireComp) sité dans la classe ParserEntree.
	Ayant rencontré des difficultés, nous avons fais le choix de laisser cet algorithme "de côté" pour ne pas perdre trop de temps. Nous savons
	que l'idée est bonne et nous aurions corrigé cet algorithme si nous avions eu plus de temps.
	
	L'algorithme fonctionnait dans les cas "classiques" mais lorsqu'un composite etait lui même composé de composites, la recursion ne fonctionnait pas
	(problème de gestion de flux).
