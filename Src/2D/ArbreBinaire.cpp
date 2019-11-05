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
