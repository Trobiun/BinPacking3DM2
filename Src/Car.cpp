#include <GL/gl.h>
#include <GL/glut.h>
#include "Car.h"

Car::Car() {
}

Car::Car(float height, float width, float length, Pos3D pos, float angle)
: Object3D(height, width, length, pos, angle) {
}

Car::Car(const Car& orig) {
}

Car::~Car() {
}

void Car::create() {
    glutSolidCube(1.0);
}