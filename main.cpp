#include "algorithm.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <chrono>
#include <string>

#include <cmath>
#include <thread>

template <typename TimePoint>
std::chrono::milliseconds toMs(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

void printHelp() {
    std::clog << "Usage example:\n"
              << "-input FILENAME - filename to read points from (required)\n"
              << "-clusters K - number of clusters (required)\n"
              << "-output FILENAME - filename to write points with cluster ID´s (required)\n"
              << "-centroids - filename to write centroids (optional, default is centroids.txt) \n"
              << "-threads - how many threads will be used (optional, default is 1) \n"
              << "-clusters 2 -input sample_1.txt -output result.txt -centroids centroids.txt\n";
}


void saveToFile(algorithm kmeans, const std::string& output,const std::string& outputCentroids, int k){
    //write centroids to file
    std::ofstream centroidStream(outputCentroids);
    if(!outputCentroids.empty()){
        if (centroidStream.good()) {
            for (size_t a = 0; a < k; ++a)
                centroidStream << kmeans.centroids[a].x << " " << kmeans.centroids[a].y << std::endl;
        } else{
            std::clog << "Cannot open file '" << outputCentroids << "' for writing points with cluster IDs!\n";
        }

    }
    else{ //if centroid output was not specified
        std::ofstream centroid("centroids.txt");
        if (centroid.good()) {
            for (size_t a = 0; a < k; ++a)
                centroid << kmeans.centroids[a].x << " " << kmeans.centroids[a].y << std::endl;
        } else{
            std::clog << "Cannot open file '" << outputCentroids << "' for writing points with cluster IDs!\n";
        }
    }

    //write clusters to file
    std::ofstream outputStream(output);
    if (outputStream.good()) {
        for (auto & classification : kmeans.classifications)
            outputStream << classification.x << " " << classification.y << " " << classification.clusterId << std::endl;
    } else{
        std::clog << "Cannot open file '" << output << "' for writing points with cluster IDs!\n";
    }


}

int main(int argc, char const *argv[]) {
    int k = 0;
    int threads = 1;
    std::string inputFile;
    std::string outputFile;
    std::string outputCentroids;

    try{
        for (int i = 1; i < argc; i++)
        {
            if (!strcmp(argv[i], "--help")){
                printHelp();
                return 0;
            }
            if (!strcmp(argv[i], "--h")){
                printHelp();
                return 0;
            }
            if (!strcmp(argv[i], "-threads")){
                if (i + 1 >= argc) {
                    throw std::runtime_error("No multi-thread argument. Try --help");
                }
                std::size_t endpos = 0;
                threads = std::stoi(argv[++i], &endpos);
                if(threads<=0){
                    throw std::runtime_error("Number of threads has to be a positive number. Try --help");
                }
            }
            else if (!strcmp(argv[i], "-clusters")) {
                if (i + 1 >= argc) {
                    throw std::runtime_error("Number argument is missing. Try --help");
                }
                std::size_t endpos = 0;
                k = std::stoi(argv[++i], &endpos);
                if(k<=0){
                    throw std::runtime_error("Number of clusters has to be a positive number. Try --help");
                }

            }
            else if (!strcmp(argv[i], "-output")) {
                if (i + 1 >= argc) {
                    throw std::runtime_error("Output argument is missing. Try --help");
                }
                outputFile = argv[++i];
            }
            else if (!strcmp(argv[i], "-input")){
                if (i + 1 >= argc){
                    throw std::runtime_error("No input path argument. Try --help");
                }
                inputFile = argv[++i];
            }
            else if (!strcmp(argv[i], "-centroids")){
                if (i + 1 >= argc) {
                    throw std::runtime_error("No output-Centroids argument. Try --help");
                }
                outputCentroids = argv[++i];
            }
            else {
                throw std::runtime_error("Invalid command. Try --help");
            }
        }

        if (argc > 1 && k > 0 && !inputFile.empty() && !outputFile.empty()){

            algorithm kmeans;

            auto start = std::chrono::high_resolution_clock::now(); //start
            kmeans.kmeans(k, kmeans.readDataFromFile(inputFile), threads); //algorithm
            auto end = std::chrono::high_resolution_clock::now(); //end

            saveToFile(kmeans,outputFile,outputCentroids,k); //save results to output and outputCentroids

            //Print data to user
            std::cout << "Time: " << toMs(end-start).count() << " ms to finish" << std::endl;
            std::cout << "Number of clusters: " << kmeans.centroids.size() << std::endl;
            std::cout << "Iterations: " << kmeans.counter << std::endl;
            std::cout << "Threads: " << threads << std::endl;
            std::cout << "Input file name: "; std::cout << inputFile << std::endl;
            std::cout << "Output file name: " << outputFile << std::endl;

            if(outputCentroids.empty()){
                std::cout << "Centroids file name: " << "centroids.txt" << " ";
            }
            else{
                std::cout << "Centroids file name: " << outputCentroids << " ";
            }

        }
        else{
            throw std::runtime_error("Missing commands. (-clusters,-input and -output is required). You can use --help.");
        }
    }
    catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "Invalid number. You can use --help" << std::endl;
    }
}
