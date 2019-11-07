#ifndef ____CONTENEUR____
#define ____CONTENEUR____

#include <list>
#include "../../Include/2D/Composant.h"

class Conteneur {
	protected:
		int id;
		float largeur;
		float longueur;
		std::list<Composant> composants;
	public:

		/* Constructeurs                            */

		Conteneur(void);
		Conteneur(int id, float largeur, float longueur);

		/* Destructeur                              */

		~Conteneur(void);

		/* Setters                                  */

		virtual bool setLargeur(float largeur);
		virtual bool setLongueur(float longueur);

		/* Getters                                  */

		int getId();
		float getLargeur();
		float getLongueur();
};

#endif
