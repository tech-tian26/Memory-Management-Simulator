#ifndef MEMORY_SYSTEM_H
#define MEMORY_SYSTEM_H

#include "vm/VirtualMemory.h"
#include "cache/Cache.h"
#include "allocator/Allocator.h"

class MemorySystem {
private:
    VirtualMemory vm;
    Cache L1;
    Cache L2;

    Allocator* allocator;  // ← injection pointer

public:
    MemorySystem();
    void setAllocator(Allocator* alloc);

    void access(int virtualAddress);
    void stats() const;
};

#endif
