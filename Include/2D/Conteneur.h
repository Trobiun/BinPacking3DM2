#ifndef ____CONTENEUR____
#define ____CONTENEUR____

#include <list>
#include "2D/Composant.h"
#include "2D/ArbreBinaire.h"

class Conteneur {
	protected:
		int id;
		float largeur;
		float longueur;
		Position2D pos;
		std::list<Composant *> composants;
		ArbreBinaire* arbre;
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

		/* Modélisation */
		void model();
};

#endif
