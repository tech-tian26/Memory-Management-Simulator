@echo off
echo ===============================
echo Building Memory Simulator
echo ===============================
echo.

echo Running compiler...
echo.

g++ -Isrc src/main_system.cpp src/system/MemorySystem.cpp src/vm/VirtualMemory.cpp src/cache/Cache.cpp src/allocator/FirstFit.cpp src/allocator/BestFit.cpp src/allocator/WorstFit.cpp src/buddy/BuddyAllocator.cpp -o memsim.exe

echo.
echo ===============================
echo Build finished. Exit code: %ERRORLEVEL%
echo ===============================

echo.
IF EXIST memsim.exe (
    echo ✅ memsim.exe was created successfully.
) ELSE (
    echo ❌ memsim.exe was NOT created.
)

echo.
pause
