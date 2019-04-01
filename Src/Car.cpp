#include <cmath>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Car.h"
#include "RT3D.h"
#include "TR3D.h"

#define MAX_ACCELERATION 60.0
#define MAX_SPEED 80.0
#define ACCELERATION_FACTOR 10.0
#define ANGLE_FACTOR 20.0

Car::Car() {
}

Car::Car(float height, float width, float length, Pos3D pos, float angle)
: Object3D(height, width, length, pos, angle) {
    acceleration = Dir3D(0.0, 0.0, 0.0);
    vitesse = Dir3D(0.0, 0.0, 0.0);
    vitesseLaterale = Dir3D(0, 0, 0);
    direction = Dir3D(1.0, 0.0, 0.0);
    timeAccel = 0;
    this->angle = 0.0;
    this->angle2 = 0.0;
    this->angleInput = 0.0;
    virage = false;
}

Car::Car(const Car& orig) {
    acceleration = Dir3D(0.0, 0.0, 0.0);
    vitesse = Dir3D(0.0, 0.0, 0.0);
    direction = Dir3D(1.0, 0.0, 0.0);
    timeAccel = 0;
    angle = 0;
    angle2 = 0.0;
    virage = false;
}

Car::~Car() {
}

void Car::create() {
    //glutSolidCube(1.0);
    glBegin(GL_LINES);
    //glVertex3f(0, 0, 0);
    //glVertex3f(1.0, 0.0, 0.0);
    glVertex3d(0, 0, 0);
    glVertex3d(acceleration.x, acceleration.y, acceleration.z);
    glVertex3d(0, 0, 0);
    glVertex3d(vitesse.x, vitesse.y, vitesse.z);
    glVertex3d(0, 0, 0);
    glVertex3d(direction.x, direction.y, direction.z);
    glEnd();
}

void Car::accelerate(bool accelerating) {
    if (accelerating) {
        if (timeAccel < MAX_ACCELERATION) {
            timeAccel += 1;
        }
    }
    else {
        if (timeAccel > 0) {
            timeAccel -= 1;
        }
    }
}

void Car::move() {
    acceleration.x = direction.x * accelerationInput * ACCELERATION_FACTOR;
    acceleration.y = direction.y * accelerationInput * ACCELERATION_FACTOR;
    acceleration.z = direction.z * accelerationInput * ACCELERATION_FACTOR;

    double steer_angle = angleInput * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED);
	printf("%lf\n",steer_angle);
    RT3D rotation = RT3D(steer_angle, 0.0, 1.0, 0.0);
    rotation.transformation(&this->direction, &this->direction);
    //Dir3D droite;
    //RT3D rotationDroite = RT3D(-90, 0.0, 1.0, 0.0);
    //rotationDroite.transformation(&direction, &droite);

    double currentSpeed = vitesse.norme();
    if (currentSpeed < MAX_SPEED) {
        vitesse.x += acceleration.x * 1.0 / 60.0;
        vitesse.y += acceleration.y * 1.0 / 60.0;
        vitesse.z += acceleration.z * 1.0 / 60.0;
    }
    position.x += vitesse.x * 1.0 / 60.0;
    position.y += vitesse.y * 1.0 / 60.0;
    position.z += vitesse.z * 1.0 / 60.0;
}

void Car::moveForward() {
    //
    //    acceleration.x = direction.x * accelerationInput * ACCELERATION_FACTOR;
    //    acceleration.y = direction.y * accelerationInput * ACCELERATION_FACTOR;
    //    acceleration.z = direction.z * accelerationInput * ACCELERATION_FACTOR;
    //    acceleration.x = direction.x * 1 * ACCELERATION_FACTOR;
    //    acceleration.y = direction.y * 1 * ACCELERATION_FACTOR;
    //    acceleration.z = direction.z * 1 * ACCELERATION_FACTOR;
    //    Dir3D accel = Dir3D(&direction);
    //    accel.x += acceleration.x * ACCELERATION_FACTOR;
    //    accel.y += acceleration.y * ACCELERATION_FACTOR;
    //    accel.z += acceleration.z * ACCELERATION_FACTOR;

    //    accel.normalisation();
    //    if (timeAccel > 0) {
    //        vitesse.x = accel.x * timeAccel / MAX_ACCELERATION * 1; //(MAX_ACCELERATION / timeAccel);
    //        vitesse.y = accel.y * timeAccel / MAX_ACCELERATION * 1; //(MAX_ACCELERATION / timeAccel);
    //        vitesse.z = accel.z * timeAccel / MAX_ACCELERATION * 1; //(MAX_ACCELERATION / timeAccel);
    //    }
    //    else {
    //        vitesse.x = accel.x * 0.1;
    //        vitesse.y = accel.y * 0.1;
    //        vitesse.z = accel.z * 0.1;
    //    }
    //    vitesse = accel;timeAccel % MAX_ACCELERATION;
    //    direction = vitesse;
}

void Car::moveBackward() {

}

void Car::rotateAngle(int diff) {

}

void Car::setAngleInput(double input) {
    angleInput = input;
}

void Car::moveLeft() {
    angleInput = 1;
    //    printf("%lf\n", angle2);
    //    if (angle2 < 180) {
    //
    //        angle2 += 1 * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED);
    //        RT3D rotation = new RT3D(1 * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED), 0.0, 1.0, 0.0);
    //        rotation.transformation(&direction, &direction);
    //    }
    //    Dir3D accel;
    //    RT3D rotation = new RT3D(90, 0.0, 1.0, 0.0);
    //    rotation.transformation(&direction, &accel);
    //    accel.normalisation();
    //    this->acceleration = accel;
}

void Car::moveRight() {
    angleInput = -1;
    //    Dir3D accel;
    //    printf("%lf\n", angle2);
    //    if (angle2 > -180) {
    //
    //        angle2 -= 1 * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED);
    //        RT3D rotation = new RT3D(-1 * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED), 0.0, 1.0, 0.0);
    //        rotation.transformation(&direction, &direction);
    //    }
    //    }
    //    acceleration = direction;
    //    direction = accel;
    //    Dir3D accel;
    //    RT3D rotation = new RT3D(-90, 0.0, 1.0, 0.0);
    //    rotation.transformation(&direction, &accel);
    //    accel.normalisation();
    //    this->acceleration = accel;
}

void Car::setAccelerationInput(double input) {
    this->accelerationInput = input;
}