#ifndef ____ALGORITHM____
#define ____ALGORITHM____

#include <2D\ArbreBinaire.h>
#include "../../Include/2D/Composant.h"
#include "../../Include/2D/Conteneur.h"

class Algorithm {

protected :
	ArbreBinaire* arbre;
	std::list<Composant *> composants;
	std::list<Conteneur *> conteneurs;
public:
	Algorithm(std::list<Composant*> composantsMain, std::list<Conteneur*> conteneursMain, ArbreBinaire* arbreMain);

	~Algorithm(void);

	std::list<Composant*> calculRangement();
};
#endif