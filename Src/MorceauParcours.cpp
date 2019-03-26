#include <GL/gl.h>
#include "MorceauParcours.h"

MorceauParcours::MorceauParcours(Pos3D origin, float length) {
    this->origin = origin;
    this->length = length;
}

MorceauParcours::~MorceauParcours() {
}

Pos3D MorceauParcours::getPosition() {
    return origin;
}

void MorceauParcours::modeliser() {

}