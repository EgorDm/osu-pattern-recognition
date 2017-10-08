#include <iostream>
#include <models.h>
#include "math.h"
#include "osu_extensions.h"
#include "iterator.h"
#include "classifiers.h"
#include "patterns.h"

using namespace osupp;

int main() {
    auto bm = osupp::BeatmapReader::read(samplePath);
    auto iter = BeatmapIterator(bm);

    //auto square = new SquarePattern();
    //auto star = new PolygramPattern();
    //auto stream = new StreamPattern();
    //auto polyBuilder = new PolygramPatternBuilder();
    //auto convexBuilder = new ConvexPatternBuilder();
    auto streamBuilder = new StreamPatternBuilder();
    //auto square = new ConvexPatternOld(4);
    for(; !iter.ended(); ) {
        //if(square->classify(iter)) std::cout << "Found square" << iter.getHitObject(0)->time << std::endl;
        //if(star->classify(iter)) std::cout << "Found star" << iter.getHitObject(0)->time << std::endl;
        //auto pattern = polyBuilder->build(iter);
        //auto pattern = convexBuilder->build(iter);
        auto pattern = streamBuilder->build(iter);
        if(pattern == nullptr) {
            iter.step();
            continue;
        }
        std::cout << "Found pattern" << pattern->time << " Count:" << pattern->objects.size() << std::endl;
        std::cout << "BPM: " << dynamic_cast<StreamPattern*>(pattern)->get_bpm() << std::endl;
        for(const auto &o : pattern->objects) {
            std::cout << o->pos << std::endl;
        }
        delete pattern;
    }

//    osupp::Coordinate coords[] = {Coordinate(256, 32), Coordinate(104, 88), Coordinate(160, 240), Coordinate(312, 192)};
//    std::cout << "and " << "Convex? " << (bool)math::is_convex(coords, sizeof(coords) / sizeof(coords[0])) << std::endl;

//    osupp::Coordinate cc = math::pcircumcenter(Coordinate(0, 0), Coordinate(0, 60), Coordinate(40, 100));
//    std::cout << cc.x << "and " << cc.y << std::endl;
    return 0;
}