#include <GL/gl.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "MorceauParcoursVirage.h"

MorceauParcoursVirage::MorceauParcoursVirage(Pos3D origin, float length, float maxRadius, Direction dir, Direction dir2) : MorceauParcours(origin, length, dir) {
    this->maxRadius = maxRadius;
	this->dir2 = dir2;
}

MorceauParcoursVirage::~MorceauParcoursVirage() {
}

void MorceauParcoursVirage::modeliser() {
    glBegin(GL_QUAD_STRIP);
    double a;
    double xmax, xmin;
    double zmax, zmin;
    for (int i = 0; i <= NB_FACETS; i++) {
        a = (2 * M_PI * i / 4) / NB_FACETS;
        xmax = maxRadius * cos(a);
        zmax = -maxRadius * sin(a);
        glNormal3d(cos(a), 0.0, -sin(a));
        glVertex3d(xmax, 0, zmax);

        xmin = (maxRadius - length) * cos(a);
        zmin = -(maxRadius - length) * sin(a);
        //glNormal3f(cos(a), 0.0, -sin(a));
        glVertex3d(xmin, 0, zmin);
    }
    glEnd();
}