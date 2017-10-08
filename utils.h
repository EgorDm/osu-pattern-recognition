//
// Created by egordm on 2-10-2017.
//

#ifndef OSU_PATTERN_UTILS_H
#define OSU_PATTERN_UTILS_H

#include <memory>

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

namespace utils {
    template<typename Base, typename T>
    inline bool instanceof(const T *) {
        return std::is_base_of<Base, T>::value;
    }

    template<typename Base, typename T>
    inline bool ptr_instanceof(const T &ptr) {
        if (auto temp = std::dynamic_pointer_cast<Base>(ptr)) return true;
        return false;
    }

    int overflow(int x, int max);
}

#endif //OSU_PATTERN_UTILS_H
