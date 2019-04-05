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
    Pos3D getPosition();
    void accelerate(bool accelerating);
    void move1();
    void move2();
    void move3();
    void moveLeft();
    void moveRight();
    float steering(float inputAngle);
    void setVirage(bool virage);
    void setAccelerationInput(double input);
    void rotateAngle(int diff);
    void setAngleInput(double input);
    double accelerationFunction(long accelTime);
private:
    Dir3D acceleration;
    Dir3D vitesse;
    Dir3D vitesseLaterale;
    Dir3D velocity;
    Dir3D direction;
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