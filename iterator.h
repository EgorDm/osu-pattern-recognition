//
// Created by egordm on 2-10-2017.
//

#ifndef OSU_PATTERN_ITERATOR_H
#define OSU_PATTERN_ITERATOR_H


#include <models.h>

class BeatmapIterator {
public:
    BeatmapIterator(const osupp::Beatmap &beatmap);

    osupp::Beatmap beatmap;

    std::shared_ptr<osupp::HitObject> getHitObject(int offset);

    std::shared_ptr<osupp::TimingPoint> getTimingPoint(int offset);

    void step();

    bool ended();

    int obj_cursor;
    int tp_cursor;
private:

};


#endif //OSU_PATTERN_ITERATOR_H
