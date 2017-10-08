//
// Created by egordm on 2-10-2017.
//

#include <beatmap_file.h>
#include "osu_extensions.h"
#include "utils.h"

using namespace osupp::reading;

namespace osupp {
    Beatmap BeatmapReader::read(const std::string &path) {
        auto ret = Beatmap();
        auto file = BeatmapFile(path, BeatmapFile::Mode::Read);

        auto meta = file.readAttributeSection("[Metadata]");
        parseAttrib(meta, "Title", ret.title);
        parseAttrib(meta, "Artist", ret.artist);
        parseAttrib(meta, "Creator", ret.creator);
        parseAttrib(meta, "BeatmapID", ret.id);
        parseAttrib(meta, "BeatmapSetID", ret.set_id);

        auto diff = file.readAttributeSection("[Difficulty]");
        parseAttrib(diff, "SliderMultiplier", ret.sliderMultiplayer);
        parseAttrib(diff, "SliderTickRate", ret.sliderTickRate);

        std::shared_ptr<TimingPoint> ktp = nullptr;
        std::shared_ptr<TimingPoint> tp = nullptr;
        for (const auto &line : file.readSection("[TimingPoints]")) {
            parse(line, tp);
            if (utils::ptr_instanceof<KeyTimingPoint>(tp)) {
                ktp = std::static_pointer_cast<InheritedTimingPoint>(tp);
            } else {
                if (ktp == nullptr) throw std::runtime_error("Beatmap starts with an inherited timing point.");
                std::static_pointer_cast<InheritedTimingPoint>(tp)->parent = std::static_pointer_cast<KeyTimingPoint>(
                        ktp);
            }
            ret.timingpoints.push_back(tp);
        }

        std::shared_ptr<HitObject> obj = nullptr;
        for (const auto &line : file.readSection("[HitObjects]")) {
            try {
                parse(line, obj);
                if (obj != nullptr) ret.hitobjects.push_back(obj);
            } catch (...) {}
        }

        return ret;
    }
}

