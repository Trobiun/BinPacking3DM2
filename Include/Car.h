#ifndef VOITURE_H
#define VOITURE_H

#include "Pos3D.h"
#include "Dir3D.h"
#include "Object3D.h"

class Car : public Object3D {
public:
    Car();
    Car(float height, float width, float length, Pos3D pos, float angle);
    virtual ~Car();
    void create();
    Pos3D getPosition();
    void accelerate(int acceleInput, double timeSinceLastFrame);
    void move(double timeSinceLastFrame);
    void move2();
    void move3();
    void moveG();
    void moveD();
    float steering(float inputAngle, double timeSinceLastFrame);
    void setVirage(bool virage);
    void setAccelerationInput(double input);
    void rotateAngle(int diff);
    void setAngleInput(double input);
    double accelerationFunction(long accelTime);
    double getDeplaceX();
    double getDeplaceZ();
private:
    Dir3D acceleration;
    Dir3D vitesse;
    Dir3D vitesseLaterale;
    Dir3D velocity;
    Dir3D direction;
    Dir3D backwardFriction;
    double angle2;
    double steerInput;
    double steerAngle;
    long timeAccel;
    bool virage;
    bool accelerating;
    bool braking;
    double angleInput = 0.0;
    double accelerationInput = 0.0;
    /*float height;
    float width;
    float length;
    Pos3D position;*/
};

#endif /* VOITURE_H */