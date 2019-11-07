#ifndef ____ALGORITHM____
#define ____ALGORITHM____

#include "2D/Composant.h"
#include "2D/Conteneur.h"

class Algorithm {
protected :
	std::list<Composant *> composants;
	std::list<Conteneur *> conteneurs;
public:
	Algorithm(std::list<Composant*> composantsMain, std::list<Conteneur*> conteneursMain);
	~Algorithm(void);

	std::list<Composant*> calculRangement();
};
#endif