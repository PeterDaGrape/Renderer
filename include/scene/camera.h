#pragma once

#include <vector>
#include "globals.h"

class Camera {
    private:
    Vec3 location;
    float fov;

    float zNear;
    float zFar;

    float projectionMat[4][4];


    // is a vector describing the direction the camera points
    // .x: = clockwise around x axis
    // .y  = clockwise around y axis
    // .z  = clockwise around z axis
    Vec3 rotation;

    public:
    Camera(Vec3 location, float fov, Vec3 rotation, int width, int height, float zNear, float zFar);


    float (&get4x4ProjMat())[4][4] { return projectionMat; }



    void calculate4x4ProjMat(int width, int height); 


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