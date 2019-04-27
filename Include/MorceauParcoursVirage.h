#pragma once
#include "MorceauParcours.h"

#define NB_FACETS 20

class MorceauParcoursVirage :
public MorceauParcours {
public:
    MorceauParcoursVirage(Pos3D orgin, float width, float maxRadius, Direction dir, Direction dir2);
    virtual ~MorceauParcoursVirage();

    virtual void modeliser();
    void creationMorceauVirage(float maxRadius, float width);
	void creationBordureVirage(float maxRadius, float width);
    virtual bool testPresenceCar(Pos3D pos);
protected:
    float maxRadius;
    Direction dir2;
    bool testPresenceRectangle(Pos3D pos);
    bool testPresenceCercle(Pos3D pos);
};

