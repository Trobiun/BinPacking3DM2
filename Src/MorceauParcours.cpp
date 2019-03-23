#include <GL/gl.h>
#include "MorceauParcours.h"

MorceauParcours::MorceauParcours(Pos3D origin, float height) {
    this->origin = origin;
    this->height = height;
}

MorceauParcours::~MorceauParcours() {
}

Pos3D MorceauParcours::getPosition() {
    return origin;
}

void MorceauParcours::modeliser() {

}