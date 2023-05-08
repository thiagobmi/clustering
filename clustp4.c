#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
// Definição de estruturas
struct ponto
{
    int *X;
    int *Y;
};

typedef struct ponto point_t;

struct centroids
{
    float *X;
    float *Y;
};

typedef struct centroids centroid_t;

// Verificações de memória
int checkMemCentroid(centroid_t *centro)
{
    if (centro == NULL)
    {
        printf("ERRO\n");
        exit(0);
        return 0;
    }
}

int checkMemPointArr(point_t *points)
{
    if (points == NULL)
    {
        printf("ERRO point arr\n");
        exit(0);
        return 0;
    }
}

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

// Alocação de memória
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
point_t *newPointArr(int n)
{
    point_t *points = (point_t *)malloc(sizeof(point_t) * n);
    checkMemPointArr(points);

    for (int i = 0; i < n; i++)
    {
        points[i].X = (int *)malloc(sizeof(int));
        checkMemIntArr(points[i].X);
    }
    for (int i = 0; i < n; i++)
    {
        points[i].Y = (int *)malloc(sizeof(int));
        checkMemIntArr(points[i].Y);
    }
    return points;
}

centroid_t *newCentroidArr(int k)
{
    centroid_t *centroids = malloc(sizeof(float) * k * 5);
    checkMemCentroid(centroids);

    for (int i = 0; i < k; i++)
    {
        centroids[i].X = (float *)malloc(sizeof(float));
        checkMemFloatArr(centroids[i].X);
    }
    for (int i = 0; i < k; i++)
    {
        centroids[i].Y = (float *)malloc(sizeof(float));
        checkMemFloatArr(centroids[i].Y);
    }
    return centroids;
}

point_t *reallocPointArr(point_t *points, int current_size, int n)
{
    points = realloc(points, (sizeof(point_t) * n));
    checkMemPointArr(points);

    for (int i = current_size; i < n; i++)
    {
        points[i].X = (int *)malloc(sizeof(int));
        checkMemIntArr(points[i].X);
        points[i].Y = (int *)malloc(sizeof(int));
        checkMemIntArr(points[i].Y);
    }

    return points;
}

void resetIntArr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = 0;
}

// Liberação de memória;
void freeFloatMatrix(float **arr, int k)
{
    for (int i = 0; i < k; i++)
        free(arr[i]);

    free(arr);
}
void freeMemory(float *shorter_distance, float **distance, int k)
{
    freeFloatMatrix(distance, k);
    free(shorter_distance);
}

// Atribuição dos valores como points

point_t *generateRandomPoints(point_t *points, int n, int n_sum)
{

    srand(time(NULL));
    for (n; n < n_sum; n++)
    {
        *points[n].X = -2000 + rand() % 5000;
        *points[n].Y = -2000 + rand() % 5000;
    }

    return points;
}

point_t *readPoints(point_t *points, int n, int n_sum)
{

    for (n; n < n_sum; n++)
    {
        scanf("%d %d", points[n].X, points[n].Y);
    }

    return points;
}

point_t *addPointsToArray(point_t *points, int n, int n_sum, int flag)
{
    if (flag == 0)
        return generateRandomPoints(points, n, n_sum);
    else
        return readPoints(points, n, n_sum);
}

// Randomiza os old_centroids em algum ponto
int getRandomPointIndex(int random_point_index, int *rand_arr, int count_rand, int n)
{
    random_point_index = rand() % n;

    for (int j = 0; j < count_rand; j++)
        while (random_point_index == rand_arr[j])
            random_point_index = rand() % n;

    return random_point_index;
}

float **getDistances(point_t *points, centroid_t *centroids, int n, int k)
{

    float **distance = newFloatMatrix(k, n);

    for (int j = 0; j < k; j++)
    {
        for (int i = 0; i < n; i++)
        {
            distance[j][i] = sqrt(pow((*points[i].X - *centroids[j].X), 2) + pow((*points[i].Y - *centroids[j].Y), 2));
        }
    }
    return distance;
}

float *getShorterDistances(float **distance, int n, int k)
{
    int shorter;
    float *shorter_distance = newFloatArr(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (distance[j][i] < shorter || j == 0)
            {
                shorter_distance[i] = distance[j][i];
                shorter = distance[j][i];
            }
        }
    }
    return shorter_distance;
}

