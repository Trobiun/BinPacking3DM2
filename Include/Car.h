#ifndef VOITURE_H
#define VOITURE_H

#include "Pos3D.h"
#include "Dir3D.h"
#include "Object3D.h"

class Car : public Object3D {
public:
    Car();
    Car(float height, float width, float length, Pos3D pos, float angle);
    Car(const Car& orig);
    virtual ~Car();
    void create();
private:
    float height;
    float width;
    float length;
    Pos3D position;
    Dir3D direction;
};

#endif /* VOITURE_H */

