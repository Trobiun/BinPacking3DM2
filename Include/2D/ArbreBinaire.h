#ifndef ____ARBREBINAIRE____
#define ____ARBREBINAIRE____
#include <stdio.h>
#include "Composant.h"

class ArbreBinaire {
protected :
	Composant * espace_libre;
	ArbreBinaire * sous_arbre_gauche;
	ArbreBinaire * sous_arbre_droite;
	ArbreBinaire * parent;
public:
        GLfloat bleu[4] = {0.0F,0.0F,1.0F,1.0F};
	/* Constructeurs                            */

	ArbreBinaire(float coteX, float coteY);
	ArbreBinaire(Composant* composant, ArbreBinaire* p);

	/* Destructeur                              */

	~ArbreBinaire(void);

	/* Setters                                  */

	virtual bool setEspaceLibre(Composant * el);
	virtual bool setSousArbreGauche(ArbreBinaire * ag);
	virtual bool setSousArbreDroite(ArbreBinaire * ad);
	virtual bool setParent(ArbreBinaire * p);

	/* Getters                                  */

	Composant * getEspaceLibre();
	ArbreBinaire * getSousArbreGauche();
	ArbreBinaire * getSousArbreDroite();
	ArbreBinaire * getParent();

	ArbreBinaire* recherchePremierEspaceLibreValide(float coteX, float coteY);

	bool creationFils(float coteX, float coteY, int choix);
	bool decoupeHorizontale(float coteX, float coteY, Composant* libre, Position2D* pos, Composant* gauche, Composant* droite);
	bool decoupeVerticale(float coteX, float coteY, Composant* libre, Position2D* pos, Composant* gauche, Composant* droite);
	bool decoupeSelonAire(float coteX, float coteY, Composant* libre, Position2D* pos, Composant* gauche, Composant* droite);

	/*affichage */
	void affichageArbre();
        
        void model();
        
};

#endif 

