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

class ConvexPattern : public Pattern {
public:
    unsigned int point_count = 0;
};


class PolygramPattern : public ConvexPattern {
public:
};

class StreamPattern : public Pattern {
public:
    inline float get_bpm() {
        return 60000 / timestep / 4;
    }

    float spacing = 0;
    unsigned int timestep = 0;
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

class CircumCentredPatternBuilder : public PatternBuilder {
protected:
    bool step(std::shared_ptr<osupp::HitObject> obj) override;

    osupp::Coordinate centre;
    float width{};
};

class PolygramPatternBuilder : public CircumCentredPatternBuilder {
public:

protected:
    bool step(std::shared_ptr<osupp::HitObject> obj) override;

    bool validate() override;

    Pattern *instantiate() override;

    inline unsigned int min_objects() override {
        return 5;
    };
};

class ConvexPatternBuilder : public CircumCentredPatternBuilder {
public:

protected:
    bool step(std::shared_ptr<osupp::HitObject> obj) override;

    bool validate() override;

    Pattern *instantiate() override;

    inline unsigned int min_objects() override {
        return 4;
    };
};

class StreamPatternBuilder : public PatternBuilder {
protected:
    bool step(std::shared_ptr<osupp::HitObject> obj) override;

    Pattern *instantiate() override;

    inline unsigned int min_objects() override {
        return 4;
    };

    float spacing = 0;
    float timestep = 0;

    const float max_spacing = 60;
    const float max_time = 300;
};



#endif //OSU_PATTERN_PATTERNS_H