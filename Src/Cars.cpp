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
    deplacex = 0;
    deplacez = 0;
}

Cars::~Cars() {
}

void Cars::create() {
    glutSolidCube(1.0);
}

void Cars::accelerate(int accelerating) {
    if (accelerating > 0) {
        if (vitesse < 0) {
            vitesse += 0.003;
        }
        else if (vitesse < MAX_VITESSE) {
            vitesse += 0.001;
        }
    }
    else if (accelerating < 0) {
        if (vitesse > 0) {
            vitesse -= 0.003;
        }
        else if (vitesse > MAX_RECUL) {
            vitesse -= 0.001;
        }
    }
    else {
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
    //	printf("angle = %lf\n", this->angle);
    deplacex = 0.0, deplacez = 0.0;
    if (angleT >= 0 && angleT < 90) {
        angleT = angleT * 3.14 / 180;
        deplacex = cos(angleT) * vitesse;
        deplacez = sin(angleT) * vitesse;
        //		printf("angle = %lf, virage x %lf\n", angleT, cos(angleT));
    }
    if (angleT >= 90 && angleT < 180) {
        angleT -= 90;
        angleT = angleT * 3.14 / 180;
        deplacex = -sin(angleT) * vitesse;
        deplacez = cos(angleT) * vitesse;
    }
    if (angleT >= 180 && angleT < 270) {
        angleT -= 180;
        angleT = angleT * 3.14 / 180;
        deplacex = -cos(angleT) * vitesse;
        deplacez = -sin(angleT) * vitesse;
    }
    if (angleT >= 270 && angleT < 360) {
        angleT -= 270;
        angleT = angleT * 3.14 / 180;
        deplacex = sin(angleT) * vitesse;
        deplacez = -cos(angleT) * vitesse;
    }
    position.x += deplacex;
    position.z += deplacez;
}

void Cars::moveG() {
    this->angle++;
    if (angle > 0) {
        angle = angle - 360;
    }
    //    printf("angle++\n", angle);
}

void Cars::moveD() {
    this->angle--;
    if (angle <= -360) {
        angle += 360;
    }
    //    printf("angle--\n", angle);
}

void modifPos(int i, int j) {

}

float Cars::getVitesse() {
    return vitesse;
}

float Cars::getDeplaceX() {
    return deplacex;
}

float Cars::getDeplaceZ() {
    return deplacez;
}