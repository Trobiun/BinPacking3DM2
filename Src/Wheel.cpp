#include "Wheel.h"
#include "GL/glut.h"

Wheel::Wheel(float radius, Pos3D pos, float angle) : Object3D(radius, radius, radius, pos, angle) {
    this->radius = radius;
}

Wheel::~Wheel() {
}

void Wheel::create() {
    glutSolidTorus(radius * 1, radius * 1.5, 10, 10);
}