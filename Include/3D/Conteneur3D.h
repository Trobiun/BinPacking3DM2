#ifndef ____CONTENEUR3D____
#define ____CONTENEUR3D____

#include <GL/gl.h>
#include <list>
#include "3D/Composant3D.h"
#include "3D/ArbreBinaire3D.h"

class Conteneur3D {
	protected:
		int id;
		float coteX;
		float coteY;
		float coteZ;
		Position3D *pos;
		ArbreBinaire3D* arbre;
		std::list<Composant3D *> composants;
		int nb;
                
	public:
                //static GLfloat couleur[4];
		/* Constructeurs                            */

		Conteneur3D(void);
		Conteneur3D(int id, float nCoteX, float nCoteY, float nCoteZ, int nnb);

		/* Destructeur                              */

		~Conteneur3D(void);

		/* Setters                                  */

		virtual bool setCoteX(float nCoteX);
		virtual bool setCoteY(float nCoteY);
		virtual bool setCoteZ(float nCoteZ);
		virtual bool setNb(int nnb);
		virtual bool setPosition(Position3D * position);
        virtual bool setPosition(float posX, float posY, float posZ);
        virtual Position3D* getPosition();
		virtual bool addComposant(Composant3D * comp);
		/* Getters                                  */

		int getId();
		float getCoteX();
		float getCoteY();
		float getCoteZ();
		int getNb();
		bool takeCont();
		std::list<Composant3D *> getListComposant();

		/* Mod�lisation */
		void model();

		ArbreBinaire3D* rechercheLibre(float sCoteX, float sCoteY, float sCoteZ);

		/*Affichage*/

		void affichageConteneur();
};

#endif
