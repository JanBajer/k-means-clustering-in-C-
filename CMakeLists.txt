cmake_minimum_required(VERSION 3.21)
project(Jan_Bajer_KMeans_Clustering)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(KMEANS_SOURCES
        algorithm.cpp
        point.cpp)

add_executable(kmeans ${KMEANS_SOURCES} main.cpp)