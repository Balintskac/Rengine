cmake_minimum_required(VERSION 3.25)
project(Rengine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# Ensure vcpkg exists inside vendor/
# ------------------------------------------------------------------------------
set(VCPKG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg")

# ------------------------------------------------------------------------------
# Set the vcpkg toolchain
# ------------------------------------------------------------------------------
# Tell CMake to use vcpkg (if not already provided via command line)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file"
    )
endif()


if(NOT EXISTS "${VCPKG_ROOT}/.git")
    message(STATUS "Cloning vcpkg...")
    execute_process(
        COMMAND git clone --recurse-submodules https://github.com/microsoft/vcpkg.git "${VCPKG_ROOT}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vendor"
    )
endif()

# Bootstrap vcpkg if not built yet
if(WIN32)
    set(VCPKG_BOOTSTRAP_SCRIPT "${VCPKG_ROOT}/bootstrap-vcpkg.bat")
else()
    set(VCPKG_BOOTSTRAP_SCRIPT "${VCPKG_ROOT}/bootstrap-vcpkg.sh")
endif()

if(NOT EXISTS "${VCPKG_ROOT}/vcpkg")
    message(STATUS "Bootstrapping vcpkg...")
    execute_process(
        COMMAND ${VCPKG_BOOTSTRAP_SCRIPT}
        WORKING_DIRECTORY "${VCPKG_ROOT}"
    )
endif()

# ------------------------------------------------------------------------------
# Install required packages (only if not installed yet)
# ------------------------------------------------------------------------------
set(VCPKG_PACKAGES
    glm
    spdlog
    glfw3
    glad
    assimp
    stb
    imgui
)

message(STATUS "Ensuring required vcpkg packages are installed...")

# Run 'vcpkg install' once for all packages
execute_process(
    COMMAND ${VCPKG_ROOT}/vcpkg install ${VCPKG_PACKAGES}
    WORKING_DIRECTORY ${VCPKG_ROOT}
)

message(STATUS "Using vcpkg from: ${VCPKG_ROOT}")
message(STATUS "asd" ${CMAKE_TOOLCHAIN_FILE})

# Add engine and sandbox as subprojects
add_subdirectory(Engine)
add_subdirectory(Sandbox)

# Optional fallback (if toolchain fails)
list(APPEND CMAKE_PREFIX_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/vcpkg/installed/x64-windows/share"
)
