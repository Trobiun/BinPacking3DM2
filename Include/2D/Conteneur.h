#ifndef ____CONTENEUR____
#define ____CONTENEUR____

#include "Position2D.h"

class Conteneur {
	protected:
		int id;
		float largeur;
		float longueur;
		Position2D pos;

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
