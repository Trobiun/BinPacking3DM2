#pragma once
#include "Pos3D.h"

class MorceauParcours {

public: enum Direction
	{
		EST,
		OUEST,
		NORD,
		SUD
	};

public:
    MorceauParcours(Pos3D origin, float width, Direction dir);
    virtual ~MorceauParcours();

    Pos3D getPosition();
    virtual void modeliser();
protected:
    float width;
    Pos3D origin;
	Direction dir;
};

