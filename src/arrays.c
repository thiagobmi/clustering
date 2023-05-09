#include"../include/arrays.h"

int checkMemIntArr(int *arr)
{
    if (arr == NULL)
    {
        printf("ERRO int arr\n");
        exit(0);
        return 0;
    }
}

int checkMemFloatArr(float *arr)
{
    if (arr == NULL)
    {
        printf("ERRO float arr\n");
        exit(0);
        return 0;
    }
}

int checkMemFloatMatrix(float **arr)
{

    if (arr == NULL)
    {
        printf("ERRO float matrix\n");
        exit(0);
        return 0;
    }
}

int checkMemIntMatrix(int **arr)
{

    if (arr == NULL)
    {
        printf("ERRO int matrix\n");
        exit(0);
        return 0;
    }
}

float *newFloatArr(int size)
{
    float *arr = (float *)malloc(sizeof(float) * size);
    checkMemFloatArr(arr);
    return arr;
}

float **newFloatMatrix(int rows, int cols)
{
    float **arr = (float **)malloc(sizeof(float *) * rows);

    for (int i = 0; i < rows; i++)
        arr[i] = newFloatArr(cols);

    return arr;
}


double *newDoubleArr(int size)
{
    double *arr = (double *)malloc(sizeof(double) * size);
    return arr;
}

void resetSum(double *sumX, double *sumY, int k)
{
    for (int i = 0; i < k; i++)
    {
        sumX[i] = 0;
        sumY[i] = 0;
    }
}

int *newIntArr(int size)
{
    int *arr = (int *)malloc(sizeof(int) * size);
    checkMemIntArr(arr);
    return arr;
}

int **newIntMatrix(int rows, int cols)
{
    int **arr = (int **)malloc(sizeof(int) * rows * 2);
    for (int i = 0; i < rows; i++)
        arr[i] = newIntArr(cols);

    return arr;
}

int **newCluster(int *count, int k)
{

    int **cluster = (int **)malloc(sizeof(int *) * k);
    checkMemIntMatrix(cluster);

    for (int i = 0; i < k; i++)
        cluster[i] = newIntArr(count[i]);

    return cluster;
}

void resetIntArr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = 0;
}

void freeFloatMatrix(float **arr, int k)
{
    for (int i = 0; i < k; i++)
        free(arr[i]);

    free(arr);
}

void freeDistancesMemory(float *shorter_distance, float **distance, int k)
{
    freeFloatMatrix(distance, k);
    free(shorter_distance);
}

void freeClusterMemory(int **cluster, int **is_shorter_distance, int k)
{
    for (int i = 0; i < k; i++)
    {
        free(is_shorter_distance[i]);
        free(cluster[i]);
    }
    free(cluster);
    free(is_shorter_distance);
}