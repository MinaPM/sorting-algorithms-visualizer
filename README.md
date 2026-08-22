## Build

This project uses CMake presets for both native and web (Emscripten) builds.

### Prerequisites

- CMake 3.28+
- [Ninja](https://ninja-build.org/) build system
- Git (to fetch emsdk for web builds)

### Initial setup

**Native:**
```bash
cmake --preset native
```

**Web (Emscripten):**

1. Install and activate Emscripten via the setup script. This clones emsdk into `emsdk/` at the project root and only needs to be run once per machine (or after a fresh clone):  

- **Linux/macOS**
```bash
   ./scripts/setup_emscripten.sh
```
- **Windows**
```ps1
   .\scripts\setup_emscripten.ps1
```

2. Configure using the preset. The `web` preset points `CMAKE_TOOLCHAIN_FILE` directly at `emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake`, so no `EMSDK` environment variable or `emcmake` wrapper is needed:
```bash
   cmake --preset web
```

If `emsdk/` hasn't been set up yet, this will fail with a message telling you to run the setup script first, instead of a raw toolchain error.

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
   cmake --preset web
```

**Native build:**

1. After code changes:
```bash
   cmake --build build-native
```
2. After `CMakeLists.txt` changes:
```bash
   cmake --preset native
```

### Notes

- `emsdk/` is gitignored; each machine/clone runs the setup script once to populate it locally.
- Assets are copied into the build output automatically (native), or preloaded into the virtual filesystem via `--preload-file` (web).
- Web build links SDL2 + SDL2_ttf via Emscripten's built-in port system (`-sUSE_SDL=2`, `-sUSE_SDL_TTF=2`) and enables `ALLOW_MEMORY_GROWTH`.
- SDL2 and SDL2_ttf are fetched automatically via CMake's `FetchContent`.
