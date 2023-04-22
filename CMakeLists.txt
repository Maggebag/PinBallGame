cmake_minimum_required(VERSION 3.15)
project(pinballGame)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

set(SRC pinballGame.cpp src/gameObjects.cpp)

add_subdirectory(tests/manualTests)

add_executable(pinballGame ${SRC})
target_link_libraries(pinballGame PRIVATE threepp::threepp ${BULLET_LIBRARIES})
target_include_directories(pinballGame PUBLIC include)
