//
// Created by egordm on 2-10-2017.
//

#ifndef OSU_PATTERN_OSU_EXTENSIONS_H
#define OSU_PATTERN_OSU_EXTENSIONS_H

#include <models.h>

namespace osupp {
    class BeatmapReader {
    public:
        static Beatmap read(const std::string &path);
    };
}


#endif //OSU_PATTERN_OSU_EXTENSIONS_H
