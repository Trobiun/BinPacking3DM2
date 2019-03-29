#include <stdio.h>
#include "TG3D.h"
#include "RT3D.h"
#include "Dir3D.h"
#include <cmath>

#define PI 3.14159265359 
RT3D::RT3D(void) :TG3D() {

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

/* dans le sujet on dit qu'on reçoit alpha en degré, la fonction cos et sin utilise des radiants on doit convertir*/
static void construction(RT3D *rt, double alpha, double ax, double ay, double az) {
	Dir3D axe(ax, ay, az);
	axe.normalisation();
	alpha = alpha * PI / 180;
	double co = cos(alpha);
	double si = sin(alpha);
	rt->c[0][0] = (axe.x * axe.x) + co * (1 - axe.x * axe.x);
	rt->c[0][1] = (axe.x * axe.z)*(1-co)-axe.z*si;
	/*.
	.il faut le faire pour les 9 variables meme si la on le fait que pour deux
	.
	.*/
}