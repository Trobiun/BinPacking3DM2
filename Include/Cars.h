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
    double getVitesse();
    double getDeplaceX();
    double getDeplaceZ();

private:
    double accel;
    double rotation;
    double vitesse;

    double deplacex;
    double deplacez;

    /*float height;
    float width;
    float length;
    Pos3D position;*/
};

#endif 

