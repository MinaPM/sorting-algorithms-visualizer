# Sorting Algorithms Visualizer — SFML Legacy (Archived)

> ⚠️ This branch is archived and no longer maintained.
> Active development has moved to `main`, which uses SDL2 for web (WASM) support.

## Why this was archived

This project originally used SFML for rendering, but was migrated to SDL2 to
support web deployment. SFML does not have solid support for compiling to
WebAssembly (via Emscripten), which made it a poor fit for running in the
browser. SDL2 has mature, well-tested Emscripten support, making it possible
to target the web as a platform without a major rendering rewrite.

## Status

- Archived: AUG-2026
- Last commit: tagged `sfml-final`
- Preserved for reference only — not receiving updates or bugfixes


## Build (for reference)

- **Project name:** Sorting Algorithms
- **SFML version:** 3.0.2 (fetched automatically via CMake's `FetchContent`, no manual install needed)
- **Build system:** CMake (3.28+)
- **Language standard:** C++17

### Steps

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

The executable (`main`) will be output to `build/bin/`. The `assets/` directory is automatically copied next to the built executable as a post-build step, so no manual asset copying is needed.

### Notes

- SFML is pulled directly from GitHub via `FetchContent` at configure time (no system-wide SFML install required, but requires internet access on first build).
- Linked SFML modules: System, Window, Graphics, Audio, Network.
- On Windows/Visual Studio, the executable is set as the startup project automatically.

## Active development

See the `main` branch for the current SDL-based version.
