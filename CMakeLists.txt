cmake_minimum_required(VERSION 3.17)
project(Bosconian)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw-3.3.2)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(Bosconian main.cpp include/controller/Controller.h src/controller/Controller.cpp src/view/View.cpp include/view/View.h App_data/pink_enemy_7_64.bmp)

target_link_libraries(Bosconian glfw ${OPENGL_LIBRARIES})
