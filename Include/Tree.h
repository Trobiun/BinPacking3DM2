#ifndef TREE_H
#define TREE_H

#include "Branch.h"
#include "Object3D.h"
#include <list>

class Tree : public Object3D {
protected:
	float radius;
	std::list<Branch*> branch;
public:
	Tree(float height, float width, Pos3D pos, float angle);
	virtual ~Tree();

private:
	void create(); 
	void makeTree(float height, float base);
	
};

#endif /* TREE_H */

