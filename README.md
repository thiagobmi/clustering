# clustering_algorithms
This is a H-means based clustering algorithm. n is the number of two-dimensional points and k is the number of centroids.

This program works as a packet-oriented clustering algorithm. A initial number of points and centroids can be defined in the start of the execution. If the initial number is higher than the number of centroids, the program will wait until the number of centroids and points is at least equal to start processing.

After finishing the initial clustering, the program will be awaiting for more points to start clustering again.
The points coordinates must be writen in the input as:

```bash
  n x1 y1 x2 y2 x3 y3 ... xn yn
```

With n being the number of points to be added to the next clustering.

![grafico](https://user-images.githubusercontent.com/118558122/219134302-e03d4c72-2a2d-4667-a496-fdc1c834d8d5.gif)

![gif2](https://user-images.githubusercontent.com/118558122/219137153-73b8f11d-c2aa-40ab-a2aa-b53f0864356b.gif)
