#ifndef ____CONTENEUR____
#define ____CONTENEUR____

#include <GL/gl.h>
#include <list>
#include "2D/Composant.h"
#include "2D/ArbreBinaire.h"

class Conteneur {
	protected:
		int id;
		float largeur;
		float longueur;
		Position2D *pos;
		std::list<Composant *> composants;
		ArbreBinaire* arbre;
                
	public:
                //static GLfloat couleur[4];
		/* Constructeurs                            */

		Conteneur(void);
		Conteneur(int id, float largeur, float longueur);

		/* Destructeur                              */

		~Conteneur(void);

		/* Setters                                  */

		virtual bool setLargeur(float largeur);
		virtual bool setLongueur(float longueur);
		virtual bool setPosition(Position2D * position);
                virtual bool setPosition(float x, float y);
		virtual bool addComposant(Composant * comp);
		/* Getters                                  */

		int getId();
		float getLargeur();
		float getLongueur();
		ArbreBinaire* getArbre();
		std::list<Composant *> getListComposant();

		/* Mod�lisation */
		void model();

		ArbreBinaire* rechercheLibre(float largeur, float longueur);

		/*Affichage*/

		void affichageConteneur();
};

#endif
