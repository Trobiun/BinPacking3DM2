#pragma once
#include "Pos3D.h"

class MorceauParcours {
public:
    MorceauParcours(Pos3D origin, float height);
    virtual ~MorceauParcours();

    Pos3D getPosition();
    virtual void modeliser();

protected:
    float height;
    Pos3D origin;
};

