#pragma once
#include "engine/backend/backend.h"

class CPUWireframe: public BackEnd {

private:


public:

    //SDL_Renderer* init(SDL_Window* screen);
    CPUWireframe();
    void drawFrame(int width, int height, Scene* scene, SDL_Renderer* renderer);
    void drawObject(int width, int height, Camera* camera, const Object& object, SDL_Renderer* renderer);
};