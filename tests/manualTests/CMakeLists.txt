
set(SRC physicsTest.cpp ${CMAKE_SOURCE_DIR}/src/objectsLogic.cpp)

add_executable(bulletTesting ${SRC})
target_link_libraries(bulletTesting PRIVATE threepp::threepp ${BULLET_LIBRARIES})
target_include_directories(bulletTesting PUBLIC "${CMAKE_SOURCE_DIR}/include")
