#include <2D/Debug.h>
#include <stdio.h>
#include <GL/glut.h>


#include "3D/Composant3D.h"

Composant3D::Composant3D(void) : id(-1), coteX(-1.0), coteY(-1.0), coteZ(-1.0), conteneur(-1) {
    position = DBG_NEW Position3D();
}
Composant3D::Composant3D(int nid, float nCoteX, float nCoteY, float nCoteZ) : id(nid), coteX(nCoteX), coteY(nCoteY), coteZ(nCoteZ), conteneur(-1) {
	position = DBG_NEW Position3D();
}
Composant3D::Composant3D(int nid, float nCoteX, float nCoteY, float nCoteZ, std::vector<int> tab) : id(nid), coteX(nCoteX), coteY(nCoteY), coteZ(nCoteZ), conteneur(-1) {
	orientationPossible = tab;
	position = DBG_NEW Position3D();
}

Composant3D::Composant3D(int nid, float nCoteX, float nCoteY, float nCoteZ, Position3D* pos) : id(nid), coteX(nCoteX), coteY(nCoteY), coteZ(nCoteZ), conteneur(-1) {
    position = DBG_NEW Position3D(pos->getX(), pos->getY(), pos->getZ());
}

Composant3D::Composant3D(int nid, float nCoteX, float nCoteY, float nCoteZ, float posX, float posY, float posZ) : id(nid), coteX(nCoteX), coteY(nCoteY), coteZ(nCoteZ), conteneur(-1) {
    position = DBG_NEW Position3D(posX, posY, posZ);
}

Composant3D::~Composant3D(void) {
    if (position != nullptr) {
        delete position;
        position = nullptr;
    }
}

/* Getters                                  */

int Composant3D::getId(void) {
    return id;
}

float Composant3D::getCoteX(void) const {
    return coteX;
}

float Composant3D::getCoteY(void) const {
    return coteY;
}

float Composant3D::getCoteZ(void) const {
	return coteZ;
}

float Composant3D::getVolume(void) {
    return coteY * coteX * coteZ;
}

Position3D* Composant3D::getPosition(void) {
    return position;
}
std::vector<int> Composant3D::getTabOrientation(void) const {
	return orientationPossible;
}

bool Composant3D::operator<(const Composant3D* a) {
    if (a->coteX * a->coteY * a->coteZ < coteX * coteY * coteZ) {
        return true;
    }
    return false;
}

/* Setters                                  */


bool Composant3D::setCoteX(float nCoteX) {
    coteX = nCoteX;
    return true;
}

bool Composant3D::setCoteY(float nCoteY) {
    coteY = nCoteY;
    return true;
}


bool Composant3D::setCoteZ(float nCoteZ) {
	coteZ = nCoteZ;
	return true;
}

bool Composant3D::setPosition(Position3D* pos) {
    position->setX(pos->getX());
    position->setY(pos->getY());
	position->setZ(pos->getZ());
    return true;
}

bool Composant3D::setPosition(float posX, float posY, float posZ) {
    position->setX(posX);
    position->setY(posY);
	position->setY(posZ);
    return true;
}

bool Composant3D::setTabOrientation(std::vector<int> tab) {
	orientationPossible = tab;
	return true;
}
bool Composant3D::setTabOrientation(int face1, int face2, int face3, int face4, int face5, int face6) {
	orientationPossible.push_back(face1);
	orientationPossible.push_back(face2);
	orientationPossible.push_back(face3);
	orientationPossible.push_back(face4);
	orientationPossible.push_back(face5);
	orientationPossible.push_back(face6);
	return true;
}

bool Composant3D::setConteneur(int cont) {
    conteneur = cont;
    return true;
}

int Composant3D::getIdConteneur() {
    return conteneur;
}

/* Mod�lisation */
void Composant3D::model(const GLfloat couleur[4]) {
    glPushMatrix();
    glTranslatef(position->getX() + coteX / 2.0, position->getY() + coteY / 2.0, position->getZ() + coteZ / 2.0);
    glScalef(coteX, coteY, coteZ);
    glColor4fv(couleur);
    glutSolidCube(1.0);
	GLfloat couleur1[4] = { 0.0F, 0.0F, 1.0F, 1.0F };
	glColor4fv(couleur1);
	glutWireCube(1.0);
    glPopMatrix();
}

/*Affichage */

void Composant3D::affichageComposant() {
    printf("COMPOSANT : Id = %d, CoteX = %.2f, CoteY = %.2f, CoteZ = %.2f, Position = (%.2f,%.2f, %.2f), , Conteneur = %d \n"
        , id, coteX, coteY, coteZ, position->getX(), position->getY(), position->getZ(), conteneur);
}