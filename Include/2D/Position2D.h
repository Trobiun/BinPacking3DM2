#ifndef ____POSITION2D____
#define ____POSITION2D____


class Position2D {
	protected :
		float x;
		float z;
	public :

		/* Constructeurs                            */

		Position2D(void);
		Position2D(float x,float z);

		/* Destructeur                              */

		~Position2D(void);

		/* Setters                             */

		virtual bool setX(float x);
		virtual bool setZ(float z);

		/* Getters                              */

		float getX();
		float getZ();
};

#endif
