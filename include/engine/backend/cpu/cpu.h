#pragma once
#include "engine/backend/backend.h"

class CPU: public BackEnd {

private:


public:

    //SDL_Renderer* init(SDL_Window* screen);
    CPU(int width, int height);
    void drawFrame(Scene* scene);
    void drawObject(Camera* camera, Object object);
};