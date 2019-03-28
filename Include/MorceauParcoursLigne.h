#pragma once
#include "MorceauParcours.h"

class MorceauParcoursLigne :
public MorceauParcours {
public:
    MorceauParcoursLigne(Pos3D origin, float width, float length, Direction dir);
    virtual ~MorceauParcoursLigne();
    virtual void modeliser();
	void creationMorceauVertical(float width, float length, float decalage);
	void creationMorceauHorizontal(float width, float length, float decalage);

protected:
    float length;
};

