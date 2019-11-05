#ifndef ____ARBREBINAIRE____
#define ____ARBREBINAIRE____
#include "Composant.h"
#include "Conteneur.h"

class ArbreBinaire {
protected :
	Composant * espace_libre;
	ArbreBinaire * sous_arbre_gauche;
	ArbreBinaire * sous_arbre_droite;
	ArbreBinaire * parent;
public:
	/* Constructeurs                            */

	ArbreBinaire(Conteneur * conteneur);
	ArbreBinaire(Conteneur * conteneur, ArbreBinaire * parent);
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

	ArbreBinaire* recherchePremierEspaceLibreValide(ArbreBinaire* noeud, float largeur, float longueur);

	bool creationFils(ArbreBinaire* noeud, float largeur, float longueur, int choix);
	bool decoupeHorizontale(ArbreBinaire* noeud, float largeur, float longueur);
	bool decoupeVerticale(ArbreBinaire* noeud, float largeur, float longueur);
	bool decoupeSelonAire(ArbreBinaire* noeud, float largeur, float longueur);
};

#endif 

