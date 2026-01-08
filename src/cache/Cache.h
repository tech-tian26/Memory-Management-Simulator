#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstddef>
#include <string>
#include "CacheSet.h"

class Cache {
private:
    size_t cache_size;
    size_t block_size;
    int associativity;
    int num_sets;

    std::string policy;  // FIFO, LRU, LFU

    std::vector<CacheSet> sets;

    int hits = 0;
    int misses = 0;

    int findVictim(CacheSet &set);

public:
    Cache(size_t cacheSize, size_t blockSize,
          int assoc, std::string repl_policy);

    bool access(size_t address);
    void stats(const std::string &name) const;
};

#endif
