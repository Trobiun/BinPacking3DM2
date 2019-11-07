#include "2D/Algorithm.h"

Algorithm::Algorithm(std::list<Composant *> composantsMain, std::list<Conteneur *> conteneursMain) : composants(composantsMain), conteneurs(conteneursMain){
	composants.sort();
}

std::list<Composant*> Algorithm::calculRangement() {
	bool place = false;
	std::list<Composant*>::iterator comp;
	std::list<Conteneur *>::iterator cont = conteneurs.begin();
	while (cont != conteneurs.end()) {
		comp = composants.begin();
		while (comp != composants.end()) {

			place = (*cont)->rechercheLibre((*comp)->getLargeur(), (*comp)->getLongueur());
			if (place) {
				composants.erase(comp);
				place = false;
			}
			comp++;
		}
		cont++;
	}
	return composants;
}