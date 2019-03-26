#include <GL/gl.h>
#include "MorceauParcoursLigne.h"

MorceauParcoursLigne::MorceauParcoursLigne(Pos3D origin, float height, float width, Direction dir) : MorceauParcours(origin, height, dir) {
    this->width = width;
}

MorceauParcoursLigne::~MorceauParcoursLigne() {
}

void MorceauParcoursLigne::modeliser() {
    glBegin(GL_QUAD_STRIP);
	glPushMatrix();
	//glTranslatef(origin.x, 0.0, origin.z);
    glNormal3f(0.0F, 0.0F, -1.0F);
    glVertex3f(0.0F, 0.0F, 0.0F);
    glVertex3f(0.0F, 0.0F, length);
    glVertex3f(width, 0.0F, 0.0F);
    glVertex3f(width, 0.0F, length);
	glPopMatrix();
    glEnd();
}
