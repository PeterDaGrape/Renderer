#pragma once
#include "engine/backend/backend.h"

class CPUWireframe: public BackEnd {

private:


public:

    //SDL_Renderer* init(SDL_Window* screen);
    CPUWireframe(int width, int height);
    void drawFrame(Scene* scene);
    void drawObject(Camera* camera, Object object);
};