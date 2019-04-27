#ifndef TREE_H
#define TREE_H

#include "Object3D.h"

class Tree : public Object3D {
protected:
	float radius;
public:
	Tree(float height, float width, Pos3D pos, float angle);
	virtual ~Tree();

private:
	void create(); 
	void makeTree(float height, float base);
	
};

#endif /* TREE_H */

