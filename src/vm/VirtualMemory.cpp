#include "VirtualMemory.h"
#include <iostream>

VirtualMemory::VirtualMemory(int vSize, int pSize,
                             int pSizePage, std::string repl)
    : virtual_size(vSize),
      physical_size(pSize),
      page_size(pSizePage),
      policy(repl),
      page_table(vSize / pSizePage) {

    num_frames = physical_size / page_size;
}

int VirtualMemory::findVictim() {
    if (policy == "FIFO") {
        int v = fifo_queue.front();
        fifo_queue.pop();
        return v;
    }

    // LRU
    int victim = 0;
    int max_age = -1;
    for (int i = 0; i < page_table.entries.size(); i++) {
        if (page_table.entries[i].valid &&
            page_table.entries[i].age > max_age) {
            max_age = page_table.entries[i].age;
            victim = i;
        }
    }
    return victim;
}

int VirtualMemory::access(int vaddr) {
    int page = vaddr / page_size;
    int offset = vaddr % page_size;

    // Page hit
    if (page_table.entries[page].valid) {
        page_hits++;
        page_table.entries[page].age = 0;
        return page_table.entries[page].frame * page_size + offset;
    }

    // Page fault
    page_faults++;

    int frame;
    if (fifo_queue.size() < num_frames) {
        frame = fifo_queue.size();
    } else {
        int victim = findVictim();
        frame = page_table.entries[victim].frame;
        page_table.entries[victim].valid = false;
    }

    page_table.entries[page].valid = true;
    page_table.entries[page].frame = frame;
    page_table.entries[page].age = 0;

    fifo_queue.push(page);

    return frame * page_size + offset;
}

void VirtualMemory::stats() const {
    int total = page_hits + page_faults;
    double fault_rate = (total == 0) ? 0.0 :
        (double)page_faults / total;

    std::cout << "\n=== Virtual Memory Stats ===\n";
    std::cout << "Page Hits   : " << page_hits << "\n";
    std::cout << "Page Faults : " << page_faults << "\n";
    std::cout << "Fault Rate  : " << fault_rate * 100 << " %\n";
}
