#pragma once

#include "Dir3D.h"
#include "TG3D.h"
class TR3D : public TG3D{

public:

public:
	/* Constructeurs                            */
	TR3D(void);
	TR3D(double tx, double ty, double tz);
	TR3D(Dir3D *d);
	TR3D(TR3D *tg);

	/* Destructeur                              */
	~TR3D(void);

};
