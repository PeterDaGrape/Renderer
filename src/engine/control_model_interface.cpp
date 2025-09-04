#include "engine/control_model_interface.h"
#include <iostream>
using namespace std;

ControlModelInterface::ControlModelInterface(Camera* camera) {

    this -> camera = camera;

}

void ControlModelInterface::setFOV(float fov) {

    if (!camera) {
        cerr << "Camera pointer is invalid" << endl;
    }



    if (fov != getFOV()) {
        camera -> setFOV(fov, *width, *height);
    }

    camera -> setFOV(fov, *width, *height);
}