#include <GL/gl.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "MorceauParcoursVirage.h"

MorceauParcoursVirage::MorceauParcoursVirage(Pos3D origin, float width, float maxRadius, Direction dir, Direction dir2) : MorceauParcours(origin, width, dir) {
    this->maxRadius = maxRadius;
    this->dir2 = dir2;
}

MorceauParcoursVirage::~MorceauParcoursVirage() {
}

void MorceauParcoursVirage::modeliser() {
    glPushMatrix();
    // fait tourner le virage dans le bon sens
    glTranslatef(this->origin.x, this->origin.y, this->origin.z);
    if ((dir == EST && dir2 == NORD) || (dir == SUD && dir2 == OUEST)) {
        glRotated(270.0, 0.0, 1.0, 0.0);
    }
    else if ((dir == OUEST && dir2 == NORD) || (dir == SUD && dir2 == EST)) {
        glRotated(180.0, 0.0, 1.0, 0.0);
    }
    else if ((dir == NORD && dir2 == EST) || (dir == OUEST && dir2 == SUD)) {
        glRotated(90.0, 0.0, 1.0, 0.0);
    }

    float blanc[] = {1.0F, 1.0F, 1.0F, 1.0F};
    float rouge[] = {1.0F, 0.0F, 0.0F, 1.0F};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);
    //creation du virage
    creationMorceauVirage(maxRadius, width);

    //creation des bordures
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);
    creationMorceauVirage(maxRadius + 2, 2);
    creationMorceauVirage(maxRadius - width, 2);
    glPopMatrix();
}

void MorceauParcoursVirage::creationMorceauVirage(float maxRadius, float width) {
	glBegin(GL_QUAD_STRIP);
	double a;
	double xmax, xmin;
	double zmax, zmin;
	glNormal3d(0, 1.0, 0.0);
	for (int i = 0; i <= NB_FACETS; i++) {
		a = (2 * M_PI * i / 4) / NB_FACETS;
		xmax = maxRadius * cos(a);
		zmax = -maxRadius * sin(a);
		glTexCoord2d(xmax, zmax);
		glVertex3d(xmax, 0, zmax);
		xmin = (maxRadius - width) * cos(a);
		zmin = -(maxRadius - width) * sin(a);
		//glNormal3f(cos(a), 0.0, -sin(a));
		glTexCoord2d(xmin, zmin);
		glVertex3d(xmin, 0, zmin);
	}
	glEnd();
}

void MorceauParcoursVirage::creationBordureVirage(float maxRadius, float width) {
	glBegin(GL_QUAD_STRIP);
	double a;
	double xmax, xmin;
	double zmax, zmin;
	glNormal3d(0, 1.0, 0.0);
	for (int i = 0; i <= NB_FACETS; i++) {
		a = (2 * M_PI * i / 4) / NB_FACETS;
		xmax = maxRadius * cos(a);
		zmax = -maxRadius * sin(a);
		glVertex3d(xmax, 0, zmax);

		xmin = (maxRadius - width) * cos(a);
		zmin = -(maxRadius - width) * sin(a);
		//glNormal3f(cos(a), 0.0, -sin(a));
		glVertex3d(xmin, 0, zmin);
	}
	glEnd();
}

bool MorceauParcoursVirage::testPresenceRectangle(Pos3D pos) {
    bool res = true;
    if ((dir == EST && dir2 == NORD) || (dir == SUD && dir2 == OUEST)) {
        res = true;
    }
    if ((dir == OUEST && dir2 == NORD) || (dir == SUD && dir2 == EST)) {
        res = true;
    }
    if ((dir == NORD && dir2 == EST) || (dir == OUEST && dir2 == SUD)) {
        res = true;
    }
    return res;
}

bool MorceauParcoursVirage::testPresenceCercle(Pos3D pos) {
    double distanceOrigin = origin.distance(&pos);
    return distanceOrigin >= maxRadius - width && distanceOrigin < maxRadius;
}

bool MorceauParcoursVirage::testPresenceCar(Pos3D pos) {
    return testPresenceRectangle(pos) && testPresenceCercle(pos);
}
