#pragma once
#include <SDL.h>
#include "scene.h"
#include "scene/camera.h"
#include "engine/control_model_interface.h"
#include "engine/gui.h"
#include "engine/backend/backend.h"



class ViewController {

private:

    ControlModelInterface* interface;

    GUI_Manager* gui;
    BackEnd* backend;

    SDL_Window* window;
    SDL_Renderer* renderer;
    
    int height;
    int width;
    
    public:

    ViewController(BackEnd* backend, ControlModelInterface* interface, int width, int height);
    ~ViewController();

    void processEvent(SDL_Event* e);

    void draw(Scene* scene);


    int getWidth() {return width;}
    void setWidth(int width) {this -> width = width;}
    
    int getHeight() {return height;}
    void setHeight(int height) {this -> height = height;}

    SDL_Renderer* getRenderer() {return renderer; }
    SDL_Window* getWindow() {return window; }
    void setGUI(GUI_Manager* gui) {this -> gui = gui;}
    GUI_Manager* getGUI() {return gui; }

    

};