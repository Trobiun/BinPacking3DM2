#include <GL/gl.h>
#include <stdio.h>
#include "MorceauParcoursLigne.h"

MorceauParcoursLigne::MorceauParcoursLigne(Pos3D origin, float width, float length, Direction dir) : MorceauParcours(origin, width, dir) {
    this->length = length;
}

MorceauParcoursLigne::~MorceauParcoursLigne() {
}

void MorceauParcoursLigne::modeliser() {
    glPushMatrix();
    glTranslatef(origin.x, 0.0, origin.z);
    glBegin(GL_QUADS);
    float blanc[] = {1.0F, 1.0F, 1.0F, 1.0F};
    float rouge[] = {1.0F, 0.0F, 0.0F, 1.0F};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);
    if (dir == NORD || dir == SUD) {
        glNormal3f(0.0F, 1.0F, 0.0F);
        creationMorceauVertical(width, length, 0.0);
		glEnd();
		glBegin(GL_QUADS);

        //creation des deux bordures	
        glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);
        creationBordureVerticale(-2, length, 0.0);
        creationBordureVerticale(2, length, width);
    }
    else {
        glNormal3f(0.0F, 1.0F, 0.0F);
        creationMorceauHorizontal(width, length, 0.0);
		glEnd();
		glBegin(GL_QUADS);

        //creation des deux bordures
        glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);
        creationBordureHorizontale(-2, length, 0.0);
        creationBordureHorizontale(2.0, length, width);
    }
    glEnd();
    glPopMatrix();
}

void MorceauParcoursLigne::creationMorceauVertical(float width, float length, float decalage) {
	glTexCoord2d(0, 0);
	glVertex3f(decalage, 0.0F, 0.0F);
	glTexCoord2d(0, length);
	glVertex3f(decalage, 0.0F, length);
	glTexCoord2d(width, length);
	glVertex3f(decalage + width, 0.0F, length);
	glTexCoord2d(width, 0);
	glVertex3f(decalage + width, 0.0F, 0.0F);
}

void MorceauParcoursLigne::creationBordureVerticale(float width, float length, float decalage) {
	glVertex3f(decalage, 0.0F, 0.0F);
	glVertex3f(decalage, 0.0F, length);
	glVertex3f(decalage + width, 0.0F, length);
	glVertex3f(decalage + width, 0.0F, 0.0F);
}

void MorceauParcoursLigne::creationMorceauHorizontal(float width, float length, float decalage) {
	glTexCoord2d(0, 0);
	glVertex3f(0.0F, 0.0F, decalage);
	glTexCoord2d(0, length);
	glVertex3f(length, 0.0F, decalage);
	glTexCoord2d(width, length);
	glVertex3f(length, 0.0F, decalage + width);
	glTexCoord2d(width, 0);
	glVertex3f(0.0F, 0.0F, decalage + width);
}

void MorceauParcoursLigne::creationBordureHorizontale(float width, float length, float decalage) {
	glVertex3f(0.0F, 0.0F, decalage);
	glVertex3f(length, 0.0F, decalage);
	glVertex3f(length, 0.0F, decalage + width);
	glVertex3f(0.0F, 0.0F, decalage + width);
}

bool MorceauParcoursLigne::testPresenceCar(Pos3D pos) {
    bool res = false;
    if (dir == NORD || dir == SUD) {
        res = pos.x >= origin.x && pos.x <= origin.x + width && pos.z >= origin.z && pos.z <= origin.z + length;
    }
    else {
        res = pos.x >= origin.x && pos.x <= origin.x + length && pos.z >= origin.z && pos.z <= origin.z + width;
    }
    return res;
}