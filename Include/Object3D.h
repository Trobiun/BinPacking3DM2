#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Pos3D.h"

class Object3D {
protected:
    double angle;
public:
    float height;
    float width;
    float length;
    Pos3D position;
public:
    Object3D();
    Object3D(float height, float width, float length, Pos3D position, double angle);
    virtual ~Object3D();
    void model();
    Pos3D getPosition();
protected:
    virtual void create() = 0;
    virtual void beforeTranslate();
    virtual void beforeRotate();
    virtual void beforeScale();
    virtual void afterScale();
private:
    void init();
    void translate();
    void rotate();
    void scale();
};

#endif /* OBJECT3D_H */

