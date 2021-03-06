cmake_minimum_required(VERSION 3.17)
project(Bosconian)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw-3.3.2)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/openal-soft)

find_package(OpenGL REQUIRED)

add_executable(Bosconian main.cpp include/controller/Controller.h src/controller/Controller.cpp src/view/View.cpp include/view/View.h include/model/Player.h include/model/EnemyBase.h include/model/EnemyShip.h include/model/Mine.h include/model/Asteroid.h include/model/GameObject.h src/model/GameObject.cpp src/model/Player.cpp src/model/EnemyShip.cpp src/model/EnemyBase.cpp src/model/Mine.cpp src/model/Asteroid.cpp include/model/Model.h src/model/Model.cpp include/Utility.h include/model/BackgroundPixel.h src/model/BackgroundPixel.cpp include/model/ProjectilePlayer.h src/model/ProjectilePlayer.cpp include/model/EnemyBasePart.h src/model/EnemyBasePart.cpp include/model/ITypeMissile.h include/model/PTypeMissile.h include/model/ETypeMissile.h src/model/ITypeMissile.cpp src/model/PTypeMissile.cpp src/model/ETypeMissile.cpp include/model/SpyShip.h src/model/SpyShip.cpp include/model/Formation.h src/model/Formation.cpp src/audio/SoundControl.cpp include/audio/SoundControl.h src/audio/WAVLoader.cpp include/audio/WAVLoader.h src/audio/Sound.cpp include/audio/Sound.h)

target_link_libraries(Bosconian glfw OpenAL ${OPENGL_LIBRARIES})
