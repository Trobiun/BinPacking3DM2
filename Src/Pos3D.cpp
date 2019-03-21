#include <math.h>
#include "Pos3D.h"

Pos3D::Pos3D(void) : CH3D(0.0, 0.0, 0.0, 1.0) {

}

Pos3D::Pos3D(float px, float py, float pz) : CH3D(px, py, pz, 1.0) {

}

Pos3D::Pos3D(Pos3D *p) : CH3D(p) {

}

Pos3D::~Pos3D() {
    
}

double Pos3D::distance(Pos3D *p) {
	return distance(this, p);
}

double Pos3D::distance(Pos3D *p1, Pos3D *p2) {
	double dx = p1->c[0] - p2->c[0];
	double dy = p1->c[1] - p2->c[1];
	double dz = p1->c[2] - p2->c[2];
	return sqrt(dx*dx + dy*dy + dz*dz);
}