#ifndef POINTS_H
#define POINTS_H 1

#include<time.h>

struct ponto
{
    int *X;
    int *Y;
};

typedef struct ponto point_t;
int checkMemPointArr(point_t *points);
point_t *newPointArr(int n);
point_t *reallocPointArr(point_t *points, int current_size, int n);
point_t *generateRandomPoints(point_t *points, int n, int n_sum);
point_t *readPoints(point_t *points, int n, int n_sum);
point_t *addPointsToArray(point_t *points, int n, int n_sum, int flag);
point_t *receiveAdditionalPoints(int n, int k, int flag);
point_t *addPoints(point_t *points, int n, int n_plus, int flag);

#endif