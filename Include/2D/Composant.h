#ifndef ____COMPOSANT____
#define ____COMPOSANT____

#include "Position2D.h"

class Composant {
	protected :
		int id;
		float largeur;
		float longueur;
		Position2D *position;
		int conteneur;
	public :

		/* Constructeurs                            */

		Composant(void);
		Composant(int nid, float nLargeur, float nLongueur);
		Composant(int nid, float nLargeur, float nLongueur, Position2D* pos);

		/* Destructeur                              */

		~Composant(void);

		/* Setters                                  */

		virtual bool setLargeur(float largeur);
		virtual bool setLongueur(float longueur);
		virtual bool setPosition(Position2D *pos);
		virtual bool setConteneur(int cont);

		/* Getters                                  */

		int getId();
		float getLargeur();
		float getLongueur();
		float getAire();
		Position2D* getPosition();
};

#endif
