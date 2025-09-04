#include "scene/scene.h"
#include "scene/object.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "globals.h"
using namespace std;

Scene* Scene::scene = nullptr;

Scene::Scene() {
    cout << "Scene object has been made" << endl;
}

void Scene::setCamera(Camera* c) {
    this -> camera = c;
}

Camera* Scene::getCamera() {
    return camera;
}


int Scene::loadMeshes(string pathname) {

    cout << "loading mesh from: " << pathname <<endl;

    ifstream file(pathname, ios::in);


    //in obj vertex indices are not reset with new object, must offset at end of each object
    int vertOffset = 0;


    if (file.is_open()) {

        cout << "File opened successfully." << endl;

        string line;

        vector<Vec3> normals;

        while (getline(file, line)) {
            //cout << line << endl;
            if (line[0] == 'o') {
                //Line describes an object
                string objectName = line.substr(2, line.length());
                cout << "creating object called: " << objectName << endl;

                if (objects.size() > 0) {
                    //cout << "Incrementing offset " << endl; 
                    vertOffset += objects.at(objects.size() - 1).getVertices().size();
                }

                Object object(objectName);
                this -> objects.push_back(object);
            } else if (line[0] == 'v' && line[1] == ' ') {
                //Line is describing a vertex


                string data = line.substr(2, line.length());
                
                std::array<float, 3> values{};
                std::istringstream iss(data);

                float x, y, z;

                iss >> x >> y >> z;
                //cout << "x: " << x << " y: " << y << " z: " << z << endl ;

                Vec3 v;
                v.x = x;
                v.y = y;
                v.z = z;

                this -> objects.back().addVertex(v);
            
            } else if (line[0] == 'v' && line[1] == 'n') {
                //line is describing a normal

                string data = line.substr(2, line.length());
                std::array<float, 3> values{};
                std::istringstream iss(data);

                Vec3 n;
                iss >> n.x >> n.y >> n.z;
                //cout << "x: " << n.x << " y: " << n.y << " z: " << n.z << endl ;

                normals.push_back(n);

            } else if (line[0] == 'f') {
                //line describes a face
                // format face1 (vertex/texture/normal) 
                // Ignoring textures for now
                string data = line.substr(2, line.length());

                // Takes string in form:
                // 1/1/1 5/2/1 7/3/1 3/4/1
                // may also 
                //cout << str << endl;
                
                // Separate into strings separated by space

                Face face;

                istringstream iss(data);
                string s;
                while (getline(iss, s, ' ') ) {
                    //cout << s << endl;

                    //s is in form 2/13/6
                    // can be in form 2//6 without texture coords
                    istringstream slashString(s);
                    
                    string v, t, n; 

                    getline(slashString, v, '/');
                    getline(slashString, t, '/');
                    getline(slashString, n, '/');

                    int vertexID = stoi(v);
                    // commented out until it's needed
                    //int textureID = stoi(t); 
                    int normalID = stoi(n); 

                    //cout << "vID: " << vertexID << " tID: " << textureID << " normalID: " << normalID << endl;


                    face.setNormal(normals.at(normalID - 1));

                    face.addVertex(objects.back().getVertexPtr(vertexID - vertOffset - 1));

                }

                this -> objects.back().addFace(face);

            }
        }

        // Close the file
        file.close();



        cout << "File closed." << endl;
    }
    else {
        // Display error if file was not opened
        cerr << "Error opening file!" << endl;
        return -1;
    }


    return 0;
}

