#include "engine/backend/cpu/transformations.h"
#include <math.h>
#include <iostream>

using namespace std;


void matMul4x4X4x1(const float (&matrixA)[4][4], const float (&matrixB)[4], float (&result)[4]) {


    // Unrolled 4×4 × 4×1 multiplication (row‑major order)
    result[0] = matrixA[0][0] * matrixB[0] + matrixA[1][0] * matrixB[1] +
                matrixA[2][0] * matrixB[2] + matrixA[3][0] * matrixB[3];

    result[1] = matrixA[0][1] * matrixB[0] + matrixA[1][1] * matrixB[1] +
                matrixA[2][1] * matrixB[2] + matrixA[3][1] * matrixB[3];

    result[2] = matrixA[0][2] * matrixB[0] + matrixA[1][2] * matrixB[1] +
                matrixA[2][2] * matrixB[2] + matrixA[3][2] * matrixB[3];

    result[3] = matrixA[0][3] * matrixB[0] + matrixA[1][3] * matrixB[1] +
                matrixA[2][3] * matrixB[2] + matrixA[3][3] * matrixB[3];
}

void applyRotations(Vec3 rotationVec, float (&matrix)[4]) {
    float theta;
    float workingCopy[4];
    
    
    theta = rotationVec.x;
    float rotMatX[4][4] {
        {1, 0, 0, 0},
        {0, cos(theta), -sin(theta), 0},
        {0, sin(theta), cos(theta), 0},
        {0, 0, 0, 1}
    };

    theta = rotationVec.y;
    float rotMatY[4][4] {
        {cos(theta), 0, sin(theta), 0},
        {0, 1, 0, 0},
        {-sin(theta), 0, cos(theta), 0},
        {0, 0, 0, 1}
    };

    theta = rotationVec.z;
    float rotMatZ[4][4] {
        {cos(theta), -sin(theta), 0, 0},
        {sin(theta), cos(theta), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    
    memcpy(workingCopy, matrix, 4 * sizeof(float));
    matMul4x4X4x1(rotMatY, workingCopy, matrix);
    
    memcpy(workingCopy, matrix, 4 * sizeof(float));
    matMul4x4X4x1(rotMatX, workingCopy, matrix);

    memcpy(workingCopy, matrix, 4 * sizeof(float));
    matMul4x4X4x1(rotMatZ, workingCopy, matrix);


}



const Point vertexWorldToScreen(int width, int height, Camera* camera, Vec3* vertex) {

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


    point.x = (-x_ndc + 1.0f) * 0.5f * width;
    point.y = (1.0f - y_ndc) * 0.5f * height;
    
    return point;
}






bool inBounds(Point p, int width, int height) {
    return (p.x >= 0 && p.x < width) && (p.y >= 0 && p.y < height);
}
