#include "../include/hMeans.h"

void hMeans(int argc, char *argv[])
{
    int n;
    int k;
    int iterations;
    int flag;
    int n_plus=0;
    int current_size = 0;
    int numfile = 0;
    point_t *points;
    FILE *pont_arq;

    n = 0, k = 0, iterations = 0, flag = 0;

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
        points = receiveAdditionalPoints(n, k, flag);
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
        printf("Iteracao: %d\n", l);
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
    free(points);
    free(centroids);
}