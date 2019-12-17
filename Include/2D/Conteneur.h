#ifndef ____CONTENEUR____
#define ____CONTENEUR____

#include <GL/gl.h>
#include <list>
#include "2D/Composant.h"
#include "2D/ArbreBinaire.h"

class Conteneur {
	protected:
		int id;
		float coteX;
		float coteY;
		Position2D *pos;
		std::list<Composant *> composants;
		ArbreBinaire* arbre;
                
	public:
                //static GLfloat couleur[4];
		/* Constructeurs                            */

		Conteneur(void);
		Conteneur(int id, float nCoteX, float nCoteY);

		/* Destructeur                              */

		~Conteneur(void);

		/* Setters                                  */

		virtual bool setCoteX(float nCoteX);
		virtual bool setCoteY(float nCoteY);
		virtual bool setPosition(Position2D * position);
        virtual bool setPosition(float posX, float posY);
        virtual Position2D* getPosition();
		virtual bool addComposant(Composant * comp);
		/* Getters                                  */

		int getId();
		float getCoteX();
		float getCoteY();
		ArbreBinaire* getArbre();
		std::list<Composant *> getListComposant();

		/* Mod�lisation */
		void model();

		ArbreBinaire* rechercheLibre(float sCoteX, float sCoteY);

		/*Affichage*/

		void affichageConteneur();
};

#endif
