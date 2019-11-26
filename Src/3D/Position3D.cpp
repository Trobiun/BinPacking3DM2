#include "3D/Position3D.h"

Position3D::Position3D(void) : Position3D(0.0, 0.0, 0.0) {
}

Position3D::Position3D(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {
    
}

Position3D::~Position3D(void) {
}

/* Getters                                  */

float Position3D::getX(void) {
    return x;
}

float Position3D::getY(void) {
    return y;
}
float Position3D::getZ(void) {
	return z;
}

/* Setters                                  */

bool Position3D::setX(float nx) {
    x = nx;
    return true;
}

bool Position3D::setY(float ny) {
    y = ny;
    return true;
}
bool Position3D::setZ(float nz) {
	z = nz;
	return true;
}
