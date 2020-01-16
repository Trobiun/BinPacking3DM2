#ifndef ____COMPOSANT3D____
#define ____COMPOSANT3D____

#include <GL/gl.h>
#include <vector>
using namespace std;
#include "3D/Position3D.h"

class Composant3D {
	protected :
		int id;
		float coteX;
		float coteY;
		float coteZ;
		Position3D *position;
		std::vector<int> orientationPossible;
		int conteneur;
	public :

		/* Constructeurs                            */

		Composant3D(void);
		Composant3D(int nid, float nCoteX, float nCoteY, float nCoteZ);
		Composant3D(int nid, float nCoteX, float nCoteY, float nCoteZ, std::vector<int> tab);
		Composant3D(int nid, float nCoteX, float nCoteY, float nCoteZ, Position3D* pos);
		Composant3D(int nid, float nCoteX, float nCoteY, float nCoteZ, float x, float y, float z);
		/* Destructeur                              */

		~Composant3D(void);

		/* Setters                                  */

		virtual bool setCoteX(float nCoteX);
		virtual bool setCoteY(float nCoteY);
		virtual bool setCoteZ(float nCoteZ);
		virtual bool setPosition(Position3D *pos);
		virtual bool setTabOrientation(std::vector<int> tab);
		virtual bool setTabOrientation(int face1, int face2, int face3, int face4, int face5, int face6);
        virtual bool setPosition(float posX, float posY, float posZ);
		virtual bool setConteneur(int cont);

		/* Getters                                  */

		int getId();
		int getIdConteneur();
		float getCoteX() const;
		float getCoteY() const;
		float getCoteZ() const;
		std::vector<int> getTabOrientation() const;
		float getVolume();
		Position3D* getPosition();

		/* Comparateur                             */
		bool operator<(const Composant3D* a);

		/* Modelisation */
		void model(const GLfloat couleur[4], bool opaque);

		/*Affichage */
		void affichageComposant();
};
#endif
