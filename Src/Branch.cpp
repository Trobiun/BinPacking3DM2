#include <stdio.h>
#include <stdlib.h>
#include "Branch.h"
#include "GL/glut.h"

Branch::Branch(float height, float width, Pos3D pos, float angle) : Object3D(height, width, width, pos, angle) {

}

Branch::~Branch() {
}

static void makeCylinder(float height, float base) {
	GLUquadric *obj = gluNewQuadric();
	//gluQuadricDrawStyle(obj, GLU_LINE);
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, base, base - (0.2*base), height, 20, 20);
	glPopMatrix();
}

void Branch::create() {
	makeCylinder(height, width);
}

