#include <stdio.h>
#include "TG3D.h"
#include "TR3D.h"

TR3D::TR3D(void):TG3D() {
	
}

TR3D::TR3D(TR3D *tr):TG3D(tr) {
}

TR3D::TR3D(Dir3D *d) : TG3D() {
	this->c[0][3] = d->x;
	this->c[1][3] = d->y;
	this->c[2][3] = d->z;
}


TR3D::TR3D(double tx, double ty, double tz) : TG3D() {
	this->c[0][3] = tx;
	this->c[1][3] = ty;
	this->c[2][3] = tz;
}

TR3D::~TR3D(void) {
}

