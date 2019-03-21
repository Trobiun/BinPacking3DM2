#pragma once
#include "MorceauParcours.h"
class MorceauParcoursLigne :
	public MorceauParcours
{
public:
	MorceauParcoursLigne(Pos3D origin, float height, float width);
	virtual ~MorceauParcoursLigne();
	virtual void modeliser();

protected:
	float width;
};

