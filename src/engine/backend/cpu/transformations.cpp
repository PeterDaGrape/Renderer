#include "engine/backend/cpu/transformations.h"
#include <iostream>
#include <math.h>
using namespace std;


Point vertexWorldToScreen(Window* window, Camera* camera, Vec3* vertex) {
    Vec3 worldPoint = *vertex - camera->getLocation();

    float aspect = window->getWidth() / (float)window->getHeight();
    float scale = 1.0f / tan(camera->getFOV() * (M_PI / 180.0f) * 0.5f);

    float x_ndc = (worldPoint.x / -worldPoint.z) * scale / aspect;
    float y_ndc = (worldPoint.y / -worldPoint.z) * scale;

    Point point;
    point.x = (x_ndc + 1.0f) * 0.5f * window->getWidth();
    point.y = (1.0f - y_ndc) * 0.5f * window->getHeight(); // Y inverted for screen coords

    return point;
}