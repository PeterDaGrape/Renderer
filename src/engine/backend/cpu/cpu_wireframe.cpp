#include "engine/backend/cpu/cpu_wireframe.h"
#include <iostream>
#include <vector>
#include "scene/object.h"
#include "engine/backend/cpu/transformations.h"

using namespace std;

CPUWireframe::CPUWireframe()
{
     
}

void CPUWireframe::drawFrame(int width, int height, Scene* scene, SDL_Renderer* renderer) {


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (const Object& object : scene -> getObjects()) {
        drawObject(width, height, scene->getCamera(), object, renderer);
    }

 }

void CPUWireframe::drawObject(int width, int height, Camera* camera, const Object& object, SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);


    for (const Face& face : object.getFaces()) {

        const vector<Vec3*>& vertices = face.getVertexPtrs();

        
        //backface culling
        Vec3 faceVector = *vertices.at(0) - camera->getLocation();

        Vec3 normal = face.getNormal();

        if (normal.dot(faceVector) > 1e-6) {
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        Point prevPoint{-1, -1};

        for (int i = 0; i <= vertices.size(); i++) {

            Point p = vertexWorldToScreen(width, height, camera, vertices[(i + 1) % vertices.size()]);

            if (inBounds(p, width, height) && inBounds(prevPoint, width, height)){
                SDL_RenderDrawLine(renderer, p.x, p.y, prevPoint.x, prevPoint.y);
            }

            prevPoint = p;
        }
    }
}
