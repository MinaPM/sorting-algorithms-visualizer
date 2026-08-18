## Build

This project uses CMake presets for both native and web (Emscripten) builds.

### Prerequisites

- CMake 3.28+
- [Ninja](https://ninja-build.org/) build system
- For web builds: [Emscripten SDK (emsdk)](https://emscripten.org/docs/getting_started/downloads.html)

SDL2 and SDL2_ttf are fetched automatically via CMake's `FetchContent`, no manual install needed for native builds.

### Initial setup

**Native (Windows):**
```bash
cmake -S . -B build-native
```

**Web (Emscripten):**

1. Install and activate Emscripten via emsdk:
```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
```

2. Set up the environment. 

Currently, `EMSDK` is set as a global Windows environment variable pointing to the emsdk installation. (Planned: automate this via CMakeLists instead of relying on a global var.)

3. Configure:
```bash
   emcmake cmake -S . -B build-web
```

### Development workflow

**Web build:**

1. Start a local server and keep it running:
```bash
   emrun --no_browser --port 8080 .\build-web\bin\main.html
```
2. After code changes:
```bash
   cmake --build build-web
```
3. After `CMakeLists.txt` changes:
```bash
   emcmake cmake -S . -B build-web
```

**Native build:**

1. After code changes:
```bash
   cmake --build build-native
```
2. After `CMakeLists.txt` changes:
```bash
   cmake -S . -B build-native
```

### Notes

- Assets are copied into the build output automatically (native), or preloaded into the virtual filesystem via `--preload-file` (web).
- Web build links SDL2 + SDL2_ttf via Emscripten's built-in port system (`-sUSE_SDL=2`, `-sUSE_SDL_TTF=2`) and enables `ALLOW_MEMORY_GROWTH`.