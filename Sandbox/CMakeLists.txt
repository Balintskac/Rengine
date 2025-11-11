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

if (WIN32)
    set(VCPKG_BIN_PATH "${CMAKE_SOURCE_DIR}/Vendor/vcpkg/installed/x64-windows/bin")

    add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${VCPKG_BIN_PATH}"
        $<TARGET_FILE_DIR:Sandbox>)
    message(STATUS "✅ Copied all DLLs from vcpkg/bin to Sandbox output folder")
endif()