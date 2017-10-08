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
}

