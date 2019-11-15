#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#include "2D/Composant.h"

Composant::Composant(void) {
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
	if (position != NULL) {
		//delete position;
		position = NULL;
	}
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

int Composant::getIdConteneur() {
	return conteneur;
}
/* Mod�lisation */
void Composant::model(GLfloat couleur[4]) {
	glPushMatrix();
	glTranslatef(position->getX() + largeur / 2, position->getY() + longueur / 2, 0.0);
	glScalef(largeur, longueur, 0.0);
    //GLfloat couleur[] = {0.0F,1.0F,0.0F,1.0F};
    glColor4fv(couleur);
	glutSolidCube(1.0);
	glPopMatrix();
}

/*Affichage */

void Composant::affichageComposant() {
	printf("COMPOSANT : Id = %d, Largeur = %.2f, Longueur = %.2f, Position = (%.2f,%.2f), Conteneur = %d \n"
		, id, largeur, longueur, position->getX(), position->getY(), conteneur);
}