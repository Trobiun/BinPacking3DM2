#include "CH3D.h"
#include <stdio.h>

CH3D::CH3D(void) {
	c[0] = c[1] = c[2] = 0.0;
	c[3] = 1.0;
}

CH3D::CH3D(double x, double y, double z, double w) {
	c[0] = x;
	c[1] = y;
	c[2] = z;
	c[3] = w;
}

CH3D::CH3D(CH3D *ch) {
	c[0] = ch->c[0];
	c[1] = ch->c[1];
	c[2] = ch->c[2];
	c[3] = ch->c[3];
}

CH3D::~CH3D(void) {
}

void CH3D::print(void) {
	printf("%10.4lf %10.4lf %10.4lf %10.4lf", c[0], c[1], c[2], c[3]);
}