#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#include "2D/Conteneur.h"
#include "2D/ArbreBinaire.h"

Conteneur::Conteneur(void) {
	id = 0;
	largeur = longueur = 0.0;
}

Conteneur::Conteneur(int nid, float nLargeur, float nLongueur){
	id = nid;
	largeur = nLargeur;
	longueur = nLongueur;
	pos = new Position2D();
	arbre = new ArbreBinaire(nLargeur, nLongueur);
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
ArbreBinaire* Conteneur::getArbre(void) {
	return arbre;
}
std::list<Composant*> Conteneur::getListComposant(void) {
	return composants;
}

void Conteneur::model() {
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.0F, 1.0F, 0.0F);
	glVertex2f(pos->getX(), pos->getY());
	glVertex2f(pos->getX(), pos->getY() +largeur);
	glVertex2f(pos->getX() +longueur, pos->getY() +largeur);
	glVertex2f(pos->getX() +longueur, pos->getY());
	glEnd();
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
bool Conteneur::setPosition(Position2D *position) {
	pos = position ;
	return true;
}

bool Conteneur::addComposant(Composant * comp) {
	comp->setConteneur(id);
	composants.push_back(comp);
	return true;
}

ArbreBinaire* Conteneur::rechercheLibre(float largeur, float longueur) {
	return arbre->recherchePremierEspaceLibreValide(largeur, longueur);
}

void Conteneur::affichageConteneur() {
	printf("CONTENEUR : Id = %d, Largeur = %.2f, Longueur = %.2f, Position = (%.2f,%.2f), Liste des composants = \n"
		, id, largeur, longueur, pos->getX(), pos->getY());
	if (composants.empty()) {
		printf("Aucun.  \n");
	}
	else {
		std::list<Composant*>::iterator it;
		for (it = composants.begin(); it != composants.end(); it++) {
			(*it)->affichageComposant();
		}
	}
}