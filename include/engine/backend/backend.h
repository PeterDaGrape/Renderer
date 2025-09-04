#pragma once
#include <SDL.h>
#include "scene/object.h"
#include "scene/camera.h"
#include "scene.h"

class BackEnd {

protected:


public:
    virtual ~BackEnd() = default;
    virtual void drawFrame(int width, int height, Scene* scene, SDL_Renderer* renderer) = 0;
    virtual void drawObject(int width, int height, Camera* camera, const Object& object, SDL_Renderer* renderer) = 0;
    
};