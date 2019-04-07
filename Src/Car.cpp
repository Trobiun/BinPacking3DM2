#include <cmath>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Car.h"
#include "RT3D.h"
#include "TR3D.h"

#define MAX_ACCELERATION 150.0
#define MAX_SPEED 80.0
#define ACCELERATION_FACTOR 30.0
#define ANGLE_FACTOR 30.0
#define LERP_FACTOR 20.0
#define MAX_STEER 5.0f
#define BACKWARD_FRICTION_FACTOR 0.1f
#define LATERAL_FRICTION_FACTOR 0.1f

Car::Car() {
}

Car::Car(float height, float width, float length, Pos3D pos, float angle)
: Object3D(height, width, length, pos, angle) {
    acceleration = Dir3D(0.0, 0.0, 0.0);
    vitesse = Dir3D(0.0, 0.0, 0.0);
    vitesseLaterale = Dir3D(0, 0, 0);
    direction = Dir3D(1.0, 0.0, 0.0);
    backwardFriction = Dir3D(0, 0, 0);
    timeAccel = 0;
    this->angle = 0.0;
    this->angle2 = 0.0;
    this->steerInput = 0.0;
    virage = false;
}

Car::~Car() {
}

void Car::create() {
    glutSolidCube(1.0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3d(0, 0, 0);
    glVertex3d(acceleration.x, acceleration.y, acceleration.z);
    glVertex3d(0, 0, 0);
    glVertex3d(vitesse.x, vitesse.y, vitesse.z);
    glVertex3d(0, 0, 0);
    glVertex3d(direction.x, direction.y, direction.z);
    glEnd();
}

Pos3D Car::getPosition() {
    return position;
}

double Car::accelerationFunction(long accelTime) {
    if (accelerating && accelTime > 0) {
        return (MAX_ACCELERATION / (accelTime));
    }
    if (braking && accelTime > 0) {
        return -(MAX_ACCELERATION / (accelTime));
    }
    return accelerationInput * (MAX_ACCELERATION / (1));
    //    if (accelTime == 0) {
    //        return 0;
    //    }
}

void Car::accelerate(int accelInput, double timeSinceLastFrame) {
    this->accelerationInput = accelInput;
    if (accelerationInput > 0) {
        accelerating = true;
        braking = false;
    }
    if (!accelerating && accelerationInput < 0) {
        printf("acc\n");
        accelerating = true;
        braking = false;
    }
    if (accelerating && accelerationInput < 0) {
        accelerating = false;
        braking = true;
    }
    if (accelerationInput == 0 && !accelerating) {
        accelerating = false;
        braking = false;
    }
    //    if (accelerating) {
    //        if (timeAccel < MAX_ACCELERATION) {
    //            timeAccel += 1;
    //        }
    //    }
    //    if (braking) {
    //        if (timeAccel > 0) {
    //            timeAccel -= 1;
    //        }
    //    }
}

void Car::move(double timeSinceLastFrame) {
    //    accelerate(true, accelerationInput);
    //    if (accelerationInput) {
    acceleration.x = direction.x * accelerationInput * ACCELERATION_FACTOR;
    acceleration.y = direction.y * accelerationInput * ACCELERATION_FACTOR;
    acceleration.z = direction.z * accelerationInput * ACCELERATION_FACTOR;
    //    }
    //    else {
    //        acceleration.x = -vitesse.x; // / ACCELERATION_FACTOR;
    //        acceleration.y = -vitesse.y; // / ACCELERATION_FACTOR;
    //        acceleration.z = -vitesse.z; // / ACCELERATION_FACTOR;
    //    }

    backwardFriction.x = -vitesse.x * BACKWARD_FRICTION_FACTOR;
    backwardFriction.y = -vitesse.y * BACKWARD_FRICTION_FACTOR;
    backwardFriction.z = -vitesse.z * BACKWARD_FRICTION_FACTOR;

    //    RT3D rotLaterale = RT3D(90, 0.0, 1.0, 0.0);
    //    rotLaterale.transformation(&vitesse, &vitesseLaterale);
    Dir3D lateralFriction = Dir3D();
    lateralFriction.x = -vitesseLaterale.x * LATERAL_FRICTION_FACTOR;
    lateralFriction.y = -vitesseLaterale.y * LATERAL_FRICTION_FACTOR;
    lateralFriction.z = -vitesseLaterale.z * LATERAL_FRICTION_FACTOR;
    backwardFriction.x = -vitesse.x * BACKWARD_FRICTION_FACTOR;
    backwardFriction.y = -vitesse.y * BACKWARD_FRICTION_FACTOR;
    backwardFriction.z = -vitesse.z * BACKWARD_FRICTION_FACTOR;
    vitesse.x += (backwardFriction.x + lateralFriction.x) * 1.0 / 60.0;
    vitesse.y += (backwardFriction.y + lateralFriction.y) * 1.0 / 60.0;
    vitesse.z += (backwardFriction.z + lateralFriction.z) * 1.0 / 60.0;

    double steer_angle = steering(steerInput);
    printf("%lf\n", steer_angle);
    if (vitesse.norme() > 0) {
        steer_angle = steerInput * ANGLE_FACTOR; // * (vitesse.norme() / MAX_SPEED);
    }
    else {
        steer_angle = steerInput * ANGLE_FACTOR; // * (1 / 2);
    }
    steerInput = 0.00;
    Dir3D dirTemp;
    RT3D rotation = RT3D(steer_angle, 0.0, 1.0, 0.0);
    rotation.transformation(&direction, &direction);

    //    std::chrono::time_point<std::chrono::system_clock> thisFrame = std::chrono::system_clock::now();
    //    std::chrono::duration<double, std::centi> elapsedTime = std::chrono::duration_cast<std::chrono::seconds> (thisFrame - lastFrame).count();
    double currentSpeed = vitesse.norme();
    if (currentSpeed < MAX_SPEED) {
        vitesse.x += acceleration.x * timeSinceLastFrame;
        vitesse.y += acceleration.y * timeSinceLastFrame;
        vitesse.z += acceleration.z * timeSinceLastFrame;
    }
    position.x += vitesse.x * timeSinceLastFrame;
    position.y += vitesse.y * timeSinceLastFrame;
    position.z += vitesse.z * timeSinceLastFrame;
}

void Car::move2() {
    float steerAngle = steering(steerInput);
    printf("%f\n", steerAngle);
    float sn = std::sin(steerAngle);
    float cs = std::cos(steerAngle);
    //    double steer_angle = steerInput * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED);
    //    Dir3D temp;
    RT3D rotation = RT3D(steerAngle, 0.0, 1.0, 0.0);
    rotation.transformation(&direction, &direction);
    //    vitesse = temp;
    double currentSpeed = vitesse.norme();
    if (currentSpeed < MAX_SPEED) {
        velocity.y = cs * vitesse.y + sn * vitesse.x;
        velocity.x = cs * vitesse.x - sn * vitesse.y;
        vitesse.x = acceleration.x * 1.0 / 60.0;
        vitesse.y = acceleration.y * 1.0 / 60.0;
        vitesse.z = acceleration.z * 1.0 / 60.0;
    }
    position.x += vitesse.x * 1.0 / 60.0;
    position.y += vitesse.y * 1.0 / 60.0;
    position.z += vitesse.z * 1.0 / 60.0;
    acceleration.x = direction.x * accelerationInput * ACCELERATION_FACTOR;
    acceleration.y = direction.y * accelerationInput * ACCELERATION_FACTOR;
    acceleration.z = direction.z * accelerationInput * ACCELERATION_FACTOR;
}

void Car::move3() {
    //    accelerate(accelerationInput != 0, 0);
    double accel = accelerationFunction(timeAccel);
    //    printf("%lf\t", accel);
    acceleration.x = direction.x * accel;
    acceleration.y = direction.y * accel;
    acceleration.z = direction.z * accel;
    //    printf("%f\n", acceleration.norme());

    double steer_angle = steerInput * ANGLE_FACTOR; // * (vitesse.norme() / MAX_SPEED);
    Dir3D dirTemp;
    RT3D rotation = RT3D(steer_angle, 0.0, 1.0, 0.0);
    rotation.transformation(&direction, &direction);

    double currentSpeed = vitesse.norme();
    if (currentSpeed < MAX_SPEED) {
        vitesse.x += acceleration.x * 1.0 / 60.0;
        vitesse.y += acceleration.y * 1.0 / 60.0;
        vitesse.z += acceleration.z * 1.0 / 60.0;
    }
    position.x += vitesse.x * 1.0 / 60.0;
    position.y += vitesse.y * 1.0 / 60.0;
    position.z += vitesse.z * 1.0 / 60.0;
}

void Car::rotateAngle(int diff) {

}

void Car::setAngleInput(double input) {
    steerInput = input;
}

void Car::moveG() {
    steerInput = 1;
    //    printf("%lf\n", angle2);
    //    if (angle2 < 180) {
    //
    //        angle2 += 1 * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED);
    //        RT3D rotation = new RT3D(1 * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED), 0.0, 1.0, 0.0);
    //        rotation.transformation(&direction, &direction);
    //    }
    //    Dir3D accel;
    //    RT3D rotation = new RT3D(90, 0.0, 1.0, 0.0);
    //    rotation.transformation(&direction, &accel);
    //    accel.normalisation();
    //    this->acceleration = accel;
}

void Car::moveD() {
    steerInput = -1;
    //    Dir3D accel;
    //    printf("%lf\n", angle2);
    //    if (angle2 > -180) {
    //
    //        angle2 -= 1 * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED);
    //        RT3D rotation = new RT3D(-1 * ANGLE_FACTOR * (vitesse.norme() / MAX_SPEED), 0.0, 1.0, 0.0);
    //        rotation.transformation(&direction, &direction);
    //    }
    //    }
    //    acceleration = direction;
    //    direction = accel;
    //    Dir3D accel;
    //    RT3D rotation = new RT3D(-90, 0.0, 1.0, 0.0);
    //    rotation.transformation(&direction, &accel);
    //    accel.normalisation();
    //    this->acceleration = accel;
}

void Car::setAccelerationInput(double input) {
    this->accelerationInput = input;
}

float Car::steering(float inputAngle) {
    float smoothedAngle = 0;
    float dt = 1;
    float CHANGE_MODIFIER = 12.0f;
    float MIN_LIMIT = -15.0f;
    float MAX_LIMIT = 15.0f;
    if (std::abs(inputAngle) > 0.001) {
        float test = (float) (steerAngle + inputAngle * dt * CHANGE_MODIFIER);
        if (test < MIN_LIMIT) {
            smoothedAngle = MIN_LIMIT;
        }
        else {
            if (MAX_LIMIT < test) {
                smoothedAngle = MAX_LIMIT;
            }
            else {
                smoothedAngle = test;
            }
        }
        //        smoothedAngle = clamp((float) (steerAngle + inputAngle * dt * CHANGE_MODIFIER), -0.6F, 0.6F);
    }
    else {
        //  No steer input - move toward centre (0)
        if (steerAngle > 0) {
            smoothedAngle = std::fmax(steerAngle - dt * CHANGE_MODIFIER, 0.0f);
        }
        else if (steerAngle < 0) {
            smoothedAngle = std::fmin(steerAngle + dt * CHANGE_MODIFIER, 0.0f);
        }
    }
    return smoothedAngle;
}