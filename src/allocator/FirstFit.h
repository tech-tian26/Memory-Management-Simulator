#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include "Allocator.h"
#include <vector>

class FirstFit : public Allocator {
private:
    struct Block {
        size_t start;
        size_t size;
        bool free;
        int block_id;
        size_t requested;
    };

    size_t total;
    std::vector<Block> blocks;
    int next_id;
    mutable size_t total_requests = 0;
    mutable size_t successful_allocs = 0;

    void coalesce();

public:
    FirstFit(size_t memory_size);
    int malloc(size_t size) override;
    void freeBlock(int block_id) override;
    void dump() const override;
    void stats() const override;
};

#endif
