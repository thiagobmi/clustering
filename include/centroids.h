#ifndef CENTROIDS_H
#define CENTROIDS_H 1

#include "points.h"
#include "arrays.h"

struct centroids
{
    float X;
    float Y;
};
typedef struct centroids centroid_t;

int checkMemCentroid(centroid_t *centro);
centroid_t *newCentroidArr(int k);
centroid_t *randomizeCentroids(point_t *points, int n, int k);

#endif