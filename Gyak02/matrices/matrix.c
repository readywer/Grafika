#include "matrix.h"

#include <stdio.h>
#include <math.h>

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}
void init_identity_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
            if(i==j) matrix[i][j] = 1.0;
        }
    }
}
void print_matrix(const float a[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", a[i][j]);
        }
        printf("\n");
    }
}
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}
void print_vector(const float vector[3][1]){
    int i;
    int j;
    for (i = 0; i < 3; ++i) {
        printf("%4.4f ", vector[i][0]);
        printf(" ");
    }
    printf("\n");
}
void scalar(float a[3][3], float l, float c[3][3]){
    int i;
    int j;
    init_zero_matrix(c);
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j]=l*a[i][j];
        }
    }
}
void multiply_matrices(float a[3][3], float b[3][3], float c[3][3]){
    int i, j, k;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j]=0;
            for(k=0; k<3; k++){
                c[i][j]+= a[i][k]*b[k][j];
            }
        }
    }
}
void transform_point(float a[3][3], float vector[3][1], float result[3][1]){
    int i;
    int j;
    for (i = 0; i < 3; ++i) {
        result[i][0]=0;
        for (j = 0; j < 3; ++j) {
            result[i][0]+=a[i][j]*vector[j][0];
        }
    }
}
void scale(float a[3][3], float s_x, float s_y){
    int i,j;
    float tempmatrix[3][3];
    init_identity_matrix(tempmatrix);
    float resultm[3][3];
    init_identity_matrix(resultm);
    tempmatrix[0][0]=s_x;
    tempmatrix[1][1]=s_y;
    multiply_matrices(tempmatrix, a, resultm);
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            a[i][j]=resultm[i][j];
        }
    }
}
void shift(float matrix[3][3], float d_x, float d_y){
    int i,j;
    float tmatrix[3][3];
    init_identity_matrix(tmatrix);
    float result[3][3];
    init_identity_matrix(result);
    tmatrix[0][2]=d_x;
    tmatrix[1][2]=d_y;
    multiply_matrices(tmatrix, matrix, result);
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            matrix[i][j]=result[i][j];
        }
    }
}
void rotate(float a[3][3], float angle){
    int i,j;
    float radian=angle/180*(atan(1)*4);
    float tempmatrix[3][3];
    init_identity_matrix(tempmatrix);
    float resultM[3][3];
    init_identity_matrix(resultM);
    tempmatrix[0][0]=cos(radian);
    tempmatrix[0][1]=-sin(radian);
    tempmatrix[1][0]=sin(radian);
    tempmatrix[1][1]=cos(radian);
    multiply_matrices(tempmatrix, a, resultM);
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            a[i][j]=resultM[i][j];
        }
    }
}
