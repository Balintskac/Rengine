cmake_minimum_required(VERSION 3.16)
project(Rengine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add engine and sandbox as subprojects
add_subdirectory(Engine)
add_subdirectory(Sandbox)
