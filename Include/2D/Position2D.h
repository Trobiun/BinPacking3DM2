#ifndef ____POSITION2D____
#define ____POSITION2D____

#include <GL/gl.h>

class Position2D {
	protected :
		float x;
		float y;
	public :

		/* Constructeurs                            */

		Position2D(void);
		Position2D(float x,float y);

		/* Destructeur                              */

		~Position2D(void);

		/* Setters                             */

		virtual bool setX(float x);
		virtual bool setY(float y);

		/* Getters                              */

		float getX();
		float getY();
};

#endif
