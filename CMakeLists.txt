cmake_minimum_required(VERSION 3.20)

project(synth LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES main.cpp)
list(TRANSFORM SOURCES PREPEND "src/")

find_package(SDL2 REQUIRED CONFIG)

add_executable(synth ${SOURCES})
target_include_directories(synth PRIVATE "${CMAKE_SOURCE_DIR}/include" ${SDL2_INCLUDE_DIRS})
target_link_libraries(synth PRIVATE SDL2::SDL2)
