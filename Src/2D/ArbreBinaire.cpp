#include "../../Include/2D/ArbreBinaire.h"

ArbreBinaire::ArbreBinaire(Conteneur * conteneur) {
	espace_libre->setLargeur(conteneur->getLargeur());
	espace_libre->setLongueur(conteneur->getLongueur());
	sous_arbre_gauche = nullptr;
	sous_arbre_droite = nullptr;
	parent = nullptr;
}
ArbreBinaire::ArbreBinaire(Conteneur * conteneur, ArbreBinaire * p) {
	espace_libre->setLargeur(conteneur->getLargeur());
	espace_libre->setLongueur(conteneur->getLongueur());
	sous_arbre_gauche = nullptr;
	sous_arbre_droite = nullptr;
	parent = p;
}

ArbreBinaire::ArbreBinaire(Composant* composant, ArbreBinaire* p) {
	espace_libre->setLargeur(composant->getLargeur());
	espace_libre->setLongueur(composant->getLongueur());
	sous_arbre_gauche = nullptr;
	sous_arbre_droite = nullptr;
	parent = p;
}

ArbreBinaire::~ArbreBinaire() {
}

/* Setters                                  */

bool ArbreBinaire::setEspaceLibre(Composant * el) {
	espace_libre = el;
	return true;
}
bool ArbreBinaire::setSousArbreGauche(ArbreBinaire * ag) {
	sous_arbre_gauche = ag;
	return true;
}

bool ArbreBinaire::setSousArbreDroite(ArbreBinaire * ad) {
	sous_arbre_droite = ad;
	return true;
}
bool ArbreBinaire::setParent(ArbreBinaire * p) {
	parent = p;
	return true;
}

/* Getters                                  */

Composant * ArbreBinaire::getEspaceLibre() {
	return espace_libre;
}
ArbreBinaire * ArbreBinaire::getSousArbreGauche() {
	return sous_arbre_gauche;
}
ArbreBinaire * ArbreBinaire::getSousArbreDroite() {
	return sous_arbre_droite;
}

ArbreBinaire * ArbreBinaire::getParent() {
	return parent;
}

ArbreBinaire* ArbreBinaire::recherchePremierEspaceLibreValide(ArbreBinaire* noeud, float largeur, float longueur) {
	Composant* racine = noeud->getEspaceLibre();
	ArbreBinaire* res = nullptr;
	if (racine->getLargeur() >= largeur && racine->getLongueur() >= longueur) {
		return noeud;
	}
	else {
		if (noeud->getSousArbreGauche() != nullptr) {
			 res = recherchePremierEspaceLibreValide(noeud->getSousArbreGauche(), largeur, longueur);
			if (res != nullptr) {
				return res;
			}
		}
		if (noeud->getSousArbreDroite() != nullptr) {
			res = recherchePremierEspaceLibreValide(noeud->getSousArbreDroite(), largeur, longueur);
			if (res != nullptr) {
				return res;
			}
		}
	}
	return nullptr;
}

bool ArbreBinaire::creationFils(ArbreBinaire* noeud, float largeur, float longueur, int choix) {
	Composant* libre = noeud->getEspaceLibre();
	Position2D* pos = libre->getPosition();
	Composant* gauche = nullptr;
	Composant* droite = nullptr;
	switch (choix)
	{
	case 0:
		return decoupeHorizontale(largeur, longueur, libre, pos);
		break;
	case 1:
		return decoupeVerticale(largeur, longueur, libre, pos);
		break;
	case 2:
		return decoupeSelonAire(largeur, longueur, libre, pos);
		break;
	default:
		return false;
	}
	libre->setLargeur(0);
	libre->setLongueur(0);
	ArbreBinaire* arbreGauche = new ArbreBinaire(gauche, noeud);
	ArbreBinaire* arbreDroite = new ArbreBinaire(droite, noeud);
	noeud->setSousArbreGauche(arbreGauche);
	noeud->setSousArbreDroite(arbreDroite);
	return true;

}

bool ArbreBinaire::decoupeHorizontale(float largeur, float longueur, Composant* libre, Position2D* pos) {
	int posX = pos->getX();
	int posY = pos->getY();
	int posXnew = posY + longueur;
	int posYnew = posX + largeur;
	Composant* gauche = new Composant(0, libre->getLongueur(), libre->getLargeur() - largeur, new Position2D(posX, posYnew));
	Composant* droite = new Composant(0, libre->getLongueur() - longueur, libre->getLargeur() - largeur, new Position2D(posXnew, posY));
	return true;
}

bool ArbreBinaire::decoupeVerticale(float largeur, float longueur, Composant* libre, Position2D* pos) {
	int posX = pos->getX();
	int posY = pos->getY();
	int posXnew = posY + longueur;
	int posYnew = posX + largeur;
	Composant* gauche = new Composant(0, libre->getLongueur() - longueur, libre->getLargeur() - largeur, new Position2D(posX, posYnew));
	Composant* droite = new Composant(0, libre->getLongueur() - longueur, libre->getLargeur(), new Position2D(posXnew, posY));
	return true;
}

bool ArbreBinaire::decoupeSelonAire(float largeur, float longueur, Composant* libre, Position2D* pos) {
	int posX = pos->getX();
	int posY = pos->getY();
	int posXnew = posY + longueur;
	int posYnew = posX + largeur;
	int gaucheLargeur = (libre->getLongueur() - longueur) * (libre->getLargeur() - largeur);
	int droiteLargeur = (libre->getLongueur() - longueur) * libre->getLargeur();
	int gaucheLongueur = (libre->getLongueur() - longueur) * (libre->getLargeur() - largeur);
	int droiteLongueur = (libre->getLongueur() - longueur) * libre->getLargeur();
	if (((gaucheLargeur > gaucheLongueur) && (gaucheLargeur> droiteLongueur)) || ((droiteLargeur > gaucheLongueur) && (droiteLargeur > droiteLongueur))) {
		Composant* gauche = new Composant(0, libre->getLongueur() - longueur, libre->getLargeur() - largeur, new Position2D(posX, posYnew));
		Composant* droite = new Composant(0, libre->getLongueur() - longueur, libre->getLargeur(), new Position2D(posXnew, posY));
	}
	else {
		Composant* gauche = new Composant(0, libre->getLongueur() - longueur, libre->getLargeur() - largeur, new Position2D(posX, posYnew));
		Composant* droite = new Composant(0, libre->getLongueur() - longueur, libre->getLargeur(), new Position2D(posXnew, posY));
	}
	return true;
}