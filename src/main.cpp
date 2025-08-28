#include <iostream>

#include "scene.h"
#include "scene/camera.h"
#include "engine/backend/cpu/cpu_wireframe.h"
#include "globals.h"
#include <filesystem>

#include <SDL.h>

using namespace std;


void HandleMotion(SDL_MouseMotionEvent& E) {
  std::cout << "Mouse moved to ("
    << E.x << ", " << E.y << ")\n";
}


int main(int argc, char *argv[]) {


    Scene* scene = Scene::getInstance();
    if (scene -> loadMeshes(MESH_PATH) != 0) {
        cerr << "Something failed while loading the file" << endl;
        return -1;
    }

    //Setup camera with default options
    Camera camera(Vec3{0, 0, -8}, FOV, Vec3{0, 0, 0}, WIDTH, HEIGHT, 0.1, 100);
    scene->setCamera(&camera);


    CPUWireframe backend(WIDTH, HEIGHT);


    Uint32 prev = SDL_GetTicks();

    bool quit = false;
    SDL_Event e;

    Point mouseStart {-1, -1};

    while (!quit) {


        Uint32 now = SDL_GetTicks();
        //std::cout << "Frame rate " << (float)1000 / (float)(now - prev) << std::endl;
        Uint32 dt = now - prev;

        prev = now;

        backend.drawFrame(scene);


        // Movement stuff
        const Uint8* keystates = SDL_GetKeyboardState(NULL);

        float speed = 0.01f * dt; // units per millisecond, scaled by frame delta
        Vec3 moveVector = {0, 0, 0};


        if (keystates[SDL_SCANCODE_UP])    moveVector.z += speed;
        if (keystates[SDL_SCANCODE_DOWN])  moveVector.z -= speed;
        if (keystates[SDL_SCANCODE_LEFT])  moveVector.x += speed;
        if (keystates[SDL_SCANCODE_RIGHT]) moveVector.x -= speed;
        if (keystates[SDL_SCANCODE_SPACE]) moveVector.y += speed;
        if (keystates[SDL_SCANCODE_LSHIFT]) moveVector.y -= speed;


        camera.move(moveVector);

        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        if (e.button.state == SDL_PRESSED) {
                            cout << "clicked" << endl;
                            mouseStart = {e.button.x, e.button.y};
                        } else if (e.button.state == SDL_RELEASED) {
                            cout << "released" << endl;
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
    }


    return 0;
}