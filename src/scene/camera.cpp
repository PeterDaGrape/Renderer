#include "camera.h" 
#include <math.h>
#include <iostream>

using namespace std;


Camera::Camera(Vec3 location, float fov, Vec3 rotation, int width, int height, float zNear, float zFar) {
    this -> location = location;
    this -> fov = fov;
    this -> rotation = rotation;
    this -> mat = gsl_matrix_alloc(4, 4);
    calculateProjectionMat(width, height, zNear, zFar);
}

gsl_matrix* Camera::calculateProjectionMat(int width, int height, float zNear, float zFar) {

    
    float fov_rads = this -> fov * (M_PI / 180.0f);


    float coeffs[4][4] {
        {(float)height/ (float)width / tan(fov_rads/2), 0, 0, 0},
        {0, 1/tan(fov_rads/2), 0, 0},
        {0, 0, zFar/(zFar - zNear), 1},
        {0, 0, (-zFar * zNear) / (zFar - zNear), 0}
    };

    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << coeffs[i][j] << endl;
            gsl_matrix_set(mat, j, i, coeffs[i][j]);
        }
    }
    cout << "Calculated proj matrix!" << endl;
    return mat;
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