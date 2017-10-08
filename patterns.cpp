//
// Created by egordm on 6-10-2017.
//

#include "patterns.h"


bool PatternBuilder::step(std::shared_ptr<osupp::HitObject> obj) {
    return obj != nullptr;
}

bool PatternBuilder::validate() {
    return true;
}

Pattern *PatternBuilder::build(BeatmapIterator &iterator) {
    unsigned int offset = 0;
    objects.clear();
    while (true) {
        auto obj = iterator.getHitObject(offset);
        if (!step(obj)) break;
        offset++;
    }
    if (objects.size() < min_objects()) return nullptr;
    if (!validate()) return nullptr;
    iterator.obj_cursor += offset;

    return instantiate();
}
