
add_executable(bulletTesting physicsTest.cpp)
target_link_libraries(bulletTesting PRIVATE threepp::threepp ${BULLET_LIBRARIES})
