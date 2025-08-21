#include <iostream>

#include "scene.h"
#include "scene/camera.h"
#include "engine/backend/cpu/cpu.h"
#include "globals.h"
#include <filesystem>

#include <SDL.h>

using namespace std;


int main() {



    Scene* scene = Scene::getInstance();
    if (scene -> loadMeshes("../meshes/cube.obj") != 0) {
        cerr << "Something broke while loading the file" << endl;
        return -1;
    }


    Camera camera(Vec3{0, 0, -8}, FOV);

    scene->setCamera(&camera);

    CPU backend(WIDTH, HEIGHT);

    //temp draw 

    Uint32 prev = SDL_GetTicks();

    bool quit = false;
    SDL_Event e;
    while (!quit) {


        Uint32 now = SDL_GetTicks();
        std::cout << "Frame rate " << (float)1000 / (float)(now - prev) << std::endl;

        prev = now;


        backend.drawFrame(scene);

 

        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT: {
                    quit = true;
                } break;
            }
        }
    }


    return 0;
}