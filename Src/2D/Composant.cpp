#include "2D/Debug.h"
#include <stdio.h>
#include <GL/glut.h>


#include "2D/Composant.h"

Composant::Composant(void) : id(-1), coteX(-1.0), coteY(-1.0), conteneur(-1) {
    position = DBG_NEW Position2D();
}

Composant::Composant(int nid, float nCoteX, float nCoteY) : id(nid), coteX(nCoteX), coteY(nCoteY), conteneur(-1) {
    position = DBG_NEW Position2D();
}

Composant::Composant(int nid, float nCoteX, float nCoteY, Position2D* pos) : id(nid), coteX(nCoteX), coteY(nCoteY), conteneur(-1) {
    position = DBG_NEW Position2D(pos->getX(), pos->getY());
}

Composant::Composant(int nid, float nCoteX, float nCoteY, float posX, float posY) : id(nid), coteX(nCoteX), coteY(nCoteY), conteneur(-1) {
    position = DBG_NEW Position2D(posX, posY);
}

Composant::~Composant(void) {
    if (position != nullptr) {
        delete position;
        position = nullptr;
    }
}

/* Getters                                  */

int Composant::getId(void) {
    return id;
}

float Composant::getCoteX(void) const {
    return coteX;
}

float Composant::getCoteY(void) const {
    return coteY;
}

float Composant::getAire(void) {
    return coteY * coteX;
}

Position2D* Composant::getPosition(void) {
    return position;
}

bool Composant::operator<(const Composant* a) {
    if (a->coteX * a->coteY < coteX * coteY) {
        return true;
    }
    return false;
}

/* Setters                                  */


bool Composant::setCoteX(float nCoteX) {
    coteX = nCoteX;
    return true;
}

bool Composant::setCoteY(float nCoteY) {
    coteY = nCoteY;
    return true;
}

bool Composant::setPosition(Position2D* pos) {
    position->setX(pos->getX());
    position->setY(pos->getY());
    return true;
}

bool Composant::setPosition(float posX, float posY) {
    position->setX(posX);
    position->setY(posY);
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
void Composant::model(const GLfloat couleur[4]) {
    glPushMatrix();
    glTranslatef(position->getX() + coteX / 2.0, position->getY() + coteY / 2.0, 0.0);
    glScalef(coteX, coteY, 0.0F);
    glColor4fv(couleur);
    glutSolidCube(1.0);
	GLfloat couleur1[4] = { 0.0F, 0.0F, 1.0F, 0.0F };
	glColor4fv(couleur1);
	glutWireCube(1.0);
    glPopMatrix();
}

/*Affichage */

void Composant::affichageComposant() {
    printf("COMPOSANT : Id = %d, CoteX = %.2f, CoteY = %.2f, Position = (%.2f,%.2f), Conteneur = %d \n"
        , id, coteX, coteY, position->getX(), position->getY(), conteneur);
}