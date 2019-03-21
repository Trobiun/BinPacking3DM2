#pragma once
#include "MorceauParcours.h"

#define NB_FACETS 20

class MorceauParcoursVirage :
	public MorceauParcours
{
public:
	MorceauParcoursVirage(Pos3D orgin, float height, float maxRadius);
	virtual ~MorceauParcoursVirage();

	virtual void modeliser();
protected:
	float maxRadius;
};

