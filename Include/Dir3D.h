#ifndef DIR3D_H
#define DIR3D_H

#include "CH3D.h"
#include "Pos3D.h"

class Dir3D : public CH3D {
public:
    Dir3D(void);
    Dir3D(float dx, float dy, float dz);
    Dir3D(Dir3D *d);
    Dir3D(Pos3D *pi, Pos3D *pf);
    ~Dir3D();
	double norme();
};

#endif /* DIR3D_H */

