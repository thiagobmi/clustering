#include <stdlib.h>
#include "../include/points.h"
#include "../include/arrays.h"

int checkMemPointArr(point_t *points)
{
    if (points == NULL)
    {
        printf("ERRO point arr\n");
        exit(0);
        return 0;
    }
}

point_t *newPointArr(int n)
{
    point_t *points = (point_t *)calloc(n,sizeof(point_t));
    checkMemPointArr(points);
    return points;
}

point_t *reallocPointArr(point_t *points, int current_size, int n)
{
    points = (point_t *)realloc(points, (sizeof(point_t) * n));
    checkMemPointArr(points);

    for (int i = current_size; i < n; i++)
    {
        points[i].X = 0;
        points[i].Y = 0;
    }

    return points;
}

point_t *generateRandomPoints(point_t *points, int n, int n_sum)
{

    srand(time(NULL));
    for (n; n < n_sum; n++)
    {
        points[n].X = -2000 + rand() % 5000;
        points[n].Y = -2000 + rand() % 5000;
    }

    return points;
}

point_t *readPoints(point_t *points, int n, int n_sum)
{

    for (n; n < n_sum; n++)
        scanf("%d %d", &points[n].X, &points[n].Y);

    return points;
}

point_t *addPointsToArray(point_t *points, int n, int n_sum, int flag)
{
    if (flag == 0)
        return generateRandomPoints(points, n, n_sum);
    else
        return readPoints(points, n, n_sum);
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

point_t *addPoints(point_t *points, int n, int n_plus, int flag)
{
    unsigned int n_sum = n + n_plus;

    points = (point_t *)realloc(points, sizeof(point_t) * ((n_sum)));
    checkMemPointArr(points);

    addPointsToArray(points, n, n_sum, flag);

    return points;
}