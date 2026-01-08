#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <vector>
#include <cstddef>

class PhysicalMemory {
private:
    size_t total_size;
    std::vector<char> memory;

public:
    PhysicalMemory(size_t size);

    size_t getSize() const;
    void dump() const;
};

#endif
