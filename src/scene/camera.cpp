#include "camera.h" 
#include <math.h>
#include <iostream>
#include "engine/backend/cpu/transformations.h"

using namespace std;





Camera::Camera(Vec3 location, float fov, Vec3 rotation, int width, int height, float zNear, float zFar) {
    this -> location = location;
    this -> fov = fov;
    this -> rotation = rotation;
    this -> zNear = zNear;
    this -> zFar = zFar;

    calculate4x4ProjMat(width, height);

}

void Camera::calculate4x4ProjMat(int width, int height) {
  
     float fov_rads = this -> fov * (M_PI / 180.0f);
 
    float coeffs[4][4] {
        {(float)height/ (float)width / tan(fov_rads/2), 0, 0, 0},
        {0, 1/tan(fov_rads/2), 0, 0},
        {0, 0, zFar/(zFar - zNear), 1},
        {0, 0, (-zFar * zNear) / (zFar - zNear), 0}
    };

    memcpy(projectionMat, coeffs, sizeof(projectionMat));
    
} 


void Camera::move(Vec3 vector) {

    location = vector + location;
}

void Camera::setLocation(Vec3 location) {
    this -> location = location;
}

Vec3 Camera::getLocation() {
    return this -> location;
}

float Camera::getFOV() {
    return fov;
}