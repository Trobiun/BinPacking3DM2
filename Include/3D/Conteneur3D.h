#ifndef ____CONTENEUR3D____
#define ____CONTENEUR3D____

#include <GL/gl.h>
#include <list>
#include "3D/Composant3D.h"

class Conteneur3D {
	protected:
		int id;
		float coteX;
		float coteY;
		float coteZ;
		Position3D *pos;
		std::list<Composant3D *> composants;
                
	public:
                //static GLfloat couleur[4];
		/* Constructeurs                            */

		Conteneur3D(void);
		Conteneur3D(int id, float nCoteX, float nCoteY, float nCoteZ);

		/* Destructeur                              */

		~Conteneur3D(void);

		/* Setters                                  */

		virtual bool setCoteX(float nCoteX);
		virtual bool setCoteY(float nCoteY);
		virtual bool setCoteZ(float nCoteZ);
		virtual bool setPosition(Position3D * position);
        virtual bool setPosition(float posX, float posY, float posZ);
		virtual bool addComposant(Composant3D * comp);
		/* Getters                                  */

		int getId();
		float getCoteX();
		float getCoteY();
		float getCoteZ();
		std::list<Composant3D *> getListComposant();

		/* Mod�lisation */
		void model();

		//ArbreBinaire* rechercheLibre(float sCoteX, float sCoteY);

		/*Affichage*/

		void affichageConteneur();
};

#endif
