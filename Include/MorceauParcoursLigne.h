#pragma once
#include "MorceauParcours.h"

class MorceauParcoursLigne :
public MorceauParcours {
public:
    MorceauParcoursLigne(Pos3D origin, float length, float width);
    virtual ~MorceauParcoursLigne();
    virtual void modeliser();

protected:
    float width;
};

