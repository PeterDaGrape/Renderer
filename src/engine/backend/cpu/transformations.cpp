#include "engine/backend/cpu/transformations.h"
#include <iostream>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>


using namespace std;


Point vertexWorldToScreen(Window* window, Camera* camera, Vec3* vertex) {

    // steps:
    // 1. convert coordinates to camera coordinates
    // 2. 

    // 1
    Vec3 worldPoint = *vertex - camera->getLocation();
    Point point;
    if (worldPoint.z < 0) {
        return Point{-1, -1};
    }

    gsl_matrix* projMat = camera -> getProjectionMatrix();


    gsl_matrix* coordinateMat = gsl_matrix_alloc(4, 1);
    gsl_matrix_set(coordinateMat, 0, 0, worldPoint.x);
    gsl_matrix_set(coordinateMat, 1, 0, worldPoint.y);
    gsl_matrix_set(coordinateMat, 2, 0, worldPoint.z);
    gsl_matrix_set(coordinateMat, 3, 0, 1);

    gsl_matrix* resultMat = gsl_matrix_alloc(4, 1);
 

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, projMat, coordinateMat, 0.0, resultMat);
    


    float x_ndc = gsl_matrix_get(resultMat, 0, 0) / gsl_matrix_get(resultMat, 3, 0);
    float y_ndc = gsl_matrix_get(resultMat, 1, 0) / gsl_matrix_get(resultMat, 3, 0);
    
    point.x = (-x_ndc + 1.0f) * 0.5f * window->getWidth();
    point.y = (1.0f - y_ndc) * 0.5f * window->getHeight();
    
    return point;
}




bool inBounds(Point p, int width, int height) {
    if (p.x < width && p.x >= 0 || p.y < height && p.y >= 0) {
        return true;
    }
    return false;
}


