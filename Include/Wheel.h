#ifndef WHEEL_H
#define WHEEL_H

#include "Object3D.h"

class Wheel : public Object3D {
public:
    Wheel(Pos3D pos, float angle);
    virtual ~Wheel();
private:
    void create();
};

#endif /* WHEEL_H */

