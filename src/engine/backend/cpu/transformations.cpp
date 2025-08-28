#include "engine/backend/cpu/transformations.h"
#include <math.h>
#include <iostream>

using namespace std;


void matMul4x4X4x1(const float (&matrixA)[4][4], const float (&matrixB)[4], float (&result)[4]) {


    for (int i = 0; i < 4; i++) {
        result[i] = 0;

        for (int k = 0; k < 4; k++) {
            result[i] += matrixA[k][i] * matrixB[k];
        }
    }
}

void applyRotations(Vec3 rotationVec, float (&matrix)[4]) {
    float theta;
    float workingCopy[4];
    

    theta = rotationVec.x;

    memcpy(workingCopy, matrix, 4 * sizeof(float));

    float rotMatX[4][4] {
        {1, 0, 0, 0},
        {0, cos(theta), -sin(theta), 0},
        {0, sin(theta), cos(theta), 0},
        {0, 0, 0, 1}
    };

    matMul4x4X4x1(rotMatX, workingCopy, matrix);

    
    memcpy(workingCopy, matrix, 4 * sizeof(float));
    theta = rotationVec.y;

    float rotMatY[4][4] {
        {cos(theta), 0, sin(theta), 0},
        {0, 1, 0, 0},
        {-sin(theta), 0, cos(theta), 0},
        {0, 0, 0, 1}
    };

    matMul4x4X4x1(rotMatY, workingCopy, matrix);


    memcpy(workingCopy, matrix, 4 * sizeof(float));
    theta = rotationVec.z;

    float rotMatZ[4][4] {
        {cos(theta), -sin(theta), 0, 0},
        {sin(theta), cos(theta), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    matMul4x4X4x1(rotMatZ, workingCopy, matrix);


}



Point vertexWorldToScreen(Window* window, Camera* camera, Vec3* vertex) {

    Vec3 worldPoint = *vertex - camera -> getLocation();
    Point point;
    float x_ndc;
    float y_ndc;
    float z_ndc;
    

    //matrix shit
    float (&projectionMatrix)[4][4] = camera -> get4x4ProjMat();

    float worldPointArray[4] = {
        worldPoint.x,
        worldPoint.y,
        worldPoint.z,
        1
    };

    applyRotations(camera -> getRotation(), worldPointArray);
    
    float resultMat[4];

    //matmul
    matMul4x4X4x1(projectionMatrix, worldPointArray, resultMat);

    
    x_ndc = resultMat[0] / resultMat[3];
    y_ndc = resultMat[1] / resultMat[3];
    z_ndc = resultMat[2] / resultMat[3];


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
