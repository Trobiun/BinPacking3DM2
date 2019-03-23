#include "Dir3D.h"

Dir3D::Dir3D(void) : CH3D(0.0, 0.0, 0.0, 0.0) {

}

Dir3D::Dir3D(float dx, float dy, float dz) : CH3D(dx, dy, dz, 0.0) {

}

Dir3D::Dir3D(Dir3D *d) : CH3D(d) {

}

Dir3D::Dir3D(Pos3D *pi, Pos3D *pf) {
    c[0] = pf->c[0] - pi->c[0];
    c[1] = pf->c[1] - pi->c[1];
    c[2] = pf->c[2] - pi->c[2];
    c[3] = pf->c[3] - pi->c[3];
}

Dir3D::~Dir3D() {

}

double Dir3D::norme() {
    return 0;
}