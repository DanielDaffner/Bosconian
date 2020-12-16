cmake_minimum_required(VERSION 3.17)
project(Bosconian)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw-3.3.2)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

add_executable(Bosconian main.cpp include/controller/Controller.h src/controller/Controller.cpp src/view/View.cpp include/view/View.h include/model/Player.h include/model/EnemyBase.h include/model/EnemyShip.h include/model/Obstacle.h include/model/Mine.h include/model/Asteroid.h include/model/GameObject.h src/model/GameObject.cpp src/model/Player.cpp src/model/EnemyShip.cpp src/model/Obstacle.cpp src/model/EnemyBase.cpp src/model/Mine.cpp src/model/Asteroid.cpp include/model/Model.h src/model/Model.cpp include/Utility.h include/model/BackgroundPixel.h src/model/BackgroundPixel.cpp include/model/ProjectilePlayer.h src/model/ProjectilePlayer.cpp)

target_link_libraries(Bosconian glfw ${OPENGL_LIBRARIES})
