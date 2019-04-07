#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Object3D.h"

Object3D::Object3D() {
}

Object3D::Object3D(float height, float width, float length, Pos3D position, double angle) {
    this->height = height;
    this->width = width;
    this->length = length;
    this->position = position;
    this->angle = angle;
}

Object3D::~Object3D() {
}

void Object3D::model() {
    glPushMatrix();
    init();
    create();
    glPopMatrix();
}

Pos3D Object3D::getPosition() {
    return position;
}

void Object3D::init() {
    translate();
    rotate();
    scale();
}

void Object3D::translate() {
    glTranslatef(position.x + length / 2, position.y + height / 2, position.z + width / 2);
}

void Object3D::rotate() {
    glRotatef(angle, 0.0, 1.0, 0.0);
}

void Object3D::scale() {
    glScalef(length, height, width);
}