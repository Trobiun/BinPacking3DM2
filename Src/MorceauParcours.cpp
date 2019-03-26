#include <GL/gl.h>
#include "MorceauParcours.h"

MorceauParcours::MorceauParcours(Pos3D origin, float length, Direction dir) {
    this->origin = origin;
    this->length = length;
	this->dir = dir;
}

MorceauParcours::~MorceauParcours() {
}

Pos3D MorceauParcours::getPosition() {
    return origin;
}

void MorceauParcours::modeliser() {

}