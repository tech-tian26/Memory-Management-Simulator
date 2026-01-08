#ifndef CACHE_LINE_H
#define CACHE_LINE_H

#include <cstddef>

struct CacheLine {
    bool valid = false;
    size_t tag = 0;

    // For replacement policies
    int age = 0;       // FIFO / LRU
    int frequency = 0; // LFU
};

#endif
