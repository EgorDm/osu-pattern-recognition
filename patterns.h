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

class PatternBuilder { //TODO: explode && use modular checks(add classifiers)
public:
    explicit PatternBuilder() = default;

    virtual Pattern *build(BeatmapIterator &iterator);
protected:
    virtual bool step(std::shared_ptr<osupp::HitObject> obj);

    virtual bool validate();

    virtual Pattern *instantiate() = 0;

    virtual unsigned int min_objects() = 0;

    std::vector<std::shared_ptr<osupp::HitObject>> objects;
};



#endif //OSU_PATTERN_PATTERNS_H