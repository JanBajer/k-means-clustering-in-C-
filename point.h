//
// Created by bajerjan on 24.12.2021.
//

#ifndef JAN_BAJER_KMEANS_CLUSTERING_POINT_H
#define JAN_BAJER_KMEANS_CLUSTERING_POINT_H


#pragma once

class point
{
public:
    point(double x, double y) : x(x), y(y), clusterId(-1){};

    double x = 0; //coord x
    double y = 0; //coord y
    int clusterId = -1; //assigning point do centroid with id

    //distance between 2 points
    static double distance(const point &p1, const point &p2);
};


#endif //JAN_BAJER_KMEANS_CLUSTERING_POINT_H
