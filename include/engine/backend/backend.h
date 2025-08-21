#pragma once
#include <SDL.h>
#include "engine/window.h"
#include "scene/object.h"
#include "scene/camera.h"

class BackEnd {

protected:

    Window* window; 



public:
    virtual ~BackEnd() = default;
    virtual void drawFrame(Scene* scene) = 0;
    virtual void drawObject(Camera* camera, Object object) = 0;
    //virtual SDL_Renderer* init(SDL_Window* screen) = 0;

};