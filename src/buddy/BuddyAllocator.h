#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H

#include "allocator/Allocator.h"
#include <map>
#include <vector>
#include "buddy/BuddyBlock.h"

class BuddyAllocator : public Allocator {
private:
    size_t total_size;
    size_t min_block;
    std::map<size_t, std::vector<BuddyBlock>> free_lists;
    int next_id = 1;

    size_t nextPowerOf2(size_t n);
    size_t buddyOf(size_t addr, size_t size);
    size_t allocateRaw(size_t request);  // internal allocation returning address
    void freeRaw(size_t addr, size_t size);
    void split(size_t size);

    std::map<int, BuddyBlock> allocated; // block_id -> block info

public:
    BuddyAllocator(size_t memory_size, size_t min_block_size = 32);

    int malloc(size_t size) override;         // return block_id
    void freeBlock(int block_id) override;    // free by id
    void dump() const override;
    void stats() const override;
};

#endif
