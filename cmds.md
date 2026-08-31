
## for wasm build

1. keep running this  
`emrun --no_browser --port 8080 .\build-web\bin\main.html`  
or  
`.\emsdk\upstream\emscripten\emrun.exe --no_browser --port 8080 .\build-web-publish\bin\main.html `

2. after code changes run  
`cmake --build build-web`

3. after CMakeLists changes run  
`emcmake cmake -S . -B build-web`



## for native build

1. after code changes run  
`cmake --build build-native`

2. after CMakeLists changes run  
`cmake -S . -B build-native`