//
// Created by bajerjan on 24.12.2021.
//

#include "point.h"

//calculating distance between 2 points
double point::distance(const point &p1, const point &p2){
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
