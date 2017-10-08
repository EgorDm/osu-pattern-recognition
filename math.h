//
// Created by egordm on 2-10-2017.
//

#ifndef OSU_PATTERN_MATH_H
#define OSU_PATTERN_MATH_H


#include <maths.h>
#include <math.h>

namespace math {
    float pangle(osupp::Coordinate c0, osupp::Coordinate c1, osupp::Coordinate c2);

    osupp::Coordinate pcentroid(osupp::Coordinate c0, osupp::Coordinate c1, osupp::Coordinate c2);

    inline float raddeg(float rad) {
        return static_cast<float>(rad * 180 / M_PI);
    }

    inline float degrad(float deg) {
        return static_cast<float>(deg / 180 * M_PI);
    }

    bool is_convex(std::vector<osupp::Coordinate> points);

    osupp::Coordinate pcircumcenter(osupp::Coordinate a, osupp::Coordinate b, osupp::Coordinate c);

    osupp::Coordinate midpoint(osupp::Coordinate a, osupp::Coordinate b);

    float slope(osupp::Coordinate a, osupp::Coordinate b);

    float polygram_angle(unsigned int n, unsigned int k);

    std::vector<int> polygram_alts(unsigned int n);
}

#endif //OSU_PATTERN_MATH_H
