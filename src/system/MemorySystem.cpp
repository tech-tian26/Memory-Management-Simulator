#include "MemorySystem.h"
#include <iostream>

MemorySystem::MemorySystem()
    : vm(2048, 1024, 64, "FIFO"),
      L1(64, 16, 2, "LRU"),
      L2(256, 16, 4, "FIFO"),
      allocator(nullptr)
{}

void MemorySystem::setAllocator(Allocator* alloc) {
    allocator = alloc;
}

void MemorySystem::access(int virtualAddress) {
    int physical = vm.access(virtualAddress);
    bool hitL1 = L1.access(physical);
    if (!hitL1) {
        bool hitL2 = L2.access(physical);
        if (!hitL2) {
            // fallback to main memory – no allocator allocation here
        }
    }
}

void MemorySystem::stats() const {
    vm.stats();
    L1.stats("L1");
    L2.stats("L2");

    if (allocator)
        allocator->stats();
    else
        std::cout << "No allocator set.\n";
}
