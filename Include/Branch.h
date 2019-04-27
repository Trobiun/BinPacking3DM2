#ifndef BRANCH_H
#define BRANCH_H

#include "Object3D.h"

class Branch : public Object3D {
protected:
public:
	Branch(float height, float width, Pos3D pos, float angle);
	virtual ~Branch();

private:
	void create();
};

#endif /* BRANCH_H */

#pragma once
