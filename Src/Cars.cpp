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
#define ACCELERATION_FACTOR 30
#define ANGLE_FACTOR 180.0

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

void Cars::accelerate(int accelerating, double timeSinceLastFrame) {
    if (accelerating > 0.0F) {
        if (vitesse < 0.0F) {
            vitesse += timeSinceLastFrame / (0.003 * ACCELERATION_FACTOR);
        }
        else if (vitesse < MAX_VITESSE) {
            vitesse += timeSinceLastFrame / (0.001 * ACCELERATION_FACTOR);
            vitesse = fmin(vitesse, MAX_VITESSE);
        }
    }
    else if (accelerating < 0.0F) {
        if (vitesse > 0.0F) {
            vitesse -= timeSinceLastFrame / (0.001 * ACCELERATION_FACTOR);
            vitesse = fmax(vitesse, MAX_RECUL);
        }
        else if (vitesse > MAX_RECUL) {
            vitesse -= timeSinceLastFrame / (0.001 * ACCELERATION_FACTOR);
            vitesse = fmax(vitesse, MAX_RECUL);
        }
    }
    else {
        if (vitesse > 0.0F) {
            vitesse -= timeSinceLastFrame / (0.001 * ACCELERATION_FACTOR);
            vitesse = fmax(vitesse, MAX_RECUL);
        }
        if (vitesse < 0.0F) {
            vitesse += timeSinceLastFrame / (0.001 * ACCELERATION_FACTOR);
            vitesse = fmin(vitesse, MAX_VITESSE);
        }
    }
}

void Cars::move(double timeSinceLastFrame) {
    double angleT = -angle;
    //	printf("angle = %lf\n", this->angle);
    deplacex = 0.0, deplacez = 0.0;
    if (angleT >= 0 && angleT < 90) {
        angleT = angleT * 3.14 / 180;
        deplacex = cos(angleT);
        deplacez = sin(angleT);
        //		printf("angle = %lf, virage x %lf\n", angleT, cos(angleT));
    }
    if (angleT >= 90 && angleT < 180) {
        angleT -= 90;
        angleT = angleT * 3.14 / 180;
        deplacex = -sin(angleT);
        deplacez = cos(angleT);
    }
    if (angleT >= 180 && angleT < 270) {
        angleT -= 180;
        angleT = angleT * 3.14 / 180;
        deplacex = -cos(angleT);
        deplacez = -sin(angleT);
    }
    if (angleT >= 270 && angleT < 360) {
        angleT -= 270;
        angleT = angleT * 3.14 / 180;
        deplacex = sin(angleT);
        deplacez = -cos(angleT);
    }
    if (fabs(deplacex) < 1 || fabs(deplacez) < 1) {
        deplacex *= vitesse;
        deplacez *= vitesse;
    }
    //    printf("%lf\n", deplacex);
    position.x += deplacex * timeSinceLastFrame;
    position.z += deplacez * timeSinceLastFrame;
}

void Cars::moveG(double timeSinceLastFrame) {
    this->angle += timeSinceLastFrame * ANGLE_FACTOR;
    if (angle > 0) {
        angle = angle - 360;
    }
    //    printf("angle++\n", angle);
}

void Cars::moveD(double timeSinceLastFrame) {
    this->angle -= timeSinceLastFrame * ANGLE_FACTOR;
    if (angle <= -360) {
        angle += 360;
    }
    //    printf("angle--\n", angle);
}

void modifPos(int i, int j) {

}

double Cars::getVitesse() {

    return vitesse;
}

double Cars::getDeplaceX() {

    return deplacex;
}

double Cars::getDeplaceZ() {
    return deplacez;
}