#pragma once
#include "MorceauParcours.h"

#define NB_FACETS 20

class MorceauParcoursVirage :
public MorceauParcours {
public:
    MorceauParcoursVirage(Pos3D orgin, float width, float maxRadius, Direction dir, Direction dir2);
    virtual ~MorceauParcoursVirage();

    virtual void modeliser();
protected:
    float maxRadius;
	Direction dir2;

};

