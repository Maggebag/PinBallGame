cmake_minimum_required(VERSION 3.15)
project(testProject)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

add_executable(test main.cpp)
target_link_libraries(test PRIVATE threepp::threepp imgui::imgui ${BULLET_LIBRARIES} assimp::assimp)
