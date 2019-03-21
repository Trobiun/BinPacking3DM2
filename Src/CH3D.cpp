#include <stdio.h>
#include <iostream>
#include "CH3D.h"

CH3D::CH3D(void) {
    c[0] = 0;
    c[1] = 0;
    c[2] = 0;
    c[3] = 1;
}

CH3D::CH3D(double x, double y, double z, double t) {
    c[0] = x;
    c[1] = y;
    c[2] = z;
    c[3] = t;
}

CH3D::CH3D(CH3D *c) {
    this->c[0] = c->c[0];
    this->c[1] = c->c[1];
    this->c[2] = c->c[2];
    this->c[3] = c->c[3];
}

CH3D::~CH3D() {

}

void CH3D::print() {
    printf("%10.4lf %10.4lf %10.4lf %10.4lf",c[0],c[1],c[2],c[3]);
    //std::cout << this->c[0] << "," << c[1] << "," << c[2] << "," << c[3];
}