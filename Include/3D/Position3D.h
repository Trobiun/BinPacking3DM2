#ifndef ____POSITION3D____
#define ____POSITION3D____

#include <GL/gl.h>

class Position3D{
protected:
	float x;
	float y;
	float z;
public:

	/* Constructeurs                            */

	Position3D(void);
	Position3D(float x, float y, float z);

	/* Destructeur                              */

	~Position3D(void);

	/* Setters                             */

	virtual bool setX(float x);
	virtual bool setY(float y);
	virtual bool setZ(float z);

	/* Getters                              */

	float getX();
	float getY();
	float getZ();
};

#endif
