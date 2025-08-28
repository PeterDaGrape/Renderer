#include <iostream>

#include "scene.h"
#include "scene/camera.h"
#include "engine/backend/cpu/cpu_wireframe.h"
#include "globals.h"
#include <filesystem>

#include <SDL.h>

using namespace std;


int main() {


    Scene* scene = Scene::getInstance();
    if (scene -> loadMeshes("../meshes/cube.obj") != 0) {
        cerr << "Something failed while loading the file" << endl;
        return -1;
    }

    //Look along the z+ axis
    Camera camera(Vec3{0, 0, -8}, FOV, Vec3{0.1, 0, -0.2}, WIDTH, HEIGHT, 0.1, 100);

    scene->setCamera(&camera);

    CPUWireframe backend(WIDTH, HEIGHT);

    //temp draw 

    Uint32 prev = SDL_GetTicks();

    bool quit = false;
    SDL_Event e;
    while (!quit) {


        Uint32 now = SDL_GetTicks();
        std::cout << "Frame rate " << (float)1000 / (float)(now - prev) << std::endl;
        Uint32 dt = now - prev;

        prev = now;


        backend.drawFrame(scene);

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
                case SDL_QUIT: {
                    quit = true;
                } 
                break;
            }
        }
    }


    return 0;
}