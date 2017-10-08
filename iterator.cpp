//
// Created by egordm on 2-10-2017.
//

#include <iostream>
#include "iterator.h"

std::shared_ptr<osupp::HitObject> BeatmapIterator::getHitObject(int offset) {
    int select = obj_cursor + offset;
    if (select < 0 || select >= beatmap.hitobjects.size()) return nullptr;
    return beatmap.hitobjects[select];
}

std::shared_ptr<osupp::TimingPoint> BeatmapIterator::getTimingPoint(int offset) {
    int select = tp_cursor + offset;
    if (select < 0 || select >= beatmap.timingpoints.size()) return nullptr;
    return beatmap.timingpoints[select];
}

BeatmapIterator::BeatmapIterator(const osupp::Beatmap &beatmap) : beatmap(beatmap) {
    obj_cursor = 0;
    tp_cursor = 0;
}

void BeatmapIterator::step() {
    if (ended()) return;
    obj_cursor += 1;

    auto obj = getHitObject(0);
    while (tp_cursor + 1 < beatmap.timingpoints.size() && beatmap.timingpoints[tp_cursor + 1]->offset < obj->time)
        ++tp_cursor;
}

bool BeatmapIterator::ended() {
    return obj_cursor >= beatmap.hitobjects.size();
}
