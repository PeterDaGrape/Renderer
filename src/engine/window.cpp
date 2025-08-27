#include "engine/window.h"
#include <SDL.h>
#include "engine/backend/backend.h"
#include "engine/backend/cpu/cpu_wireframe.h"
#include "engine/backend/cpu/transformations.h"
#include <iostream>

using namespace std;


Window::Window(int width, int height) {
    this -> width = width;
    this -> height = height;
    SDL_Init(SDL_INIT_VIDEO);
}



void Window::closeWindow() {
    SDL_DestroyWindow(screen);
    SDL_Quit();
}