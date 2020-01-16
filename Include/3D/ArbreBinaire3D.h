#ifndef ____ARBREBINAIRE3D____
#define ____ARBREBINAIRE3D____
#include <stdio.h>
#include "Composant3D.h"

class ArbreBinaire3D {
protected:
	Composant3D* espace_libre;
	ArbreBinaire3D* sous_arbre_gauche;
	ArbreBinaire3D* sous_arbre_droite;
	ArbreBinaire3D* sous_arbre_haut;
	ArbreBinaire3D* parent;
public:
	GLfloat bleu[4] = { 0.0F,0.0F,1.0F,1.0F };
	/* Constructeurs                            */

	ArbreBinaire3D(float coteX, float coteY, float coteZ);
	ArbreBinaire3D(Composant3D* composant, ArbreBinaire3D* p);

	/* Destructeur                              */

	~ArbreBinaire3D(void);

	/* Setters                                  */

	virtual bool setEspaceLibre(Composant3D* el);
	virtual bool setSousArbreGauche(ArbreBinaire3D* ag);
	virtual bool setSousArbreDroite(ArbreBinaire3D* ad);
	virtual bool setSousArbreHaut(ArbreBinaire3D* ad);
	virtual bool setParent(ArbreBinaire3D* p);

	/* Getters                                  */

	Composant3D* getEspaceLibre();
	ArbreBinaire3D* getSousArbreGauche();
	ArbreBinaire3D* getSousArbreDroite();
	ArbreBinaire3D* getSousArbreHaut();
	ArbreBinaire3D* getParent();

	ArbreBinaire3D* recherchePremierEspaceLibreValide(float coteX, float coteY, float coteZ);

	bool creationFils(float coteX, float coteY, float coteZ, int choix);
	bool decoupeHorizontale(float coteX, float coteY, float coteZ, Composant3D* libre, Position3D* pos, Composant3D* gauche, Composant3D* droite, Composant3D* haut);
	bool decoupeVerticale(float coteX, float coteY, float coteZ, Composant3D* libre, Position3D* pos, Composant3D* gauche, Composant3D* droite, Composant3D* haut);
	bool decoupeSelonAire(float coteX, float coteY, float coteZ, Composant3D* libre, Position3D* pos, Composant3D* gauche, Composant3D* droite, Composant3D* haut);

	/*affichage */
	void affichageArbre();

	void model();

};

#endif 