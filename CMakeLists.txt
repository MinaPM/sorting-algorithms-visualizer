cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME "CMakeSFMLProject")
set(EXECUTABLE_NAME "main")

project(${PROJECT_NAME}  LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${EXECUTABLE_NAME} app/${EXECUTABLE_NAME}.cpp)
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE     
SFML::System      # Core functionality (vectors, time, threads)
    SFML::Window      # Window management, input
    SFML::Graphics    # 2D graphics, sprites, text
    SFML::Audio       # Sound and music
    SFML::Network     # Networking (TCP/UDP)
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXECUTABLE_NAME})