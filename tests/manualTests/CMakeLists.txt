
add_executable(bulletTesting physicsTest.cpp)
target_link_libraries(bulletTesting PUBLIC pinball-lib PRIVATE threepp::threepp ${BULLET_LIBRARIES})