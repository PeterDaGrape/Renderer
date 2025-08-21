#pragma once
#include "globals.h"
#include <string>
#include <vector>

struct Normal {
    float x;
    float y;
    float z; 
};

class Face {
    private:
    
    std::vector<Vec3*> vertices;
    Normal normal;

    public:
    Face(Normal n);
    Face();
    void setNormal(Normal n);
    void addVertex(Vec3* v_ptr);

    std::vector<Vec3> getVertices();
};

class Object {
    private:
    std::string name;

    std::vector<Vec3> vertices;
    std::vector<Face> faces;

    public:
    Object();
    Object(std::string name);
    
    void addVertex(Vec3 v);
    void addFace(Face f);

    Vec3 getVertex(int index);

    std::string getName() { return name; }

    Vec3* getVertexPtr(int index);

    std::vector<Vec3> getVertices() {return vertices;}
    std::vector<Face> getFaces() {return faces;}

    Face getFace(int index);

};