#include "Wheel.h"
#include "GL/glut.h"

Wheel::Wheel(Pos3D pos, float angle) : Object3D(0.3, 0.3, 0.3, pos, angle) {
}

Wheel::~Wheel() {
}

void Wheel::create() {
    glutSolidTorus(0.5, 0.75, 10, 10);
}