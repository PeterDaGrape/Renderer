#pragma once
#include "globals.h"
#include <string>
#include <vector>



class Face {
    private:
    
    std::vector<Vec3*> vertices;
    Vec3 normal;

    public:
    Face(Vec3 n);
    Face();
    void setNormal(Vec3 n);
    const Vec3& getNormal() const {return normal; }
    void addVertex(Vec3* v_ptr);
    const Vec3 calculateMidpoint() const;

    const std::vector<Vec3*>& getVertexPtrs() const {return vertices; }
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
    const std::vector<Face>& getFaces() const {return faces;}

    Face getFace(int index);

};