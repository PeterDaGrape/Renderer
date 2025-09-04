#include <iostream>

#include "scene.h"
#include "scene/camera.h"
#include "engine/view_controller.h"
#include "engine/control_model_interface.h"
#include "globals.h"
#include <filesystem>
#include "engine/backend/cpu/cpu_wireframe.h"

#include <SDL.h>

using namespace std;



int main(int argc, char *argv[]) {

    Scene* scene = Scene::getInstance();
    if (scene -> loadMeshes(MESH_PATH) != 0) {
        cerr << "Something failed while loading the file" << endl;
        return -1;
    }

    //Setup camera with default options
    Camera camera(Vec3{0, 0, -8}, FOV, Vec3{0, 0, 0}, WIDTH, HEIGHT, 0.1, 100);
    scene->setCamera(&camera);


    
    
    auto backend = CPUWireframe();
    ControlModelInterface interface (&camera);
    ViewController controller (&backend, &interface, WIDTH, HEIGHT);
    
    GUI_Manager gui (controller.getWindow(), controller.getRenderer());
    controller.setGUI(&gui);
    

    Uint32 prev = SDL_GetTicks();

    bool quit = false;
    SDL_Event e;

    Point mouseStart {-1, -1};


    // count number of vertices
    int count = 0;
    for (Object object : scene->getObjects()) {
        count += object.getVertices().size();
    }

    cout << count << endl;

    while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
            controller.processEvent(&e);
            
            if (controller.getGUI()->blockingEvents()) {
                break;
            }

            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if (e.button.state == SDL_PRESSED) {
                            mouseStart = {e.button.x, e.button.y};
                        } else if (e.button.state == SDL_RELEASED) {
                            mouseStart = {-1, -1};
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    
                    if (mouseStart.x == -1 || mouseStart.y == -1) { 
                        break;
                    }

                    camera.lookAbout(e.motion.x - mouseStart.x, e.motion.y - mouseStart.y);
                    mouseStart.x = e.motion.x;
                    mouseStart.y = e.motion.y;
                    break;
            }
        }

        Uint32 now = SDL_GetTicks();
        //cout << "Frame rate " << (float)1000 / (float)(now - prev) << std::endl;
        Uint32 dt = now - prev;

        prev = now;

        controller.draw(scene);

        // Movement stuff
        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        float speed = 0.01f * dt; // units per millisecond, scaled by frame delta
        Vec3 moveVector = {0, 0, 0};

        if (keystates[SDL_SCANCODE_UP])    moveVector.z += speed;
        if (keystates[SDL_SCANCODE_DOWN])  moveVector.z -= speed;
        if (keystates[SDL_SCANCODE_RIGHT]) moveVector.x += speed;
        if (keystates[SDL_SCANCODE_LEFT])  moveVector.x -= speed;
        if (keystates[SDL_SCANCODE_SPACE]) moveVector.y += speed;
        if (keystates[SDL_SCANCODE_LSHIFT]) moveVector.y -= speed;

        camera.move(moveVector);


        SDL_RenderPresent(controller.getRenderer());

    }

    return 0;
}