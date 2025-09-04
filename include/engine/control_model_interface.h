#pragma once

#include "scene/camera.h"


class ControlModelInterface {

private:


Camera* camera;


public:

    int* width;
    int* height;
    
    ControlModelInterface(Camera* camera);

    void setFOV(float fov);
    float getFOV() {return camera -> getFOV();}

};