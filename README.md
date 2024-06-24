
# Clustering

This repository contains a K-means based clustering algorithm designed to handle two-dimensional points and centroids. The algorithm operates in a packet-oriented manner, allowing for dynamic addition of points and centroids.

## Description

The program begins by defining an initial number of points and centroids. If the initial number of points is less than the number of centroids, the program will wait until the counts are equal to start processing. After the initial clustering, the program continues to wait for more points to perform additional clustering operations.

## Usage Examples

### Constant Number of Points

The following GIF demonstrates the clustering process with a constant number of points:

<p align="center">
  <img src="https://user-images.githubusercontent.com/118558122/219137153-73b8f11d-c2aa-40ab-a2aa-b53f0864356b.gif" alt="Constant number of points clustering">
</p>

### Increasing Number of Points

The following GIF demonstrates the entire clustering process with an increasing number of points:

<p align="center">
  <img src="https://user-images.githubusercontent.com/118558122/219134302-e03d4c72-2a2d-4667-a496-fdc1c834d8d5.gif" alt="Increasing number of points clustering">
</p>
