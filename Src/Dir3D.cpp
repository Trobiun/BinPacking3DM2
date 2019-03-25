#include "Dir3D.h"
#include "Pos3D.h"
#include "CH3D.h"
#include "Math.h"

Dir3D::Dir3D(void):CH3D(0.0, 0.0, 0.0, 0.0) {
}

Dir3D::Dir3D(double x, double y, double z) : CH3D(x, y, z, 0.0) {
}

Dir3D::Dir3D(Dir3D *ch) : CH3D(ch) {
}

Dir3D::Dir3D(Pos3D *pi, Pos3D *pf) {
	c[0] = pf->c[0] - pi->c[0];
	c[1] = pf->c[1] - pi->c[1];
	c[2] = pf->c[2] - pi->c[2];
	c[3] = 0;
}

Dir3D::~Dir3D(void) {
}

double Dir3D::norme(void) {
	return(sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]));
}

void Dir3D::normalisation(void) {
	double d = norme();
	if (d != 0.0) {
		c[0] /= d;
		c[1] /= d;
		c[2] /= d;
	}
}

//s'appel avec DIR1.produitScalraire(Dir2)
double Dir3D::produitScalaire(Dir3D *d) {
	//On appel la methode static avec deux directions
	return(produitScalaire(this, d));
}

//methode static s'appelle avec Dir3D::produitScalaire(DIR1, DIR2)
double Dir3D::produitScalaire(Dir3D *d1, Dir3D *d2) {
	return(d1->c[0] * d2->c[0] + d1->c[1] * d2->c[1] + d1->c[2] * d2->c[2]);
}

void Dir3D::produitVectoriel(Dir3D *d) {
	double x = this->c[1] * d->c[2] - this->c[2] * d->c[1];
	double y = this->c[2] * d->c[0] - this->c[0] * d->c[2];
	double z = this->c[0] * d->c[1] - this->c[1] * d->c[0];
	this->c[0] = x;
	this->c[1] = y;
	this->c[2] = z;
	this->c[3] = 0;
}

Dir3D *Dir3D::produitVectoriel(Dir3D *d1, Dir3D *d2) {
	double x = d1->c[1] * d2->c[2] - d1->c[2] * d2->c[1];
	double y = d1->c[2] * d2->c[0] - d1->c[0] * d2->c[2];
	double z = d1->c[0] * d2->c[1] - d1->c[1] * d2->c[0];
	/*x --> y1*z2 - z1*y2
	y --> z1*x2 - x1*z2
	z --> x1*y2 - y1*x2*/
	return (new Dir3D(x, y, z));
}

