#include "2D/Debug.h"
#include "2D/Algorithm.h"

static void verifCompoList(std::list <Composant*> liste, int type) {
    if (type == -1) {
        printf("LISTE DES COMPOSANTS DE LA LISTE RESTE: \n");
    } else {
        printf("LISTE DES COMPOSANTS DE LA LISTE CONTENEUR %d: \n", type);
    }
    std::list<Composant*>::iterator comp = liste.begin();
    while (comp != liste.end()) {
        (*comp)->affichageComposant();
        comp++;
    }
}

static bool comp(const Composant *a, const Composant *b) {
    return (a->getCoteX() * a->getCoteY() >= b->getCoteX() * b->getCoteY());
}

Algorithm::Algorithm(std::list<Composant *> composantsMain, std::list<Conteneur *> conteneursMain, std::list<Conteneur*> conteneursDispoMain) : composants(composantsMain), conteneurs(conteneursMain), conteneursDispo(conteneursDispoMain) {
    verifCompoList(composants, -1);
    composants.sort(comp);
    verifCompoList(composants, -1);
}

std::list<Composant*> Algorithm::calculRangement() {
    float longueurCourante = 0;
	std::list<Composant*>::iterator comp;
	std::list<Composant*>::iterator compErase;
    Position2D *posCourante = DBG_NEW Position2D(0, 0);
	std::list<Conteneur*>::iterator cont = conteneurs.begin();


	bool erase = false;
	while (cont != conteneurs.end() & !(composants.empty())) {
		posCourante->setX(longueurCourante);
		(*cont)->setPosition(posCourante->getX(), posCourante->getY());
		comp = composants.begin();
		for (comp; comp != composants.end(); comp++) {
			ArbreBinaire* arbre = (*cont)->rechercheLibre((*comp)->getCoteX(), (*comp)->getCoteY());
			if (arbre != nullptr) {
				if (arbre->getEspaceLibre()->getCoteX() < (*comp)->getCoteX() || arbre->getEspaceLibre()->getCoteY() < (*comp)->getCoteY()) {
					float xTemps = (*comp)->getCoteX();
					float yTemps = (*comp)->getCoteY();
					(*comp)->setCoteX(yTemps);
					(*comp)->setCoteY(xTemps);
				}
				arbre->affichageArbre();
				if (erase) {
					composants.erase(compErase);
					erase = false;
				}

				(*comp)->setConteneur((*cont)->getId());
				(*comp)->setPosition(arbre->getEspaceLibre()->getPosition());
				(*cont)->addComposant(*comp);
				arbre->creationFils((*comp)->getCoteX(), (*comp)->getCoteY(), 0);
				compErase = comp;
				arbre = nullptr;
				erase = true;
			}
		}
		if (erase) {
			composants.erase(compErase);
			erase = false;
		}
		longueurCourante = longueurCourante + 10 + (*cont)->getCoteY();
		cont++;

	}
	if (posCourante != nullptr) {
		delete posCourante;
		posCourante = nullptr;
	}
    return composants;
}

Algorithm::~Algorithm() {
    std::list<Conteneur*>::iterator it;
    for (it = conteneurs.begin(); it != conteneurs.end(); it++) {
        delete *it;
    }
    conteneurs.clear();
    std::list<Composant*>::iterator it2;
    for (it2 = composants.begin(); it2 != composants.end(); it2++) {
        delete *it2;
    }
    composants.clear();
}

void Algorithm::setListeComposant(std::list<Composant*> composantsMain){
	composants = composantsMain;
}

void Algorithm::setListeConteneur(std::list<Conteneur*> conteneursMain) {
	conteneurs = conteneursMain;
}