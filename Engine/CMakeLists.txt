
cmake_minimum_required(VERSION 3.25)
project(Engine LANGUAGES CXX)
# Engine/CMakeLists.txt

# Add all .cpp files from src/
file(GLOB_RECURSE ENGINE_SOURCES  "Core/entryPoint.h" "Application/application.h" "Application/application.cpp" "rengine.h" )
add_library(Engine STATIC ${ENGINE_SOURCES})

find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

target_include_directories(Engine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<INSTALL_INTERFACE:includes>
        ${CMAKE_SOURCE_DIR}/Vendor/vcpkg/installed/x64-windows/include
)

target_link_libraries(Engine
    PRIVATE
        glfw
        glm::glm
        spdlog::spdlog
        assimp::assimp
        glad::glad
        imgui::imgui
)

target_compile_definitions(Engine PUBLIC RE_PLATFORM_WINDOWS)
