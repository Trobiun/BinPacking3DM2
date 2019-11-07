#include "../../Include/2D/Composant.h"
#include <stdlib.h>
#include <stdio.h>

Composant::Composant(void) {
	id = 0;
	largeur = longueur = 0.0;
	position = new Position2D();
	conteneur = -1;
}
Composant::Composant(int nid, float nLargeur, float nLongueur) {
	id = nid;
	largeur = nLargeur;
	longueur = nLongueur;
	position = new Position2D();
	conteneur = -1;
}
Composant::Composant(int nid, float nLargeur, float nLongueur, Position2D* pos) {
	id = nid;
	largeur = nLargeur;
	longueur = nLongueur;
	position = pos;
	conteneur = -1;
}

Composant::~Composant(void) {
}

/* Getters                                  */

int Composant::getId(void) {
	return id;
}

float Composant::getLargeur(void) {
	return largeur;
}
float Composant::getLongueur(void) {
	return longueur;
}
float Composant::getAire(void) {
	return longueur * largeur;
}
Position2D* Composant::getPosition(void) {
	return position;
}

bool Composant::comp(const Composant& a, const Composant& b)
{
	if (a.largeur*a.longueur < b.largeur* b.longueur) {
		return true;
	}
	return false;
}

/* Setters                                  */


bool Composant::setLargeur(float nlargeur) {
	largeur = nlargeur;
	return true;
}

bool Composant::setLongueur(float nlongueur) {
	longueur = nlongueur;
	return true;
}
bool Composant::setPosition(Position2D *pos) {
	position->setX(pos->getX());
	position->setY(pos->getY());
	return true;
}

bool Composant::setConteneur(int cont) {
	conteneur = cont;
	return true;
}