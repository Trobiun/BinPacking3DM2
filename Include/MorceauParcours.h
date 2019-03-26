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
    MorceauParcours(Pos3D origin, float length, Direction dir);
    virtual ~MorceauParcours();

    Pos3D getPosition();
    virtual void modeliser();
protected:
    float length;
    Pos3D origin;
	Direction dir;
};

