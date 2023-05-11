cmake_minimum_required(VERSION 3.15)
project(pinballGame)

set(CMAKE_CXX_STANDARD 17)

find_package(threepp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

add_subdirectory(src)

add_executable(pinballGame pinballGame.cpp)
target_link_libraries(pinballGame PUBLIC pinball-lib)
target_link_libraries(pinballGame PRIVATE threepp::threepp ${BULLET_LIBRARIES})
file(COPY "${CMAKE_CURRENT_LIST_DIR}/data/textures" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/data)

#Stuff for tests
include(FetchContent)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.13.8
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_subdirectory(tests)

