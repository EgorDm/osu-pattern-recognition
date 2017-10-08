//
// Created by egordm on 2-10-2017.
//

#include <iostream>
#include <limits>
#include "math.h"

using namespace utils;

namespace math {

    float pangle(osupp::Coordinate a, osupp::Coordinate b, osupp::Coordinate c) {
        auto diffa = (b - a);
        auto diffb = (b - c);

        auto dot = diffa.dot(diffb);
        auto cross = diffa.cross(diffb);

        return fabsf(atan2f(cross, dot));
    }

    osupp::Coordinate pcentroid(osupp::Coordinate c0, osupp::Coordinate c1, osupp::Coordinate c2) {
        return (c0 + c1 + c2) / 3.0;
    }


    //https://github.com/robu3/delaunay/blob/master/Triangle.java
    osupp::Coordinate pcircumcenter(osupp::Coordinate a, osupp::Coordinate b, osupp::Coordinate c) {
        auto midAB = midpoint(a, b), midBC = midpoint(b, c);
        auto slopeAB = -1 / slope(a, b), slopeBC = -1 / slope(b, c);

        auto bAB = midAB.y - slopeAB * midAB.x;
        auto bBC = midBC.y - slopeBC * midBC.x;

        auto slopeTot = slopeBC - slopeAB;
        if(slopeTot == 0) return {std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN()};
        float x = (bAB - bBC) / slopeTot;

        return {x, (slopeAB * x) + bAB};
    }

    osupp::Coordinate midpoint(osupp::Coordinate a, osupp::Coordinate b) {
        return {(a.x + b.x) / 2, (a.y + b.y) / 2};
    }

    float slope(osupp::Coordinate a, osupp::Coordinate b) {
        return {(b.y - a.y) / (b.x - a.x)};
    }

}

