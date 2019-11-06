#include "../../Include/2D/Position2D.h"

#include <stdlib.h>
#include <stdio.h>

Position2D::Position2D(void) {
	x = 0.0;
	z = 0.0;
}

Position2D::Position2D(float nx, float nz) {
	x = nx;
	z = nz;
}

Position2D::~Position2D(void) {
}

/* Getters                                  */

float Position2D::getX(void) {
	return x;
}

float Position2D::getZ(void) {
	return z;
}


/* Setters                                  */

bool Position2D::setX(float nx) {
	x = nx;
	return true;
}

bool Position2D::setZ(float nz) {
	z = nz;
	return true;
}
