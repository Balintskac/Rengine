# Sandbox/CMakeLists.txt
cmake_minimum_required(VERSION 3.25)
project(Sandbox LANGUAGES CXX)

project(Sandbox)

file(GLOB_RECURSE SANDBOX_SOURCES "src/*.cpp")

add_executable(Sandbox ${SANDBOX_SOURCES})

# Link with Engine
target_link_libraries(Sandbox PRIVATE Engine)

# Include Engine headers
target_include_directories(Sandbox PRIVATE "${CMAKE_SOURCE_DIR}/Engine")

target_link_options(Sandbox PRIVATE -mconsole)

set_target_properties(Sandbox PROPERTIES
    LINK_FLAGS "-mconsole"
)
