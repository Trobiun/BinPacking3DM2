#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Pos3D.h"

class Object3D {
protected:
    float height;
    float width;
    float length;
    Pos3D position;
    double angle;
public:
    Object3D();
    Object3D(float height, float width, float length, Pos3D position, double angle);
    Object3D(const Object3D& orig);
    virtual ~Object3D();
    void model();
protected:
    virtual void create() = 0;
private:
    void init();
    void translate();
    void rotate();
    void scale();
};

#endif /* OBJECT3D_H */

