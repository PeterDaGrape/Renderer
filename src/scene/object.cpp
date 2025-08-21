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

Vec3 Face::calculateMidpoint() {
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

vector<Vec3> Face::getVertices() {
    vector<Vec3> returnVertices;
    for (int i = 0; i < vertices.size(); i++) {
        returnVertices.push_back(*vertices.at(i));
    }
    return returnVertices;
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