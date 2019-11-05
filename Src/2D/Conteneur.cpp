#include "../../Include/2D/Conteneur.h"

#include <stdlib.h>
#include <stdio.h>
#include <2D\Composant.h>

Conteneur::Conteneur(void) {
	id = 0;
	largeur = longueur = 100.0;

}

Conteneur::Conteneur(int nid, float nLargeur, float nLongueur){
	id = nid;
	largeur = nLargeur;
	longueur = nLongueur;
}

Conteneur::~Conteneur(void) {
}

/* Getters                                  */

int Conteneur::getId(void) {
	return id;
}

float Conteneur::getLargeur(void) {
	return largeur;
}
float Conteneur::getLongueur(void) {
	return longueur;
}


/* Setters                                  */

bool Conteneur::setLargeur(float nlargeur) {
	largeur = nlargeur;
	return true;
}

bool Conteneur::setLongueur(float nlongueur) {
	longueur = nlongueur;
	return true;
}
