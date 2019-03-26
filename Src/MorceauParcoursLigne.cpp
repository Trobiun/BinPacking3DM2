#include <GL/gl.h>
#include "MorceauParcoursLigne.h"

MorceauParcoursLigne::MorceauParcoursLigne(Pos3D origin, float width, float length, Direction dir) : MorceauParcours(origin, width, dir) {
    this->length = length;
}

MorceauParcoursLigne::~MorceauParcoursLigne() {
}

void MorceauParcoursLigne::modeliser() {
	glPushMatrix();
	glTranslatef(origin.x, 0.0, origin.z);
	glBegin(GL_QUAD_STRIP);

	if (dir == EST || dir == OUEST) {
		glNormal3f(0.0F, 1.0F, 0.0F);
		glVertex3f(0.0F, 0.0F, 0.0F);
		glVertex3f(0.0F, 0.0F, length);
		glVertex3f(width, 0.0F, 0.0F);
		glVertex3f(width, 0.0F, length);
	}
	else {
		glNormal3f(0.0F, 1.0F, 0.0F);
		glVertex3f(0.0F, 0.0F, 0.0F);
		glVertex3f(0.0F, 0.0F, width);
		glVertex3f(length, 0.0F, 0.0F);
		glVertex3f(length, 0.0F, width);
	}
    glEnd();
	glPopMatrix();
}
