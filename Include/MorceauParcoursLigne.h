#pragma once
#include "MorceauParcours.h"

class MorceauParcoursLigne :
public MorceauParcours {
public:
    MorceauParcoursLigne(Pos3D origin, float width, float length, Direction dir);
    virtual ~MorceauParcoursLigne();
    virtual void modeliser();

protected:
    float length;
};

