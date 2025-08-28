#pragma once

#include <vector>
#include "globals.h"
#include <gsl/gsl_matrix.h>

class Camera {
    private:
    Vec3 location;
    float fov;

    float zNear;
    float zFar;

    gsl_matrix* projMat;


    // is a vector describing the direction the camera points
    // .x: = clockwise around x axis
    // .y  = clockwise around y axis
    // .z  = clockwise around z axis
    Vec3 rotation;

    public:
    Camera(Vec3 location, float fov, Vec3 rotation, int width, int height, float zNear, float zFar);

    gsl_matrix* getProjectionMatrix() {return projMat;}

    // uses values
    gsl_matrix* calculateProjectionMat(int width, int height);

    void move(Vec3 vector);
    void setLocation(Vec3 location);
    Vec3 getLocation();

    float getZNear() {return zNear;}
    float getZFar() {return zFar;}


    void setRotation(Vec3 rotation) {this -> rotation = rotation;}
    Vec3 getRotation() {return rotation;}

    //returns the direction vector of the camera

    float getFOV();
};