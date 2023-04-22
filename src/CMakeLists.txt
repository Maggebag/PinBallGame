
add_library(pinball-lib "GameObjects.cpp")
target_link_libraries(pinball-lib PRIVATE threepp::threepp)
target_include_directories(pinball-lib PUBLIC "${CMAKE_SOURCE_DIR}/include")
