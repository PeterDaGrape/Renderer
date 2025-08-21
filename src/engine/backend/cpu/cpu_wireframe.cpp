#include "engine/backend/cpu/cpu_wireframe.h"
#include <iostream>
#include <vector>
#include "scene/object.h"
#include "engine/backend/cpu/transformations.h"

using namespace std;

CPUWireframe::CPUWireframe(int width, int height)
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


    SDL_Renderer* renderer = SDL_CreateRenderer(window->getScreen(), -1, SDL_RENDERER_SOFTWARE);
    window->setRenderer(renderer);


    int renderWidth;
    int renderHeight;
    if (SDL_GetRendererOutputSize(renderer, &renderWidth, &renderHeight) != 0) {
        cerr << "Could not get output size" << endl;
    } else {
        cout << "Width: " << renderWidth << " Height: " << renderHeight << endl;
    }

    window -> setWidth(renderWidth);
    window -> setHeight(renderHeight);

}

void CPUWireframe::drawFrame(Scene *scene)
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

void CPUWireframe::drawObject(Camera *camera, Object object)
{

    SDL_Renderer *renderer = window->getRenderer();

    //cout << "Rendering object: " << object.getName() << endl;

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

    for (Face face : object.getFaces()) {

        vector<Vec3> vertices = face.getVertices();

        Vec3 temp = face.calculateMidpoint();
        
        //Point test = vertexWorldToScreen(window, camera, &temp);
        //SDL_RenderDrawPoint(renderer, test.x, test.y);
        
        
        //backface culling
        Vec3 faceVector = face.calculateMidpoint() - camera->getLocation();

        Vec3 normal = face.getNormal();

        if (normal.dot(faceVector) > 1e-6) {
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);


        Point prevPoint{-1, -1};

        for (int i = 0; i <= vertices.size(); i++) {


            Point p = vertexWorldToScreen(window, camera, &vertices[(i + 1) % vertices.size()]);

            if (inBounds(p, window->getWidth(), window->getHeight()) && inBounds(prevPoint, window->getWidth(), window->getHeight())){
                SDL_RenderDrawLine(renderer, p.x, p.y, prevPoint.x, prevPoint.y);
            }

            prevPoint = p;
        }
    }
}
