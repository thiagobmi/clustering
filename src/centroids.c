#include"../include/centroids.h"
#include"../include/functions.h"

int checkMemCentroid(centroid_t *centro)
{
    if (centro == NULL)
    {
        printf("ERRO\n");
        exit(0);
        return 0;
    }
}

centroid_t *newCentroidArr(int k)
{
    centroid_t *centroids =(centroid_t*) malloc(sizeof(centroid_t) * k);
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