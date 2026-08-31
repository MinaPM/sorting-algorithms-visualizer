cmake_minimum_required(VERSION 3.28)


# Catch a missing/misconfigured Emscripten toolchain before project() tries to load it
if(CMAKE_TOOLCHAIN_FILE AND CMAKE_TOOLCHAIN_FILE MATCHES "Emscripten\\.cmake" AND NOT EXISTS "${CMAKE_TOOLCHAIN_FILE}")
    message(FATAL_ERROR
        "Emscripten toolchain not found at: ${CMAKE_TOOLCHAIN_FILE}\n"
        "It looks like emsdk hasn't been installed for this project yet.\n"
        "Run the setup script first:\n"
        "  Linux/macOS: ./scripts/setup_emscripten.sh\n"
        "  Windows:     .\\scripts\\setup_emscripten.ps1\n"
    )
endif()


set(PROJECT_NAME "Sorting Algorithms")
set(EXECUTABLE_NAME "main")

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${EXECUTABLE_NAME} src/${EXECUTABLE_NAME}.cpp)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets"
        COMMENT "Copying assets directory to build output"
    )
endif()

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(WEB_SHELL_FILE "" CACHE FILEPATH "Optional Emscripten HTML shell file")
    target_compile_options(${EXECUTABLE_NAME} PRIVATE
        "-sUSE_SDL=2"
        "-sUSE_SDL_TTF=2"
                "-O3"

    )
    target_link_options(${EXECUTABLE_NAME} PRIVATE
        "-sUSE_SDL=2"
        "-sUSE_SDL_TTF=2"
        "-sALLOW_MEMORY_GROWTH=1"
        "--preload-file" "${CMAKE_CURRENT_SOURCE_DIR}/assets@assets"
                "-O3"

    )
    if(WEB_SHELL_FILE)
        target_link_options(${EXECUTABLE_NAME} PRIVATE
            "--shell-file" "${WEB_SHELL_FILE}"
        )
    endif()

else()
    include(FetchContent)
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

    if(NOT TARGET SDL2::SDL2)
        FetchContent_Declare(SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.32.8
            GIT_SHALLOW ON
        )
        FetchContent_MakeAvailable(SDL2)
    endif()

    if(NOT TARGET SDL2_ttf::SDL2_ttf AND NOT TARGET SDL2::SDL2_ttf AND NOT TARGET SDL2_ttf)
        message(STATUS "Fetching SDL2_ttf")
        FetchContent_Declare(SDL2_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG release-2.24.0
            GIT_SHALLOW ON
        )
        set(SDL2TTF_VENDORED ON CACHE BOOL "Use vendored FreeType" FORCE)
        FetchContent_MakeAvailable(SDL2_ttf)
    endif()

    target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        SDL2::SDL2main
        SDL2::SDL2
    )

    if(TARGET SDL2_ttf::SDL2_ttf)
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
    elseif(TARGET SDL2::SDL2_ttf)
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL2::SDL2_ttf)
    elseif(TARGET SDL2_ttf)
        target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL2_ttf)
    else()
        message(FATAL_ERROR "SDL2_ttf target was not created")
    endif()
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXECUTABLE_NAME})