#ifndef ____ALGORITHM3D____
#define ____ALGORITHM3D____

#include "3D/Composant3D.h"
#include "3D/Conteneur3D.h"

class Algorithm3D {
protected:
	std::list<Composant3D*> composants3D;
	std::list<Conteneur3D*> conteneurs3D;
	std::list<Conteneur3D*> conteneursDispo3D;
public:
	Algorithm3D(std::list<Composant3D*> composantsMain, std::list<Conteneur3D*> conteneursMain, std::list<Conteneur3D*> conteneursDispoMain);
	~Algorithm3D(void);
	void setListeComposant(std::list<Composant3D*> composantsMain);
	void setListeConteneur(std::list<Conteneur3D*> conteneursMain);
	std::list<Composant3D*> calculRangement();
};
#endif
