#include "engine/window.h"
#include <SDL.h>
#include "engine/backend/backend.h"
#include "engine/backend/cpu/cpu.h"
#include "engine/backend/cpu/transformations.h"
#include <iostream>

using namespace std;


Window::Window(int width, int height) {
    this -> width = width;
    this -> height = height;

    
}



void Window::closeWindow() {
    SDL_DestroyWindow(screen);
    SDL_Quit();
}