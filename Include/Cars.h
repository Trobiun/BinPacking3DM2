#ifndef CARS_H
#define CARS_H

#include "Pos3D.h"
#include "Dir3D.h"
#include "Object3D.h"

class Cars : public Object3D {
public:
    Cars();
    Cars(float height, float width, float length, Pos3D pos, float angle);
    virtual ~Cars();
    void create();
    void accelerate(int accelerating, double timeSinceLastFrame);
    void move(double timeSinceLastFrame);
    void moveTest(double timeSinceLastFrame);
    void calculDirection();
    void moveG();
    void moveD();
    float getVitesse();
    float getDeplaceX();
    float getDeplaceZ();

private:
    float accel;
    float rotation;
    float vitesse;

    float deplacex;
    float deplacez;

    /*float height;
    float width;
    float length;
    Pos3D position;*/
};

#endif 

