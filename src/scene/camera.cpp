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

void Camera::setFOV(float fov, int width, int height) {
    this -> fov = fov;
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

Vec3 Camera::getDirectionVector() {

    Vec3 forward;
    forward.x = cos(rotation.x) * sin(rotation.y);
    forward.y = sin(rotation.x);
    forward.z = cos(rotation.x) * cos(rotation.y);



    return forward;

}

void Camera::lookAbout(int deltaX, int deltaY) {
    float sensitivity = 0.005f; // tweak for mouse speed
    rotation.y += deltaX * sensitivity; // yaw
    rotation.x -= deltaY * sensitivity; // pitch
    // Clamp pitch so camera doesn’t flip upside down
    if (rotation.x > M_PI/2) rotation.x = M_PI/2;
    if (rotation.x < -M_PI/2) rotation.x = -M_PI/2;
}


void Camera::move(Vec3 vector) {

    Vec3 forward = getDirectionVector();

    // Right vector (perpendicular to forward and world up)
    Vec3 right = forward.cross(Vec3{0, 1, 0});

    // Up vector (recomputed to ensure orthogonality)
    Vec3 up = right.cross(forward);

    Vec3 displacement =
        forward * vector.z +
        right   * vector.x +
        up      * vector.y;

    location = location + displacement;


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