cmake_minimum_required(VERSION 3.15)
project(testProject)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

add_executable(physicsTest physicsTest.cpp)
target_link_libraries(physicsTest PRIVATE threepp::threepp ${BULLET_LIBRARIES})
