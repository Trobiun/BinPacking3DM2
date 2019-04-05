#ifndef VOITURE_H
#define VOITURE_H

#include "Pos3D.h"
#include "Dir3D.h"
#include "Object3D.h"
#include "Vecteur.h"

class Car : public Object3D {
public:
    Car();
    Car(float height, float width, float length, Pos3D pos, float angle);
    Car(const Car& orig);
    virtual ~Car();
    Pos3D getPosition();
    void create();
    void accelerate(bool accelerating);
    void move1();
    void move2();
    void move3();
    double accelerationFunction(long accelTime);
    //    void moveBackward();
    void moveLeft();
    void moveRight();
    //    void setVirage(bool virage);
    void setAccelerationInput(double input);
    void rotateAngle(int diff);
    void setAngleInput(double input);
    float steering(float inputAngle);
private:
    Dir3D acceleration;
    Dir3D vitesse;
    Dir3D velocity;
    Dir3D vitesseLaterale;
    Dir3D direction;
    double angle2;
    long timeAccel;
    bool virage;
    bool accelerating;
    bool braking;
    double steerInput = 0.0;
    double accelerationInput = 0.0;
    float steerAngle = 0.0;
    /*float height;
    float width;
    float length;
    Pos3D position;*/
};

#endif /* VOITURE_H */

