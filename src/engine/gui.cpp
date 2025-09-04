#include "engine/gui.h"
#include <iostream>

#include "scene/camera.h"

using namespace std;

GUI_Manager::GUI_Manager(SDL_Window* window, SDL_Renderer* renderer) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void GUI_Manager::processEvents(SDL_Event* event) {
    ImGui_ImplSDL2_ProcessEvent(event);
}

bool GUI_Manager::blockingEvents() {
    ImGuiIO& io = ImGui::GetIO();
    return io.WantCaptureMouse;
}

void GUI_Manager::drawGUI(SDL_Renderer* renderer, ControlModelInterface* interface) {

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();


    ImGui::Begin("3D Rendering options");                          // Create a window called "Hello, world!" and append into it.



    float newFOV = interface -> getFOV();
    ImGui::SliderFloat("FOV", &newFOV, 30.0f, 180.0f);

    
    interface -> setFOV(newFOV);



    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
    ImGui::Render();

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);


}

GUI_Manager::~GUI_Manager() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext(); 
}