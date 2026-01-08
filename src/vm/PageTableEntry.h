#ifndef PAGE_TABLE_ENTRY_H
#define PAGE_TABLE_ENTRY_H

struct PageTableEntry {
    bool valid = false;
    int frame = -1;

    // for replacement
    int age = 0;     // FIFO / LRU
};

#endif
