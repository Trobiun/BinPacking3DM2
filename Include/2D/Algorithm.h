#ifndef ____ALGORITHM____
#define ____ALGORITHM____

#include "2D/Composant.h"
#include "2D/Conteneur.h"

class Algorithm {
protected :
	std::list<Composant *> composants;
	std::list<Conteneur *> conteneurs;
	std::list<Conteneur *> conteneursDispo;
public:
	Algorithm(std::list<Composant*> composantsMain, std::list<Conteneur*> conteneursMain, std::list<Conteneur*> conteneursDispoMain);
	~Algorithm(void);
	void setListeComposant(std::list<Composant*> composantsMain);
	void setListeConteneur(std::list<Conteneur*> conteneursMain);
	std::list<Composant*> calculRangement();
};
#endif