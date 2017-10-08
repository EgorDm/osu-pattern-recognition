//
// Created by egordm on 6-10-2017.
//

#ifndef OSU_PATTERN_PATTERNS_H
#define OSU_PATTERN_PATTERNS_H

#include "iterator.h"

class Pattern {
public:
    explicit Pattern() = default;

    virtual ~Pattern() {}

    std::vector<std::shared_ptr<osupp::HitObject>> objects;

    unsigned long time{};
};




#endif //OSU_PATTERN_PATTERNS_H