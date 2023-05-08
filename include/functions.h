#ifndef FUNCTIONS_H
#define FUNCTIONS_H 1

#include<math.h>
#include<string.h>
#include"centroids.h"


float **getDistances(point_t *points, centroid_t *centroids, int n, int k);
float *getShorterDistances(float **distance, int n, int k);
void calculateNewCentroids(point_t *points, centroid_t *centroids, centroid_t *old_centroids, int **cluster, double *sumX, double *sumY, int *count, int k);
int getRandomPointIndex(int random_point_index, int *rand_arr, int count_rand, int n);
void printFile(centroid_t *centroids, point_t *points, int **cluster, char *str, char *file_name, int *count, int numfile, int n, int k);
int **assignArrays(float **distance, float *shorter_distance, int *count, int n, int k);
int **processData(centroid_t *centroids, point_t *points, int *count, int n, int k);
int **createCluster(int **is_shorter_distance, int *count, int n, int k);

#endif