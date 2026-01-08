#ifndef BLOCK_H
#define BLOCK_H

#include <cstddef>

struct Block {
    size_t start;        // starting address
    size_t size;         // allocated size
    size_t requested;    // requested size
    bool free;           // free or used
    int block_id;        // allocation id
};

#endif

