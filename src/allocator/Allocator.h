#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>

class Allocator {
public:
    virtual ~Allocator() {}

    // MUST be virtual, otherwise override errors come
    virtual int malloc(size_t size) = 0;
    virtual void freeBlock(int id) = 0;
    virtual void dump() const = 0;
    virtual void stats() const = 0;
};

#endif

