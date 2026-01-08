#ifndef BUDDY_BLOCK_H
#define BUDDY_BLOCK_H

#include <cstddef>

struct BuddyBlock {
    size_t address;
    size_t size;
};

#endif
