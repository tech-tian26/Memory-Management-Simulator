#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include "PageTable.h"
#include <queue>
#include <string>

class VirtualMemory {
private:
    int virtual_size;
    int physical_size;
    int page_size;
    int num_frames;

    PageTable page_table;
    std::queue<int> fifo_queue;

    std::string policy;

    int page_hits = 0;
    int page_faults = 0;

    int findVictim();

public:
    VirtualMemory(int vSize, int pSize,int pSizePage, std::string repl);

    int access(int virtual_address);
    void stats() const;
};

#endif
