#include "2D/Position2D.h"

Position2D::Position2D(void) : Position2D(0.0, 0.0) {
}

Position2D::Position2D(float nx, float ny) : x(nx), y(ny) {
    
}

Position2D::~Position2D(void) {
}

/* Getters                                  */

float Position2D::getX(void) {
    return x;
}

float Position2D::getY(void) {
    return y;
}


/* Setters                                  */

bool Position2D::setX(float nx) {
    x = nx;
    return true;
}

bool Position2D::setY(float ny) {
    y = ny;
    return true;
}
