#include "engine/backend/cpu/transformations.h"
#include <iostream>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>


using namespace std;



void apply4x4coeffs(gsl_matrix* matrix, float coeffs[4][4]) {


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //cout << coeffs[i][j] << endl;
            gsl_matrix_set(matrix, j, i, coeffs[i][j]);
        }
    }

}

void applyRotations(Vec3 rotation, gsl_matrix* matrix) {
    float theta;
    // only need one, modify after each application
    gsl_matrix* rotationMatrix = gsl_matrix_alloc(4, 4); 


    theta = rotation.x;
    float coeffsX[4][4] {
        {1, 0, 0, 0},
        {0, cos(theta), -sin(theta), 0},
        {0, sin(theta), cos(theta), 0},
        {0, 0, 0, 1}
    };
    apply4x4coeffs(rotationMatrix, coeffsX);

    gsl_matrix* xApplied = gsl_matrix_alloc(4, 1);  
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, rotationMatrix, matrix, 0.0, xApplied);

    theta = rotation.y;
    float coeffsY[4][4] {
        {cos(theta), 0, sin(theta), 0},
        {0, 1, 0, 0},
        {-sin(theta), 0, cos(theta), 0},
        {0, 0, 0, 1}
    };
    apply4x4coeffs(rotationMatrix, coeffsY);

    gsl_matrix* yApplied = gsl_matrix_alloc(4, 1);  
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, rotationMatrix, xApplied, 0.0, yApplied);


    theta = rotation.z;
    float coeffsZ[4][4] {
        {cos(theta), -sin(theta), 0, 0},
        {sin(theta), cos(theta), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    apply4x4coeffs(rotationMatrix, coeffsZ);

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, rotationMatrix, yApplied, 0.0, matrix);

    gsl_matrix_free(rotationMatrix);    
    gsl_matrix_free(xApplied);    
    gsl_matrix_free(yApplied);   

}

void applyRotationsToVector(Vec3* vector, Vec3* rotation) {

    gsl_matrix* coordinateMat = gsl_matrix_alloc(4, 1);
    gsl_matrix_set(coordinateMat, 0, 0, vector -> x);
    gsl_matrix_set(coordinateMat, 1, 0, vector -> y);
    gsl_matrix_set(coordinateMat, 2, 0, vector -> z);
    gsl_matrix_set(coordinateMat, 3, 0, 1);

    gsl_matrix* resultMat = gsl_matrix_alloc(4, 1);

    applyRotations(*rotation, coordinateMat);
    
    vector -> x = gsl_matrix_get(coordinateMat, 0, 0);
    vector -> y = gsl_matrix_get(coordinateMat, 1, 0);
    vector -> z = gsl_matrix_get(coordinateMat, 2, 0);

    gsl_matrix_free(coordinateMat);
    gsl_matrix_free(resultMat);
 
}


Point vertexWorldToScreen(Window* window, Camera* camera, Vec3* vertex) {

    // steps:
    // 1. convert coordinates to camera coordinates
    // 2. apply rotation - not done
    // 3. apply perspective projection


    // 1
    Vec3 worldPoint = *vertex - camera->getLocation();
    Point point;

    gsl_matrix* projMat = camera -> getProjectionMatrix();

    gsl_matrix* coordinateMat = gsl_matrix_alloc(4, 1);
    gsl_matrix_set(coordinateMat, 0, 0, worldPoint.x);
    gsl_matrix_set(coordinateMat, 1, 0, worldPoint.y);
    gsl_matrix_set(coordinateMat, 2, 0, worldPoint.z);
    gsl_matrix_set(coordinateMat, 3, 0, 1);

    gsl_matrix* resultMat = gsl_matrix_alloc(4, 1);

    applyRotations(camera->getRotation(), coordinateMat);

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, projMat, coordinateMat, 0.0, resultMat);

    gsl_matrix_free(coordinateMat);    



    float x_ndc = gsl_matrix_get(resultMat, 0, 0) / gsl_matrix_get(resultMat, 3, 0);
    float y_ndc = gsl_matrix_get(resultMat, 1, 0) / gsl_matrix_get(resultMat, 3, 0);
    float z_ndc = gsl_matrix_get(resultMat, 2, 0) / gsl_matrix_get(resultMat, 3, 0);
    gsl_matrix_free(resultMat);    


    if (z_ndc < -1.0f || z_ndc > 1.0f) {
        return Point{-1, -1}; // outside clip space
    }    

    point.x = (-x_ndc + 1.0f) * 0.5f * window->getWidth();
    point.y = (1.0f - y_ndc) * 0.5f * window->getHeight();
    
    return point;
}




bool inBounds(Point p, int width, int height) {
    return (p.x >= 0 && p.x < width) && (p.y >= 0 && p.y < height);
}


