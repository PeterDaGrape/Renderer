#pragma once

#include <SDL.h>
#include "globals.h"
#include "engine/control_model_interface.h"

#include "sdl2gui/imgui.h"
#include "sdl2gui/imgui_impl_sdl2.h"
#include "sdl2gui/imgui_impl_sdlrenderer2.h"

class GUI_Manager {

    private:

    public:

    GUI_Manager(SDL_Window* window, SDL_Renderer* renderer);
    ~GUI_Manager();

    void processEvents(SDL_Event* event);
    void drawGUI(SDL_Renderer* renderer, ControlModelInterface* interface);
    bool blockingEvents();

    

};