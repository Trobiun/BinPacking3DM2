#include "2D/Algorithm.h"

Algorithm::Algorithm(std::list<Composant *> composantsMain, std::list<Conteneur *> conteneursMain, ArbreBinaire* arbreMain) : composants(composantsMain), conteneurs(conteneursMain){
	arbre = arbreMain;
	composants.sort();
	conteneurs.sort();
}

std::list<Composant*> Algorithm::calculRangement() {
	bool place = false;
	std::list<Conteneur *>::iterator cont = conteneurs.begin();
	while (cont != conteneurs.end()) {
		std::list<Composant*>::iterator comp = composants.begin();
		while (comp != composants.end()) {

			place = (*cont)->rechercheLibre((*comp)->getLargeur(), (*comp)->getLongueur());
			if (place) {
				composants.erase(comp);
				place = false;
			}
			comp++;
		}
	}
	return composants;
}