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
bool CircumCentredPatternBuilder::step(std::shared_ptr<osupp::HitObject> obj) {
    if (obj == nullptr || obj->getType() != osupp::HitObject::HitObjectType::HitCircle) return false;
    for (const auto &oi : objects) if (oi->pos == obj->pos) return false;

    if (objects.size() < 2) {
        objects.push_back(obj);
        return true;
    }

    auto tmp_centre = math::pcircumcenter(obj->pos, objects[objects.size() - 1]->pos, objects[objects.size() - 2]->pos);
    if (tmp_centre.x != tmp_centre.x || tmp_centre.y != tmp_centre.y) return false;

    if (objects.size() == 2) {
        centre = tmp_centre;
        width = obj->pos.distance(objects[objects.size() - 1]->pos);
    } else if (centre.distance(tmp_centre) > width * 0.01f) return false;

    return true;
}
