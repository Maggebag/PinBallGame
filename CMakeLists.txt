cmake_minimum_required(VERSION 3.15)
project(pinballGame)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

add_subdirectory(src)

add_subdirectory(tests/manualTests)

add_executable(pinballGame "pinballGame.cpp")
target_link_libraries(pinballGame PUBLIC pinball-lib PRIVATE threepp::threepp ${BULLET_LIBRARIES})
file(COPY "${CMAKE_CURRENT_LIST_DIR}/data/textures" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/data)

