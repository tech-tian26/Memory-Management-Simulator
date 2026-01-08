#include "FirstFit.h"
#include <iostream>

FirstFit::FirstFit(size_t memory_size) : total(memory_size), next_id(1) {
    Block initial;
    initial.start = 0;
    initial.size = memory_size;
    initial.free = true;
    initial.block_id = -1;
    initial.requested = 0;
    blocks.push_back(initial);
}

int FirstFit::malloc(size_t size) {
    total_requests++;

    for (auto &block : blocks) {
        if (block.free && block.size >= size) {
            size_t remaining = block.size - size;
            block.free = false;
            block.size = size;
            block.block_id = next_id;
            block.requested = size;
            successful_allocs++;

            if (remaining > 0) {
                Block newBlock;
                newBlock.start = block.start + size;
                newBlock.size = remaining;
                newBlock.free = true;
                newBlock.block_id = -1;
                newBlock.requested = 0;
                blocks.insert(blocks.begin() + (&block - &blocks[0]) + 1, newBlock);
            }

            return next_id++;
        }
    }
    return -1;
}

void FirstFit::freeBlock(int block_id) {
    for (auto &block : blocks) {
        if (block.block_id == block_id && !block.free) {
            block.free = true;
            block.block_id = -1;
            block.requested = 0;
            coalesce();
            return;
        }
    }
}

void FirstFit::coalesce() {
    for (size_t i = 0; i < blocks.size() - 1; i++) {
        if (blocks[i].free && blocks[i + 1].free) {
            blocks[i].size += blocks[i + 1].size;
            blocks.erase(blocks.begin() + i + 1);
            i--;
        }
    }
}

void FirstFit::dump() const {
    for (const auto &block : blocks) {
        std::cout << "[" << block.start << " - "
                  << (block.start + block.size - 1) << "] ";
        if (block.free)
            std::cout << "FREE\n";
        else
            std::cout << "USED (id=" << block.block_id << ")\n";
    }
}

void FirstFit::stats() const {
    size_t used = 0, free = 0, internal_frag = 0;
    size_t largest_free = 0;

    for (const auto &block : blocks) {
        if (block.free) {
            free += block.size;
            if (block.size > largest_free)
                largest_free = block.size;
        } else {
            used += block.size;
            internal_frag += (block.size - block.requested);
        }
    }

    double util = (double)used / (used + free);
    double external_frag = (free == 0) ? 0.0
        : 1.0 - ((double)largest_free / free);
    double success_rate = (total_requests == 0) ? 0.0 :
        (double)successful_allocs / total_requests;

    std::cout << "\n--- First Fit Statistics ---\n";
    std::cout << "Used Memory    : " << used << "\n";
    std::cout << "Free Memory    : " << free << "\n";
    std::cout << "Utilization    : " << util * 100 << " %\n";
    std::cout << "Internal Frag  : " << internal_frag << "\n";
    std::cout << "External Frag  : " << external_frag * 100 << " %\n";
    std::cout << "Success Rate   : " << success_rate * 100 << " %\n";
}
