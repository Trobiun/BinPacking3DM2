#include "2D/Algorithm.h"

Algorithm::Algorithm(std::list<Composant *> composantsMain, std::list<Conteneur *> conteneursMain) : composants(composantsMain), conteneurs(conteneursMain){
	composants.sort();
}

std::list<Composant*> Algorithm::calculRangement() {
	bool place = false;
	float longueurCourante = 0;
	Position2D *posCourante = new Position2D(0, 0);
	std::list<Composant*>::iterator comp;
	std::list<Conteneur *>::iterator cont = conteneurs.begin();
	while (cont != conteneurs.end()) {
		posCourante->setX(longueurCourante + 10);
		(*cont)->setPosition(posCourante);
		comp = composants.begin();
		while (comp != composants.end()) {

			place = (*cont)->rechercheLibre((*comp)->getLargeur(), (*comp)->getLongueur());
			if (place) {
				composants.erase(comp);
				place = false;
			}
			comp++;
		}
		longueurCourante = longueurCourante + 10 + (*cont)->getLongueur();
		cont++;

	}
	return composants;
}

Algorithm::~Algorithm() {

}