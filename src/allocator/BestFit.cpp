#include "BestFit.h"
#include <iostream>

BestFit::BestFit(size_t memory_size) : total(memory_size), next_id(1) {
    Block initial = {0, memory_size, true, -1, 0};
    blocks.push_back(initial);
}

int BestFit::findBest(size_t size) const {
    int bestIndex = -1;
    size_t bestSize = SIZE_MAX;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i].free && blocks[i].size >= size && blocks[i].size < bestSize) {
            bestIndex = i;
            bestSize = blocks[i].size;
        }
    }
    return bestIndex;
}

int BestFit::malloc(size_t size) {
    total_requests++;

    int idx = findBest(size);
    if (idx == -1) return -1;

    Block &block = blocks[idx];
    size_t remaining = block.size - size;
    block.free = false;
    block.size = size;
    block.block_id = next_id;
    block.requested = size;
    successful_allocs++;

    if (remaining > 0) {
        Block newBlock = {block.start + size, remaining, true, -1, 0};
        blocks.insert(blocks.begin() + idx + 1, newBlock);
    }

    return next_id++;
}

void BestFit::freeBlock(int id) {
    for (auto &block : blocks) {
        if (block.block_id == id && !block.free) {
            block.free = true;
            block.block_id = -1;
            block.requested = 0;
            coalesce();
            return;
        }
    }
}

void BestFit::coalesce() {
    for (size_t i = 0; i < blocks.size() - 1; i++) {
        if (blocks[i].free && blocks[i + 1].free) {
            blocks[i].size += blocks[i + 1].size;
            blocks.erase(blocks.begin() + i + 1);
            i--;
        }
    }
}

void BestFit::dump() const {
    for (const auto &block : blocks) {
        std::cout << "[" << block.start << " - "
                  << (block.start + block.size - 1) << "] ";
        std::cout << (block.free ? "FREE\n" : "USED (id=" + std::to_string(block.block_id) + ")\n");
    }
}

void BestFit::stats() const {
    size_t used=0, free=0, internal=0, biggestFree=0;
    for (const auto &b : blocks) {
        if (!b.free) {
            used += b.size;
            internal += (b.size - b.requested);
        } else {
            free += b.size;
            if (b.size > biggestFree) biggestFree = b.size;
        }
    }
    double util = used / double(used + free);
    double ext = free == 0 ? 0 : 1.0 - (biggestFree / double(free));
    double sr = total_requests == 0 ? 0.0 :
                successful_allocs / double(total_requests);

    std::cout << "\n--- Best Fit Stats ---\n";
    std::cout << "Used : " << used << "\nFree : " << free
              << "\nUtilization : " << util * 100
              << "%\nExternal Frag : " << ext * 100
              << "%\nSuccess Rate : " << sr * 100 << "%\n";
}
