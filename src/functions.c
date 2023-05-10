#include"../include/functions.h"


float **getDistances(point_t *points, centroid_t *centroids, int n, int k)
{
    float **distance = newFloatMatrix(k, n);

    for (int j = 0; j < k; j++)
    {
        for (int i = 0; i < n; i++)
        {
            distance[j][i] = sqrt(pow((points[i].X - centroids[j].X), 2) + pow((points[i].Y - centroids[j].Y), 2));
        }
    }
    return distance;
}

float *getShorterDistances(float **distance, int n, int k)
{
    int shorter=0;
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
            sumX[i] += points[cluster[i][j]].X;
            sumY[i] += points[cluster[i][j]].Y;
        }

    for (i = 0; i < k; i++)
    {
        centroids[i].X = (sumX[i] / count[i]);
        centroids[i].Y = (sumY[i] / count[i]);

        if (count[i] == 0)
        {
            centroids[i].X = old_centroids[i].X;
            centroids[i].Y = old_centroids[i].Y;
        }
    }

    for (i = 0; i < k; i++)
    {
        old_centroids[i].X = centroids[i].Y;
        old_centroids[i].Y = centroids[i].Y;
    }

    resetIntArr(count, k);
}

int getRandomPointIndex(int random_point_index, int *rand_arr, int count_rand, int n)
{
    random_point_index = rand() % n;

    for (int j = 0; j < count_rand; j++)
        while (random_point_index == rand_arr[j])
            random_point_index = rand() % n;

    return random_point_index;
}


void printFile(centroid_t *centroids, point_t *points, int **cluster, char *str, char *file_name, int *count, int numfile, int n, int k)
{

    sprintf(str, "%d", numfile);
    strcat(file_name, str);
    FILE *pont_arq = fopen(file_name, "w");

    for (int i = 0; i < k; i++)
    {
        fprintf(pont_arq, "%.2f;%.2f;0\n", centroids[i].X, centroids[i].Y);
        for (int j = 0; j < count[i]; j++)
            fprintf(pont_arq, "%d;%d;1\n", points[cluster[i][j]].X, points[cluster[i][j]].Y);
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

int **processData(centroid_t *centroids, point_t *points, int *count, int n, int k)
{
    unsigned int i, j;
    float **distance;
    float *shorter_distance;
    int **is_shorter_distance;

    distance = getDistances(points, centroids, n, k);
    shorter_distance = getShorterDistances(distance, n, k);
    is_shorter_distance = assignArrays(distance, shorter_distance, count, n, k);
    freeDistancesMemory(shorter_distance, distance, k);
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
                if (is_shorter_distance[i][j] != -20)
                {
                    cluster[i][point_count] = is_shorter_distance[i][j];
                    point_count++;
                }
    }

    return cluster;
}