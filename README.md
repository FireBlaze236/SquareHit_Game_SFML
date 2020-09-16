# SquareHit_Game_SFML

A Simple game built with SFML in C++.

## Build Instructions

### Windows

1. Download Visual Studio 2019, Make sure C++ development tools are selected in the installer options
2. Download the source code
3. Open `SFML1.sln` in Visual Studio
4. Build the project in Visual Studio. Make sure x86 is selected in Configuration options.
5. Copy over the dll files from `SFML1/` to the folder the exe was built. The game requires the exe files
to be in the same folder as the dlls.

### Other Platforms

The source code itself has no platform-dependent code so builds for other platforms can easily be created
using SFML's build instructions for said platforms.
