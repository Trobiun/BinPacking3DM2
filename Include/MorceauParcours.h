#pragma once
#include "Pos3D.h"
#include "Cars.h"

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
<<<<<<< HEAD
    virtual void modeliser();
=======
	void chargementTexture(char * filename, unsigned int textureID);
    virtual void modeliser() = 0;
>>>>>>> 22a79f2a1f94ad7ce8a129fd8a110802265bb15e
    virtual bool testPresenceCar(Pos3D pos) = 0;
    virtual void setCar(Cars* car);
    virtual bool hasCar();
protected:
    float width;
    Pos3D origin;
    Direction dir;
    Cars* car;
};

