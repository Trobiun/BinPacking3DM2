#include <cmath>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Cars.h"
#include "RT3D.h"
#include "TR3D.h"

#define MAX_VITESSE 60.0
#define MAX_RECUL -20
#define MAX_SPEED 80.0
#define ACCELERATION_FACTOR 10.0
#define ANGLE_FACTOR 20.0

Cars::Cars() {
}

Cars::Cars(float height, float width, float length, Pos3D pos, float angle)
	: Object3D(height, width, length, pos, angle) {
	accel = 0;
	vitesse = 0;
	rotation = 0;
}

Cars::~Cars() {
}

void Cars::create() {
	glutSolidCube(1.0);
	glBegin(GL_LINES);
	//glVertex3f(0, 0, 0);
	//glVertex3f(1.0, 0.0, 0.0);

	glEnd();
}

void Cars::accelerate(int accelerating) {
	if (accelerating > 0) {
		if (vitesse < 0) {
			vitesse += 0.003;
		}else if ( vitesse < MAX_VITESSE ) {
			vitesse += 0.001;
		}
	}else if ( accelerating < 0 ){
		if (vitesse > 0) {
			vitesse -= 0.003;
		}
		else if(vitesse > MAX_RECUL) {
			vitesse -= 0.001;
		}
	}else {
		if (vitesse > 0) {
			vitesse -= 0.001;
		}
		if (vitesse < 0) {
			vitesse += 0.001;
		}
	}
}

void Cars::move() {
	double angleT = -angle;
	printf("angle = %d\n", this->angle);

	if (angleT >= 0 && angleT < 90) {
		float deplacex = sin(angleT)*vitesse;
		float deplacez = cos(angleT)*vitesse;
		position.x += deplacex;
		position.z += deplacez;
	}

	if (angleT >= 90 && angleT < 180) {
		angleT -= 90;
		float deplacex = sin(angleT)*vitesse;
		float deplacez = cos(angleT)*vitesse;
		position.x += deplacex;
		position.z += deplacez;
	}	
	if (angleT >= 180 && angleT < 170) {
		angleT -= 180;
		float deplacex = -cos(angleT)*vitesse;
		float deplacez = sin(angleT)*vitesse;
		position.x += deplacex;
		position.z += deplacez;
	}	
	if (angleT >= 270 && angleT < 360) {
		angleT -= 270;
		float deplacex = sin(angleT)*vitesse;
		float deplacez = -cos(angleT)*vitesse;
		position.x += deplacex;
		position.z += deplacez;
	}
}

void Cars::moveG() {
	this->angle++;
	if (angle > 0) {
		angle = angle - 360;
	}
	printf("angle++\n", angle);


}



void Cars::moveD() {
	this->angle--;
	if (angle <= -360) {
		angle += 360;
	}
	printf("angle--\n", angle);
}

void modifPos(int i, int j) {

}