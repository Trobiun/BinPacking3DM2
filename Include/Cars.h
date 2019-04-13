#ifndef CARS_H
#define CARS_H

#include "Pos3D.h"
#include "Dir3D.h"
#include "Object3D.h"
#include "Wheel.h"

class Cars : public Object3D {
public:
    Cars();
    Cars(float height, float width, float length, Pos3D pos, float angle);
    virtual ~Cars();
    void accelerate(int accelerating, double timeSinceLastFrame);
    void move(double timeSinceLastFrame);
    void moveTest(double timeSinceLastFrame);
    void calculDirection();
    void moveG(double timeSinceLastFrame);
    void moveD(double timeSinceLastFrame);
    double getVitesse();
    double getDeplaceX();
    double getDeplaceZ();

private:
    double accel;
    double rotation;
    double vitesse;

    double deplacex;
    double deplacez;

    Wheel* wheels[4];

    /*float height;
    float width;
    float length;
    Pos3D position;*/

    void create() override;
    void beforeScale() override;

};

#endif 

