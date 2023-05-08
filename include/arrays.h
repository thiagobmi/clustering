#ifndef ARRAYS_H
#define ARRAYS_H 1

#include<stdio.h>
#include<stdlib.h>

int checkMemIntArr(int *arr);
int checkMemFloatArr(float *arr);
int checkMemFloatMatrix(float **arr);
int checkMemIntMatrix(int **arr);
float *newFloatArr(int size);
float **newFloatMatrix(int rows, int cols);
double *newDoubleArr(int size);
void resetSum(double *sumX, double *sumY, int k);
int *newIntArr(int size);
int **newIntMatrix(int rows, int cols);
int **newCluster(int *count, int k);
void resetIntArr(int *arr, int size);
void freeFloatMatrix(float **arr, int k);
void freeDistancesMemory(float *shorter_distance, float **distance, int k);
void freeClusterMemory(int **cluster, int **is_shorter_distance, int k);

#endif