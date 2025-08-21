#pragma once
#include <SDL.h>

#include "scene/scene.h"


// TODO make this a singleton setup, and setup methods for opening and closing the window
// Eventually I have to figure out how to do acceleration, but for now software will do
class Window {

    private:
    SDL_Window* screen;

    SDL_Renderer* renderer;


    int width;
    int height;

    public:

    int getWidth() {return width;}
    int getHeight() {return height;}

    Window(int width, int height);

    SDL_Renderer* getRenderer() {return renderer;}

    void setRenderer(SDL_Renderer* renderer) {this -> renderer = renderer;}
    void setWindow(SDL_Window* screen) {this -> screen = screen;}

    SDL_Window* getScreen() {return screen;}


    
    void closeWindow();

};