#include "object.h" 
#include <iostream>
#include <vector>
#include "globals.h"
using namespace std;


Face::Face(Vec3 n) {
    normal = n;
}

Face::Face() {
    
}

const Vec3 Face::calculateMidpoint() const {
    Vec3 midpoint;
    for (Vec3* v : vertices) {
        midpoint = *v + midpoint;
    }
    midpoint = midpoint / vertices.size();
    return midpoint;
}

void Face::addVertex(Vec3* v_ptr) {
    vertices.push_back(v_ptr);
}




void Face::setNormal(Vec3 n) {
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