#include "PhysicalMemory.h"
#include <iostream>

PhysicalMemory::PhysicalMemory(size_t size)
    : total_size(size), memory(size, 0) {
}

size_t PhysicalMemory::getSize() const {
    return total_size;
}

void PhysicalMemory::dump() const {
    std::cout << "Physical Memory Size: " << total_size << " bytes\n";
}
