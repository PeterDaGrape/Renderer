#pragma once
#include <string>
#include <scene/object.h>
#include <vector>
#include "camera.h"


class Scene {
    private:

    std::vector<Object> objects;
    
    Camera* camera;
    
    static Scene* scene;
    Scene();

    public:


    int loadMeshes(std::string pathname);

    void setCamera(Camera* c);
    Camera* getCamera();

    std::vector<Object> getObjects(){ return objects;}

    // Deleting the copy constructor to prevent copies
    Scene(const Scene& obj) = delete;
    static Scene* getInstance() {
        if (scene == nullptr) {
            if (scene == nullptr) {
                scene = new Scene();
            }
        }
        return scene;
    }
};