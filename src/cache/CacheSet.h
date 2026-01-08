#ifndef CACHE_SET_H
#define CACHE_SET_H

#include <vector>
#include "CacheLine.h"

class CacheSet {
public:
    std::vector<CacheLine> lines;

    CacheSet(int associativity) {
        lines.resize(associativity);
    }
};

#endif
