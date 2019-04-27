#pragma once
#include "Pos3D.h"

class MorceauParcours {
public:

    enum Direction {
        EST,
        OUEST,
        NORD,
        SUD
    };

public:
    MorceauParcours(Pos3D origin, float width, Direction dir);
    virtual ~MorceauParcours();

    Pos3D getPosition();
	void chargementTexture(char * filename, unsigned int textureID);
    virtual void modeliser() = 0;
    virtual bool testPresenceCar(Pos3D pos) = 0;
    
protected:
    float width;
    Pos3D origin;
    Direction dir;
};

