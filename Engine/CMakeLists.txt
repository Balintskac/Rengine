# Engine/CMakeLists.txt
project(Engine)

# Add all .cpp files from src/
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")

add_library(Engine STATIC ${ENGINE_SOURCES})

target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")
