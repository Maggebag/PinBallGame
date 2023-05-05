
add_library(pinball-lib "utils.cpp")
target_link_libraries(pinball-lib PRIVATE threepp::threepp ${BULLET_LIBRARIES})
target_include_directories(pinball-lib PUBLIC "${CMAKE_SOURCE_DIR}/include" )
