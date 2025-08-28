#include "camera.h" 
#include <math.h>
#include <iostream>
#include "engine/backend/cpu/transformations.h"

using namespace std;





Camera::Camera(Vec3 location, float fov, Vec3 rotation, int width, int height, float zNear, float zFar) {
    this -> location = location;
    this -> fov = fov;
    this -> rotation = rotation;
    this -> projMat = gsl_matrix_alloc(4, 4);
    this -> zNear = zNear;
    this -> zFar = zFar;

    calculateProjectionMat(width, height);
}

gsl_matrix* Camera::calculateProjectionMat(int width, int height) {

    
    float fov_rads = this -> fov * (M_PI / 180.0f);


    float coeffs[4][4] {
        {(float)height/ (float)width / tan(fov_rads/2), 0, 0, 0},
        {0, 1/tan(fov_rads/2), 0, 0},
        {0, 0, zFar/(zFar - zNear), 1},
        {0, 0, (-zFar * zNear) / (zFar - zNear), 0}
    };

    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gsl_matrix_set(projMat, j, i, coeffs[i][j]);
        }
    }
    return projMat;
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