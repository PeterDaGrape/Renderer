#include "object.h" 
#include <iostream>
#include <vector>
#include "globals.h"
using namespace std;


Face::Face(Normal n) {
    normal = n;
}

Face::Face() {
    
}

void Face::addVertex(Vec3* v_ptr) {
    vertices.push_back(v_ptr);
}

vector<Vec3> Face::getVertices() {
    vector<Vec3> returnVertices;
    for (int i = 0; i < vertices.size(); i++) {
        returnVertices.push_back(*vertices.at(i));
    }
    return returnVertices;
}


void Face::setNormal(Normal n) {
    this -> normal = n;
}

Object::Object(string name) {
    this->name = name;
}



void Object::addVertex(Vec3 v) {
    this -> vertices.push_back(v);
}

void Object::addFace(Face f) {
    this -> faces.push_back(f);
}

Vec3 Object::getVertex(int index) {
    return this -> vertices.at(index);
}

Vec3* Object::getVertexPtr(int index) {
    return &this -> vertices.at(index); 
}

Face Object::getFace(int index) {
    return this -> faces.at(index);
}