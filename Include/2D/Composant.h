#ifndef ____COMPOSANT____
#define ____COMPOSANT____

#include <GL/gl.h>

#include "2D/Position2D.h"

class Composant {
	protected :
		int id;
		float coteX;
		float coteY;
		Position2D *position;
		int conteneur;
	public :

		/* Constructeurs                            */

		Composant(void);
		Composant(int nid, float nCoteX, float nCoteY);
		Composant(int nid, float nCoteX, float nCoteY, Position2D* pos);
		Composant(int nid, float nCoteX, float nCoteY, float x, float y);
		/* Destructeur                              */

		~Composant(void);

		/* Setters                                  */

		virtual bool setCoteX(float nCoteX);
		virtual bool setCoteY(float nCoteY);
		virtual bool setPosition(Position2D *pos);
                virtual bool setPosition(float posX, float posY);
		virtual bool setConteneur(int cont);

		/* Getters                                  */

		int getId();
		int getIdConteneur();
		float getCoteX() const;
		float getCoteY() const;
		float getAire();
		Position2D* getPosition();

		/* Comparateur                             */
		bool operator<(const Composant* a);

		/* Mod�lisation */
		void model(const GLfloat couleur[4]);

		/*Affichage */
		void affichageComposant();
};

#endif
