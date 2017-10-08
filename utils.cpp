//
// Created by egordm on 2-10-2017.
//

#include "utils.h"

namespace utils {
    int overflow(int x, int max) {
        if(x >= max) return overflow(x - max, max);
        return x;
    }
}