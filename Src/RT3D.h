#include "Dir3D.h"
#include "TG3D.h"

class RT3D : public TG3D {

public:
	/* Coordonnees                              */
	double c[4][4];


public:
	/* Constructeurs                            */
	RT3D(void),
		RT3D(double alpha, double ax, double ay, double az),
		RT3D(double alpha, Dir3D *d),
		RT3D(RT3D *rt);

	/* Destructeur                              */
	~RT3D(void);

	/* Methode d'affichage texte                */
	void print(void);
};

