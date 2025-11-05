# Sandbox/CMakeLists.txt
project(Sandbox)

file(GLOB_RECURSE SANDBOX_SOURCES "src/*.cpp")

add_executable(Sandbox ${SANDBOX_SOURCES})

# Link with Engine
target_link_libraries(Sandbox PRIVATE Engine)

# Include Engine headers
target_include_directories(Sandbox PRIVATE "${CMAKE_SOURCE_DIR}/Engine/includes")
