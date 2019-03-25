/* Mathematiques de l'informatique graphique    */
/* Position en 3D                               */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Mars 2019                                    */

#ifndef ____POS3D____
#define ____POS3D____

#include "CH3D.h"

class Pos3D : public CH3D {

public:
	/* Constructeurs                            */
	Pos3D(void);
	Pos3D(double x, double y, double z);
	Pos3D(Pos3D *c);

	/* Destructeur                              */
	~Pos3D(void);

	/* Methode de calcul de la distance         */
	/* entre deux positions                     */
	double distance(Pos3D *p);

	/* Methode statique de calcul               */
	/* de la distance entre deux positions      */
	static double distance(Pos3D *p1, Pos3D *p2);
};

#endif
