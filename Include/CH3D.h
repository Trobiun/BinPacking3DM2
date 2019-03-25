/* Mathematiques de l'informatique graphique    */
/* Coordonnees homogenes en 3D                  */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Mars 2019                                    */

#ifndef ____CH3D____
#define ____CH3D____

class CH3D {

public:
	/* Coordonnees                              */
	union {
		struct {
			double x;
			double y;
			double z;
			double w;
		};
		double c[4];
	};

public:
	/* Constructeurs                            */
	CH3D(void);
	CH3D(double x, double y, double z, double w);
	CH3D(CH3D *c);

	/* Destructeur                              */
	~CH3D(void);

	/* Methode d'affichage texte                */
	void print(void);
};

#endif
