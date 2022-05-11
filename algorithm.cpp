//
// Created by bajerjan on 23.12.2021.
//

#include "algorithm.h"
#include <iostream>
#include <fstream>

//function to check 1 line, if numbers are good, we add them to our "data list",
//which we use later in algorithm
void algorithm::readOneLine(std::vector<point> &data, const std::string &line) {
    std::string num;
    std::vector<double> point;
    for (const char &c : line) {
        if (c == 45 || c == 46 || (c >= 48 && c <= 57)) {
            num += c;
        }
        else if (!num.empty()) {
            point.push_back(std::stod(num));
            num = "";
        }
    }
    if (!num.empty()) {
        point.push_back(std::stod(num));
    }
    if (point.size() != 2) {
        throw std::runtime_error("Data are invalid!");
    }

    data.emplace_back(point[0], point[1]);
}

//function to read datas from file
std::vector<point> algorithm::readDataFromFile(const std::string &fileName) {
    std::vector<point> data;
    std::ifstream file;
    std::string line;

    file.open(fileName);
    if (file.is_open()) {
        //while there are datas on line, we use our function readOneLine
        while (std::getline(file, line)) {
            readOneLine(data, line);
        }
        file.close();
        return data;
    }
    else{
        throw std::runtime_error("File not found!");
    }
}

void algorithm::kmeans(int k, std::vector<point> data, int num_threads){

    // initialize centroids with first k points of data
    for (int i = 0; i < k; i++)
        centroids.push_back(data[i]);

    //repeat until convergence or until the end of a fixed number of iterations
    for (int i = 0; i < maxIteration; i++) {

        counter = counter+1; //counter how many iterations were needed

        // For each data point find the nearest centroid and assign the point to that cluster
        for (auto & j : data) {
            auto min_distance = -1;
            for (int c = 0; c < k; c++) {
                double distance = point::distance(j,centroids[c]);
                if (min_distance < 0 || distance < min_distance){
                    j.clusterId= c;
                    min_distance = distance;
                }
            }
        }

        // calculate the mean position for centroids
        std::vector<int> clusterIdCentroidsCounter;
        std::vector<point> prevCentroids = centroids;

        //null centroids so I can calculate mean (need zeros on coords)
        for (int c = 0; c < k; c++){
            clusterIdCentroidsCounter.push_back(0);
            centroids[c].x = 0;
            centroids[c].y = 0;
        }

        //we sum all x and y of points assigned to that cluster
        for (const point &p : data){
            clusterIdCentroidsCounter[p.clusterId] += 1;
            centroids[p.clusterId].x += p.x;
            centroids[p.clusterId].y += p.y;
        }

        //we divide with points assigned to that cluster and calculate mean of new centroids
        for (int c = 0; c < k; c++){
            centroids[c].x = centroids[c].x / clusterIdCentroidsCounter[c];
            centroids[c].y = centroids[c].y / clusterIdCentroidsCounter[c];
        }

        // Check if centroids are moving (converging), if yes we repeat loop, otherwise algorithm ends.
        int move = 0;
        for (int c = 0; c < k; c++){
            //we compare new centroids with centroids from previous iteration
            if ((prevCentroids[c].x != centroids[c].x) and (prevCentroids[c].y != centroids[c].y)){
                move = 1;
                break;
            }
        }
        if (move == 0)
            break;
    }

    this->classifications = data;
}