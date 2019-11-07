#include "../../Include/2D/Algorithm.h"

Algorithm::Algorithm(std::list<Composant *> composantsMain, std::list<Conteneur *> conteneursMain, ArbreBinaire* arbreMain) : composants(composantsMain), conteneurs(conteneursMain){
	arbre = arbreMain;
	composants.sort();
	conteneurs.sort();
}

std::list<Composant*> Algorithm::calculRangement() {
	std::list<Composant*> test;
	return test;
}