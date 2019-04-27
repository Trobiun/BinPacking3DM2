#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
#include "GL/glut.h"

Tree::Tree(float height, float width, Pos3D pos, float angle) : Object3D(height, width, width, pos, angle) {
	this->radius = radius;
}

Tree::~Tree() {
}

void Tree::create() {
	makeTree(height, width);
}

static void makeCylinder(float height, float base) {
	GLUquadric *obj = gluNewQuadric();
	//gluQuadricDrawStyle(obj, GLU_LINE);
	glColor3f(0.64f, 0.16, 0.16f); glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, base, base - (0.2*base), height, 20, 20);
	glPopMatrix();
	glutSwapBuffers();
}

void Tree::makeTree(float height, float base) {

	branch.push_front(new Branch(1.0, 1.0, new Pos3D(), 1.0));
	float angle;
	makeCylinder(height, base); glTranslatef(0.0, height, 0.0);
	height -= height * .2; base -= base * 0.3;
	for (int a = 0; a < 3; a++) {
		angle = rand() % 50 + 20;
		if (angle > 48)
			angle = -(rand() % 50 + 20);
		if (height > 1) {
			glPushMatrix();
			glRotatef(angle, 1, 0.0, 1);
			makeTree(height, base);
			glPopMatrix();

		}
	}
}