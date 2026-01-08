#include <iostream>
#include <sstream>
#include <string>

#include "system/MemorySystem.h"
#include "allocator/FirstFit.h"
#include "allocator/BestFit.h"
#include "allocator/WorstFit.h"
#include "buddy/BuddyAllocator.h"

int main() {
    MemorySystem system;              // uses default constructor
    Allocator* allocator = nullptr;   // standalone allocator
    size_t memorySize = 0;

    std::string line;

    std::cout << "Memory Simulator CLI\n";
    std::cout << "Type 'help' for commands\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        /* EXIT */
        if (cmd == "exit") break;

        /* HELP */
        else if (cmd == "help") {
            std::cout <<
                "Commands:\n"
                "  init memory <size>\n"
                "  set allocator <first_fit|best_fit|worst_fit|buddy>\n"
                "  malloc <size>\n"
                "  free <block_id>\n"
                "  dump memory\n"
                "  stats\n"
                "  access <virtual_address>\n"
                "  reset\n"
                "  exit\n";
        }

        /* INIT MEMORY */
        else if (cmd == "init") {
            std::string what;
            ss >> what >> memorySize;

            if (what != "memory") {
                std::cout << "Usage: init memory <size>\n";
                continue;
            }

            delete allocator;
            allocator = new FirstFit(memorySize);

            std::cout << "Memory initialized with size "
                      << memorySize << " bytes\n";
        }

        /* SET ALLOCATOR */
        else if (cmd == "set") {
            std::string what, type;
            ss >> what >> type;

            if (what != "allocator" || memorySize == 0) {
                std::cout << "Initialize memory first\n";
                continue;
            }

            delete allocator;

            if (type == "first_fit")
                allocator = new FirstFit(memorySize);
            else if (type == "best_fit")
                allocator = new BestFit(memorySize);
            else if (type == "worst_fit")
                allocator = new WorstFit(memorySize);
            else if (type == "buddy")
                allocator = new BuddyAllocator(memorySize, 32);
            else {
                std::cout << "Unknown allocator\n";
                continue;
            }

            std::cout << "Allocator set to " << type << "\n";
        }

        /* MALLOC */
        else if (cmd == "malloc") {
            int size;
            ss >> size;

            if (!allocator) {
                std::cout << "Initialize memory first\n";
                continue;
            }

            int id = allocator->malloc(size);
            if (id == -1)
                std::cout << "Allocation failed\n";
            else
                std::cout << "Allocated block id=" << id << "\n";
        }

        /* FREE */
        else if (cmd == "free") {
            int id;
            ss >> id;

            if (!allocator) {
                std::cout << "Initialize memory first\n";
                continue;
            }

            allocator->freeBlock(id);
            std::cout << "Block " << id << " freed\n";
        }

        /* DUMP */
        else if (cmd == "dump") {
            std::string what;
            ss >> what;

            if (what == "memory" && allocator)
                allocator->dump();
            else
                std::cout << "Usage: dump memory\n";
        }

        /* STATS */
        else if (cmd == "stats") {
            if (allocator)
                allocator->stats();
            system.stats();   // VM + Cache stats
        }

        /* ACCESS */
        else if (cmd == "access") {
            int addr;
            ss >> addr;
            system.access(addr);
            std::cout << "Accessed virtual address " << addr << "\n";
        }

        /* RESET */
        else if (cmd == "reset") {
            delete allocator;
            allocator = nullptr;
            memorySize = 0;
            std::cout << "System reset\n";
        }

        else {
            std::cout << "Unknown command\n";
        }
    }

    delete allocator;
    return 0;
}
