#include <GL/gl.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "MorceauParcoursVirage.h"

MorceauParcoursVirage::MorceauParcoursVirage(Pos3D origin, float height, float maxRadius) : MorceauParcours(origin, height) {
	this->maxRadius = maxRadius;
}

MorceauParcoursVirage::~MorceauParcoursVirage()
{
}

void MorceauParcoursVirage::modeliser() {
	glBegin(GL_QUAD_STRIP);
	double a;
	double xmax, xmin;
	double zmax, zmin;
	for (int i = 0; i <= NB_FACETS; i++) {
		a = (2 * M_PI *i / 4) / NB_FACETS;
		xmax = maxRadius * cos(a);
		zmax = -maxRadius * sin(a);
		glNormal3f(cos(a), 0.0, -sin(a));
		glVertex3f(xmax, 0, zmax);

		xmin = maxRadius * cos(a);
		zmin = -(maxRadius - height) * sin(a);
		//glNormal3f(cos(a), 0.0, -sin(a));
		glVertex3f(xmin, 0, zmin);
	}
	glEnd();
}