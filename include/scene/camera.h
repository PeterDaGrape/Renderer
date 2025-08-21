#pragma once

#include <vector>
#include "globals.h"


class Camera {
    private:
    Vec3 location;
    float fov;

    public:
    Camera(Vec3 location, float fov);
    void move(Vec3 vector) {location = vector + location;}
    void setLocation(Vec3 location);
    Vec3 getLocation();

    void setFOV(float fov);
    float getFOV();


};