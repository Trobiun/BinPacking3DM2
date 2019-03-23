#include <GL/gl.h>
#include "MorceauParcoursLigne.h"

MorceauParcoursLigne::MorceauParcoursLigne(Pos3D origin, float height, float width) : MorceauParcours(origin, height) {
    this->width = width;
}

MorceauParcoursLigne::~MorceauParcoursLigne() {
}

void MorceauParcoursLigne::modeliser() {
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0.0F, 0.0F, -1.0F);
    glVertex3f(0.0F, 0.0F, 0.0F);
    glVertex3f(0.0F, 0.0F, height);
    glVertex3f(width, 0.0F, 0.0F);
    glVertex3f(width, 0.0F, height);
    glEnd();
}
