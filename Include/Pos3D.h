#ifndef POS3D_H
#define POS3D_H

#include "CH3D.h"

class Pos3D : public CH3D {
public:

	Pos3D(void);
	Pos3D(float px, float py, float pz);
	Pos3D(Pos3D *p);
	~Pos3D();

	double distance(Pos3D *p);
	static double distance(Pos3D *p1, Pos3D *p2);

};

#endif /* POS3D_H */