#pragma once

#include <vector>
#include "globals.h"
#include <gsl/gsl_matrix.h>

class Camera {
    private:
    Vec3 location;
    float fov;

    gsl_matrix* mat;


    // is a vector describing the direction the camera points
    // .x: roll = rotation around z axis, clockwise
    // .y: pitch = rotation around x axis, clockwise
    // .z: yaw = rotation around y axis, clockwise
    Vec3 rotation;

    public:
    Camera(Vec3 location, float fov, Vec3 rotation, int width, int height, float zNear, float zFar);

    gsl_matrix* getProjectionMatrix() {return mat;}

    // uses values
    gsl_matrix* calculateProjectionMat(int width, int height, float zNear, float zFar);

    void move(Vec3 vector) {location = vector + location;}
    void setLocation(Vec3 location);
    Vec3 getLocation();


    void setRotation(Vec3 rotation) {this -> rotation = rotation;}
    Vec3 getRotation() {return rotation;}

    //returns the direction vector of the camera

    float getFOV();
};