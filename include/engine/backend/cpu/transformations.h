#pragma once
#include "scene/camera.h"
#include "scene/object.h"
#include "globals.h"



const Point vertexWorldToScreen(int width, int height, Camera* camera, Vec3* vertex);
bool inBounds(Point p, int width, int height);
