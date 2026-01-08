#include "Cache.h"
#include <iostream>
#include <climits>

Cache::Cache(size_t cSize, size_t bSize,
             int assoc, std::string repl)
    : cache_size(cSize), block_size(bSize),
      associativity(assoc), policy(repl) {

    num_sets = cache_size / (block_size * associativity);
    for (int i = 0; i < num_sets; i++)
        sets.emplace_back(associativity);
}

bool Cache::access(size_t address) {
    size_t block_addr = address / block_size;
    size_t set_index = block_addr % num_sets;
    size_t tag = block_addr / num_sets;

    CacheSet &set = sets[set_index];

    // HIT check
    for (auto &line : set.lines) {
        if (line.valid && line.tag == tag) {
            hits++;
            line.frequency++;
            line.age = 0;
            return true;
        }
    }

    // MISS
    misses++;

    int victim = findVictim(set);
    set.lines[victim].valid = true;
    set.lines[victim].tag = tag;
    set.lines[victim].frequency = 1;
    set.lines[victim].age = 0;

    return false;
}

int Cache::findVictim(CacheSet &set) {
    int victim = 0;

    if (policy == "FIFO" || policy == "LRU") {
        int max_age = -1;
        for (int i = 0; i < associativity; i++) {
            if (!set.lines[i].valid)
                return i;
            if (set.lines[i].age > max_age) {
                max_age = set.lines[i].age;
                victim = i;
            }
        }
    }
    else if (policy == "LFU") {
        int min_freq = INT_MAX;
        for (int i = 0; i < associativity; i++) {
            if (!set.lines[i].valid)
                return i;
            if (set.lines[i].frequency < min_freq) {
                min_freq = set.lines[i].frequency;
                victim = i;
            }
        }
    }

    return victim;
}

void Cache::stats(const std::string &name) const {
    int total = hits + misses;
    double hit_ratio = (total == 0) ? 0.0 : (double)hits / total;

    std::cout << "\n=== " << name << " Cache Stats ===\n";
    std::cout << "Hits      : " << hits << "\n";
    std::cout << "Misses    : " << misses << "\n";
    std::cout << "Hit Ratio : " << hit_ratio * 100 << " %\n";
}
