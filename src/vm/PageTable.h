#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <vector>
#include "PageTableEntry.h"

class PageTable {
public:
    std::vector<PageTableEntry> entries;

    PageTable(int num_pages) {
        entries.resize(num_pages);
    }
};

#endif
