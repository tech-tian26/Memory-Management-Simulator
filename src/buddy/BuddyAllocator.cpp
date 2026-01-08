#include "buddy/BuddyAllocator.h"
#include "buddy/BuddyBlock.h"
#include <iostream>
#include <cmath>

BuddyAllocator::BuddyAllocator(size_t memory_size, size_t min_block_size)
    : total_size(memory_size), min_block(min_block_size) {
    free_lists[total_size].push_back({0, total_size});
}

size_t BuddyAllocator::nextPowerOf2(size_t n) {
    size_t p = 1;
    while (p < n) p <<= 1;
    return p;
}

size_t BuddyAllocator::buddyOf(size_t addr, size_t size) {
    return addr ^ size;
}

void BuddyAllocator::split(size_t size) {
    if (free_lists[size].empty()) {
        split(size * 2);
        BuddyBlock block = free_lists[size * 2].back();
        free_lists[size * 2].pop_back();
        free_lists[size].push_back({block.address, size});
        free_lists[size].push_back({block.address + size, size});
    }
}

size_t BuddyAllocator::allocateRaw(size_t req) {
    size_t block_size = nextPowerOf2(req);
    if (block_size < min_block) block_size = min_block;
    if (block_size > total_size) return SIZE_MAX;

    if (free_lists[block_size].empty()) split(block_size);
    if (free_lists[block_size].empty()) return SIZE_MAX;

    BuddyBlock blk = free_lists[block_size].back();
    free_lists[block_size].pop_back();
    return blk.address;
}

int BuddyAllocator::malloc(size_t size) {
    size_t addr = allocateRaw(size);
    if (addr == SIZE_MAX) return -1;

    int id = next_id++;
    allocated[id] = {addr, nextPowerOf2(size)};
    return id;
}

void BuddyAllocator::freeBlock(int id) {
    if (!allocated.count(id)) return;

    BuddyBlock blk = allocated[id];
    allocated.erase(id);
    freeRaw(blk.address, blk.size);
}

void BuddyAllocator::freeRaw(size_t addr, size_t size) {
    size_t buddy = buddyOf(addr, size);

    auto &vec = free_lists[size];
    // coalesce buddy block
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i].address == buddy) {
            vec.erase(vec.begin() + i);
            size_t newAddr = (addr < buddy ? addr : buddy);
            freeRaw(newAddr, size * 2);
            return;
        }
    }
    free_lists[size].push_back({addr, size});
}

void BuddyAllocator::dump() const {
    std::cout << "\n--- Buddy Allocator Dump ---\n";
    std::cout << "Allocated blocks:\n";
    for (auto &p : allocated)
        std::cout << "id=" << p.first << " addr=" << p.second.address
                  << " size=" << p.second.size << "\n";

    std::cout << "\nFree lists:\n";
    for (auto &p : free_lists) {
        std::cout << p.first << ": ";
        for (auto &blk : p.second)
            std::cout << "[" << blk.address << "," << blk.size << "] ";
        std::cout << "\n";
    }
}

void BuddyAllocator::stats() const {
    size_t used = 0, free = 0;
    for (auto &p : allocated) used += p.second.size;
    for (auto &p : free_lists)
        for (auto &b : p.second)
            free += b.size;

    std::cout << "\n--- Buddy Stats ---\n";
    std::cout << "Used : " << used << "\nFree : " << free
              << "\nUtilization : "
              << (used + free == 0 ? 0 : (used * 100.0 / (used + free)))
              << "%\n";
}
