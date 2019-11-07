#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#include "2D/Conteneur.h"

Conteneur::Conteneur(void) {
	id = 0;
	largeur = longueur = 0.0;
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

void Conteneur::model() {
	glPushMatrix();
	glTranslatef(pos.getX(), pos.getY(), 0.0);
	glScalef(largeur, longueur, 0.0);
	glutWireCube(1.0);
	glPopMatrix();
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
