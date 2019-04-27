#include <GL/gl.h>
#include "MorceauParcours.h"

MorceauParcours::MorceauParcours(Pos3D origin, float width, Direction dir) {
    this->origin = origin;
    this->width = width;
    this->dir = dir;
}

MorceauParcours::~MorceauParcours() {
}

Pos3D MorceauParcours::getPosition() {
    return origin;
}

void MorceauParcours::modeliser() {

}

void MorceauParcours::setCar(Cars* car) {
    this->car = car;
}

bool MorceauParcours::hasCar() {
    return car != NULL;
}