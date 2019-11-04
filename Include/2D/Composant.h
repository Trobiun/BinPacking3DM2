#ifndef ____COMPOSANT____
#define ____COMPOSANT____

#include "Position2D.h"

class Composant {
	protected :
		int id;
		float largeur;
		float longueur;
		Position2D *position;


	public :

		/* Constructeurs                            */

		Composant(void);
		Composant(int id,float largeur,float longueur);

		/* Destructeur                              */

		~Composant(void);

		/* Setters                                  */

		virtual bool setLargeur(float largeur);
		virtual bool setLongueur(float longueur);
		virtual bool setPosition(Position2D *pos);

		/* Getters                                  */

		int getId();
		float getLargeur();
		float getLongueur();
		float getAire();
		Position2D* getPosition();
};

#endif
