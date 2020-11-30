cmake_minimum_required(VERSION 3.17)
project(Bosconian)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(${PROJECT_SOURCE_DIR}/glfw-3.3.2)

add_executable(Bosconian main.cpp)

target_link_libraries(Bosconian glfw)