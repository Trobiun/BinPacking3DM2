#include "2D/Algorithm.h"

Algorithm::Algorithm(std::list<Composant *> composantsMain, std::list<Conteneur *> conteneursMain) : composants(composantsMain), conteneurs(conteneursMain){
	composants.sort();
}

std::list<Composant*> Algorithm::calculRangement() {
	float longueurCourante = 0;
	Position2D *posCourante = new Position2D(0, 0);
	std::list<Conteneur *>::iterator cont = conteneurs.begin();
	std::list<Composant*>::iterator comp;
	std::list<Composant*>::iterator compErase;
	bool erase= false;
	while (cont != conteneurs.end() & !(composants.empty())) {
		posCourante->setX(longueurCourante + 10);
		(*cont)->setPosition(posCourante);
		comp = composants.begin();
		for (comp; comp != composants.end(); comp++){
			ArbreBinaire * arbre = (*cont)->rechercheLibre((*comp)->getLargeur(), (*comp)->getLongueur());
			if (arbre != nullptr) {
				if (erase) {
					composants.erase(compErase);
					erase = false;
				}
				printf("la position suivie de l'id conteneur avant le set : %f,%f et %d\n" , (*comp)->getPosition()->getX(), (*comp)->getPosition()->getY(), (*comp)->getIdConteneur());
				(*comp)->setConteneur((*cont)->getId());
				(*comp)->setPosition(arbre->getEspaceLibre()->getPosition());
				printf("la position suivie de l'id conteneur apres le set : %f,%f et %d\n", (*comp)->getPosition()->getX(), (*comp)->getPosition()->getY(), (*comp)->getIdConteneur());

				(*cont)->addComposant(*comp);
				arbre->creationFils((*comp)->getLargeur(), (*comp)->getLongueur(), 3);
				compErase = comp;
				arbre = nullptr;
				erase = true;
			}
		}
		if (erase) {
			composants.erase(compErase);
			erase = false;
		}
		longueurCourante = longueurCourante + 10 + (*cont)->getLongueur();
		cont++;

	}
	return composants;
}

Algorithm::~Algorithm() {

}