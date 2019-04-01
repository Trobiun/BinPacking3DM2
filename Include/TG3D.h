#pragma once

#include "CH3D.h"

class TG3D {

public:
	/* Coordonnees                              */
	double c[4][4];


public:
	/* Constructeurs                            */
	TG3D(void);
	TG3D(TG3D *tg);

	/* Destructeur                              */
	~TG3D(void);

	/* Methode d'affichage texte                */
	void print(void);
	void affectation(TG3D *temp, TG3D *res);
	void transformation(CH3D *ch);
	void transformation(CH3D *ch, CH3D *res);
	void composition(TG3D *tg, TG3D *res);
};
