# Memory Management Simulator

A complete Operating-System level **Memory Management Simulator** written in C++.

This project simulates:

- Dynamic Physical Memory Allocation
- First Fit, Best Fit, Worst Fit Allocators
- Buddy Memory Allocation System
- Virtual Memory with Paging (FIFO)
- Multilevel Cache (L1, L2)
- Cache Replacement Policies (FIFO / LRU)
- Fragmentation & Utilization Statistics
- Interactive CLI Interface

---

## Project Structure

```
Memory-Management-Simulator/
 ├ src/
 │   ├ allocator/
 │   ├ buddy/
 │   ├ cache/
 │   ├ memory/
 │   ├ system/
 │   ├ vm/
 │   └ main_system.cpp
 ├ Test-Artifacts/
 ├ docs/
 │   └ DesignDocument.pdf
 ├ demo/
 │   └ DemoVideo.mp4
 ├ build.bat
 ├ run.bat
 ├ Makefile
 ├ README.md
 └ .gitignore
```

---

## Build Instructions

### Windows (MinGW / g++)

Open **Command Prompt** in project root and run:

```
g++ -std=c++17 -Isrc src/main_system.cpp src/system/MemorySystem.cpp src/vm/VirtualMemory.cpp src/cache/Cache.cpp src/allocator/FirstFit.cpp src/allocator/BestFit.cpp src/allocator/WorstFit.cpp src/buddy/BuddyAllocator.cpp -o memsim.exe
```

Or simply double-click:

```
build.bat
```

---

### 🔹 Linux / MacOS

Make sure `g++` is installed, then run:

```
make
```

---

## ▶️ Running the Simulator

### Windows:

```
.\memsim.exe
```

### Linux / Mac:

```
./memsim
```

---

## 🖥️ CLI Commands

```
help
init memory <size>
set allocator <first|bestfit|worstfit|buddy>
malloc <size>
free <id>
dump memory
access <virtual_address>
stats
reset
exit
```

---

## Test Artifacts

Test workloads are provided in:

```
Test-Artifacts/
```

Example:

```
.\memsim.exe < Test-Artifacts/workload1_basic.txt
```

---

## Documentation

Full design document is available at:

```
Project_report.pdf
```

---

## Demo Video

Demo video is available in:

```
demo_vdo.mp4
```

---

## System Architecture

Memory Access Flow:

```
Virtual Address
      ↓
Page Table (Virtual Memory)
      ↓
Physical Address
      ↓
L1 Cache
      ↓
L2 Cache
      ↓
Physical Memory
```

---

## Features Implemented

- Physical Memory Simulator (Contiguous)
- First Fit / Best Fit / Worst Fit Allocation
- Buddy System Allocation
- Block Splitting & Coalescing
- Virtual Memory with Paging (FIFO)
- Multilevel Cache Simulation
- Cache Hits & Misses Tracking
- Fragmentation Statistics:
  - Internal Fragmentation
  - External Fragmentation
  - Utilization
  - Allocation Success Rate

---

## Author

**Gauri Bhardwaj**  

---

## License

This project is for academic and educational use only.
