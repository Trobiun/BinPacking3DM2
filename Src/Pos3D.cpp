#include "Dir3D.h"
#include "Pos3D.h"
#include "CH3D.h"
#include <cmath>

Pos3D::Pos3D(void) : CH3D(0.0, 0.0, 0.0, 1.0) {
}

Pos3D::Pos3D(double x, double y, double z) : CH3D(x, y, z, 1.0) {
}

Pos3D::Pos3D(Pos3D *p) : CH3D(p) {
}

Pos3D::~Pos3D(void) {
}

double Pos3D::distance(Pos3D *p) {
    return distance(this, p);
}

/* Methode statique de calcul               */

/* de la distance entre deux positions      */
double Pos3D::distance(Pos3D *p1, Pos3D *p2) {
    double x = p1->c[0] - p2->c[0];
    double y = p1->c[1] - p2->c[1];
    double z = p1->c[2] - p2->c[2];
    return (sqrt(x * x + y * y + z * z));
}