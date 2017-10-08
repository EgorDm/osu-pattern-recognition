//
// Created by egordm on 6-10-2017.
//

#include "patterns.h"
#include "math.h"


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

bool PolygramPatternBuilder::step(std::shared_ptr<osupp::HitObject> obj) {
    auto size = objects.size();
    if (!CircumCentredPatternBuilder::step(obj)) return false;
    if (size < 2) return true;

    // Check wether sides have same width
    auto w1 = obj->pos.distance(objects[objects.size() - 1]->pos);
    auto w2 = objects[objects.size() - 1]->pos.distance(objects[objects.size() - 2]->pos);

    if (fabsf(w1 - width) > width * 0.01f ||
        fabsf(w2 - width) > width * 0.01f) {
        return false;
    }

    objects.push_back(obj);
    return true;
}

bool PolygramPatternBuilder::validate() {
    bool valid = false;
    for (int k : math::polygram_alts(static_cast<unsigned int>(objects.size()))) {
        float target = math::polygram_angle(objects.size(), k);
        valid = true;

        for (auto i = 0; i < objects.size() - 2; i++) {
            float angl = math::raddeg(math::pangle(objects[i]->pos, objects[i + 1]->pos, objects[i + 2]->pos));
            if (fabsf(target - angl) > target * 0.2f) {
                valid = false;
                break;
            }
        }
        if (valid) break;
    }
    return valid;
}

Pattern *PolygramPatternBuilder::instantiate() {
    auto ret = new PolygramPattern();
    ret->time = objects[0]->time;
    ret->objects = objects;
    ret->point_count = static_cast<unsigned int>(objects.size());
    return reinterpret_cast<Pattern *>(ret);
}

bool ConvexPatternBuilder::step(std::shared_ptr<osupp::HitObject> obj) {
    auto size = objects.size();
    if (!CircumCentredPatternBuilder::step(obj)) return false;
    if (size < 2) return true;

    for (const auto &oi : objects) {
        if (oi->pos.distance(obj->pos) < width * 0.8) return false;
    }

    objects.push_back(obj);
    return true;
}

bool ConvexPatternBuilder::validate() {
    std::vector<osupp::Coordinate> points;
    for (const auto &oi : objects) points.push_back(oi->pos);
    return math::is_convex(points);
}

Pattern *ConvexPatternBuilder::instantiate() {
    auto ret = new PolygramPattern();
    ret->time = objects[0]->time;
    ret->objects = objects;
    ret->point_count = static_cast<unsigned int>(objects.size());
    return reinterpret_cast<Pattern *>(ret);
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

bool StreamPatternBuilder::step(std::shared_ptr<osupp::HitObject> obj) {
    if (obj == nullptr || obj->getType() != osupp::HitObject::HitObjectType::HitCircle) return false;
    if (objects.empty()) {
        objects.push_back(obj);
        return true;
    }

    auto s = objects.back()->pos.distance(obj->pos);
    auto t = obj->time - objects.back()->time;

    if(objects.size() > 1) {
        if (fabsf(spacing - s) > spacing * 0.2f) return false;
        if (fabsf(timestep - t) > timestep * 0.1f) return false;

        if (objects.size() >= 2) {
            auto angle = math::raddeg(math::pangle(obj->pos, objects[objects.size() - 1]->pos, objects[objects.size() - 2]->pos));
            if (angle <= 90) return false;
        }
    }

    spacing = s;
    timestep = t;
    if(spacing > max_spacing || timestep > max_time) return false;

    objects.push_back(obj);
    return true;
}

Pattern *StreamPatternBuilder::instantiate() {
    auto ret = new StreamPattern();
    ret->time = objects[0]->time;
    ret->objects = objects;
    ret->timestep = static_cast<unsigned int>(timestep);
    ret->spacing = spacing;
    return ret;
}
