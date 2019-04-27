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
    virtual void modeliser();
    virtual bool testPresenceCar(Pos3D pos) = 0;
    virtual void setCar(Cars* car);
    virtual bool hasCar();
protected:
    float width;
    Pos3D origin;
    Direction dir;
    Cars* car;
};

