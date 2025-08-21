#include "camera.h"


Camera::Camera(Vec3 location, float fov) {
    this -> location = location;
    this -> fov = fov;
}

void Camera::setLocation(Vec3 location) {
    this -> location = location;
}

Vec3 Camera::getLocation() {
    return this -> location;
}

void Camera::setFOV(float fov) {
    this -> fov = fov;
}

float Camera::getFOV() {
    return fov;
}