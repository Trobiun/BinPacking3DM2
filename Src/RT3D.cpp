#include <stdio.h>
#include "TG3D.h"
#include "RT3D.h"
#include "Dir3D.h"
#define _USE_MATH_DEFINES
#include <cmath>

RT3D::RT3D(void) : TG3D() {

}

RT3D::RT3D(RT3D *rt) : TG3D(rt) {
}

RT3D::RT3D(double alpha, Dir3D *d) : TG3D() {
	construction(this, alpha, d->x, d->y, d->z);
}

RT3D::RT3D(double alpha, double ax, double ay, double az) : TG3D() {
	construction(this, alpha, ax, ay, az);
}

RT3D::~RT3D(void) {
}

/* dans le sujet on dit qu'on re�oit alpha en degr�, la fonction cos et sin utilise des radiants on doit convertir*/
void RT3D::construction(RT3D *rt, double alpha, double ax, double ay, double az) {
	Dir3D axe = Dir3D(ax, ay, az);
	axe.normalisation();
	double x = axe.x;
	double y = axe.y;
	double z = axe.z;
	double aa = alpha / 180.0 * M_PI;
	double sn = sin(aa);
	double cs = cos(aa);
	rt->c[0][0] = (double)(x * x + cs * (1 - x * x));
	rt->c[0][1] = (double)(x * y * (1 - cs) - sn * z);
	rt->c[0][2] = (double)(x * z * (1 - cs) + sn * y);
	rt->c[1][0] = (double)(x * y * (1 - cs) + sn * z);
	rt->c[1][1] = (double)(y * y + cs * (1 - y * y));
	rt->c[1][2] = (double)(y * z * (1 - cs) - sn * x);
	rt->c[2][0] = (double)(x * z * (1 - cs) - sn * y);
	rt->c[2][1] = (double)(y * z * (1 - cs) + sn * x);
	rt->c[2][2] = (double)(z * z + cs * (1 - z * z));
}