void calculateNewCentroids(point_t *points, centroid_t *centroids, centroid_t *old_centroids, int **cluster, double *sumX, double *sumY, int *count, int k)
{
    int i, j;

    for (i = 0; i < k; i++)
        for (int j = 0; j < count[i]; j++)
        {
            sumX[i] += *points[cluster[i][j]].X;
            sumY[i] += *points[cluster[i][j]].Y;
        }

    for (i = 0; i < k; i++)
    {
        *centroids[i].X = (sumX[i] / count[i]);
        *centroids[i].Y = (sumY[i] / count[i]);

        if (count[i] == 0)
        {
            *centroids[i].X = *old_centroids[i].X;
            *centroids[i].Y = *old_centroids[i].Y;
        }
    }

    for (i = 0; i < k; i++)
    {
        *old_centroids[i].X = *centroids[i].Y;
        *old_centroids[i].Y = *centroids[i].Y;
    }

    resetIntArr(count, k);
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

point_t *receiveAdditionalPoints(int n, int k, int flag)
{

    int current_size = 0, additional_size = 0;
    point_t *pointArr = newPointArr(n);
    while (n < k)
    {
        if (current_size > 0)
            pointArr = reallocPointArr(pointArr, current_size, n);

        pointArr = addPointsToArray(pointArr, current_size, n, flag);
        scanf("%d", &additional_size);
        current_size = n;
        n += additional_size;
    }

    pointArr = reallocPointArr(pointArr, current_size, n);
    pointArr = addPointsToArray(pointArr, current_size, n, flag);

    return pointArr;
}

void printFile(centroid_t *centroids, point_t *points, int **cluster, char *str, char *nome, int *count, int numfile, int n, int k)
{

    sprintf(str, "%d", numfile);
    strcat(nome, str);
    FILE *pont_arq = fopen(nome, "w");

    for (int i = 0; i < k; i++)
    {
        fprintf(pont_arq, "%.2f;%.2f;0\n", *centroids[i].X, *centroids[i].Y);
        for (int j = 0; j < count[i]; j++)
            fprintf(pont_arq, "%d;%d;1\n", *points[cluster[i][j]].X, *points[cluster[i][j]].Y);
    }

    fclose(pont_arq);
}

int **assignArrays(float **distance, float *shorter_distance, int *count, int n, int k)
{
    int **is_shorter_distance = newIntMatrix(k, n);
    for (int j = 0; j < k; j++)
        for (int i = 0; i < n; i++)
        {
            if (distance[j][i] == shorter_distance[i])
            {
                count[j]++;
                is_shorter_distance[j][i] = i;
            }
            else
                is_shorter_distance[j][i] = -20;
        }
    return is_shorter_distance;
}

centroid_t *randomizeCentroids(point_t *points, int n, int k)
{
    unsigned int count_rand = 0, random_point_index;
    centroid_t *old_centroids = newCentroidArr(k);
    unsigned int *rand_arr = newIntArr(k);

    for (int i = 0; i < k; i++)
    {
        random_point_index = getRandomPointIndex(random_point_index, rand_arr, count_rand, n);
        count_rand++;
        rand_arr[i] = random_point_index;
        *old_centroids[i].X = *points[random_point_index].X;
        *old_centroids[i].Y = *points[random_point_index].Y;
    }
    free(rand_arr);
    return old_centroids;
}

int **processData(centroid_t *centroids, point_t *points, int *count, int n, int k)
{
    unsigned int i, j;
    float **distance;
    float *shorter_distance;
    int **is_shorter_distance;

    distance = getDistances(points, centroids, n, k);
    shorter_distance = getShorterDistances(distance, n, k);
    is_shorter_distance = assignArrays(distance, shorter_distance, count, n, k);
    freeMemory(shorter_distance, distance, k);
    return is_shorter_distance;
}

int **createCluster(int **is_shorter_distance, int *count, int n, int k)
{
    int **cluster = newCluster(count, k);
    int point_count = 0;
    for (int i = 0; i < k; i++)
    {
        point_count = 0;
        while (point_count < count[i])
            for (int j = 0; j < n; j++)
            {
                if (is_shorter_distance[i][j] != -20)
                {
                    cluster[i][point_count] = is_shorter_distance[i][j];
                    point_count++;
                }
            }
    }

    return cluster;
}

point_t *addPoints(point_t *points, int n, int n_plus, int flag)
{
    unsigned int n_sum = n + n_plus;

    points = realloc(points, sizeof(point_t) * ((n_sum)));
    checkMemPointArr(points);

    for (int current_size = n; current_size < n_sum; current_size++)
    {
        points[current_size].X = (int *)malloc(sizeof(int));
        checkMemIntArr(points[current_size].X);
        points[current_size].Y = (int *)malloc(sizeof(int));
        checkMemIntArr(points[current_size].Y);
    }

    addPointsToArray(points, n, n_sum, flag);

    return points;
}

void freeClusterMemory(int **cluster, int **is_shorter_distance, int k)
{
    for (int i = 0; i < k; i++)
    {
        free(is_shorter_distance[i]);
        free(cluster[i]);
    }
}

void hMeans(int argc, char *argv[])
{

    int n;
    int k;
    int iterations;
    int flag;
    int n_plus;
    int current_size = 0;
    int numfile = 0;
    point_t *points;
    FILE *pont_arq;

    n = atoi(argv[1]);
    k = atoi(argv[2]);
    iterations = atoi(argv[3]);
    flag = atoi(argv[4]);

    double *sumX = newDoubleArr(k), *sumY = newDoubleArr(k);
    int *count = newIntArr(k);
    centroid_t *centroids = newCentroidArr(k);
    resetIntArr(count, k);
    centroid_t *old_centroids;
    int **cluster, **is_shorter_distance;

    if (n < k)
    {
        points = receiveAdditionalPoints(n, k, flag);
    }
    else
    {
        points = newPointArr(n);
        points = addPointsToArray(points, 0, n, flag);
    }

    old_centroids = randomizeCentroids(points, n, k);
    is_shorter_distance = processData(old_centroids, points, count, n, k);
    cluster = createCluster(is_shorter_distance, count, n, k);
    calculateNewCentroids(points, centroids, old_centroids, cluster, sumX, sumY, count, k);
    freeClusterMemory(cluster, is_shorter_distance, k);

    for (int l = 0; l < iterations; l++)
    {
        printf("\nL = %d\n", l);
        is_shorter_distance = processData(centroids, points, count, n, k);
        cluster = createCluster(is_shorter_distance, count, n, k);
        resetSum(sumX, sumY, k);
        calculateNewCentroids(points, centroids, old_centroids, cluster, sumX, sumY, count, k);

        if (l == iterations - 1)
            scanf("%d", &n_plus);

        if (n_plus > 0)
        {
            points = addPoints(points, n, n_plus, flag);
            n += n_plus;
            n_plus = 0;
            l = 0;
        }

        freeClusterMemory(cluster, is_shorter_distance, k);
    }
}

int main(int argc, char *argv[])
{
    hMeans(argc, argv);
}
