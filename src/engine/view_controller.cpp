#include "engine/view_controller.h"
#include "backend/cpu/cpu_wireframe.h"
#include <iostream>

using namespace std;

ViewController::ViewController(BackEnd* backend, ControlModelInterface* interface, int width, int height) {
    
    this -> width = width;
    this -> height = height;

    this -> backend = backend;

    this -> interface = interface;

    interface -> width = &this->width;
    interface -> height = &this->height;
    
    this -> gui = nullptr;

    SDL_Init(SDL_INIT_VIDEO);


    this -> window = SDL_CreateWindow(
        "3D Renderer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, 
        height, 
        //SDL_WINDOW_ALLOW_HIGHDPI
        0
    );
    
    this -> renderer = SDL_CreateRenderer(window, -1, 0);

    if (!this->renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
    }

    int renderWidth;
    int renderHeight;
    if (SDL_GetRendererOutputSize(renderer, &renderWidth, &renderHeight) != 0) {
        cerr << "Could not get output size" << endl;
    } else {
        cout << "Width: " << renderWidth << " Height: " << renderHeight << endl;
    }

    setWidth(renderWidth);
    setHeight(renderHeight);

}

void ViewController::draw(Scene* scene) {

    backend -> drawFrame(width, height, scene, renderer);
    
    gui -> drawGUI(renderer, interface);

}

ViewController::~ViewController() {
    SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void ViewController::processEvent(SDL_Event* e) {

    if (gui) {
        gui->processEvents(e);
    }
}