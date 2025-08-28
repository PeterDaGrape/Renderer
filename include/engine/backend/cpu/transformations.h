#pragma once
#include "engine/window.h"
#include "scene/camera.h"
#include "scene/object.h"
#include "globals.h"



Point vertexWorldToScreen(Window* window, Camera* camera, Vec3* vertex);
bool inBounds(Point p, int width, int height);
