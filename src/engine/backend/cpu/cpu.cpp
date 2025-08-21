#include "engine/backend/cpu/cpu.h"
#include <iostream>
#include <vector>
#include "scene/object.h"
#include "engine/backend/cpu/transformations.h"

using namespace std;

CPU::CPU(int width, int height)
{
    window = new Window(600, 480);
    
    SDL_Init(SDL_INIT_VIDEO);


    window -> setWindow(
        SDL_CreateWindow(
            "3D Renderer",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, 
            height, 
            SDL_WINDOW_ALLOW_HIGHDPI
        )
    );


    window->setRenderer(
        SDL_CreateRenderer(window->getScreen(), -1, SDL_RENDERER_SOFTWARE)
    );
}

void CPU::drawFrame(Scene *scene)
{

    SDL_Renderer *renderer = window->getRenderer();

    std::vector<Object> objects = scene->getObjects();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < objects.size(); i++)
    {

        drawObject(scene->getCamera(), objects[i]);
    }

    SDL_RenderPresent(renderer);
}

void CPU::drawObject(Camera *camera, Object object)
{

    SDL_Renderer *renderer = window->getRenderer();

    cout << "Rendering object: " << object.getName() << endl;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // SDL_RenderDrawPoint(renderer, static_cast<int>(300), static_cast<int>(240));


    
    for (Face face : object.getFaces()) {



        vector<Vec3> vertices = face.getVertices();

        for (int i = 0; i < vertices.size(); i++) {

            Point p1 = vertexWorldToScreen(window, camera, &vertices[i]);
            Point p2 = vertexWorldToScreen(window, camera, &vertices[(i + 1) % vertices.size()]);


            SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
        }


        for (Vec3 &v : vertices)
        {

            Point screenSpacePoint = vertexWorldToScreen(window, camera, &v);

            SDL_RenderDrawPoint(renderer, screenSpacePoint.x, screenSpacePoint.y);
        }

    }
    return;

}
