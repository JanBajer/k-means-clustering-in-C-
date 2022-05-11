//
// Created by bajerjan on 23.12.2021.
//

#ifndef JAN_BAJER_KMEANS_CLUSTERING_ALGORITHM_H
#define JAN_BAJER_KMEANS_CLUSTERING_ALGORITHM_H

#pragma once
#include "point.h"
#include <vector>
#include <string>
class algorithm
{
public:

    void kmeans(int k, std::vector<point> data, int threads);
    static void readOneLine(std::vector<point> &data, const std::string& line);
    static std::vector<point> readDataFromFile(const std::string& fileName);

    std::vector<point> classifications;
    std::vector<point> centroids;
    int counter = 0;
private:
    static const int maxIteration = 100;
};


#endif //JAN_BAJER_KMEANS_CLUSTERING_ALGORITHM_H
