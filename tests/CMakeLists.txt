#Copied from threepp/tests with changes for this project
add_compile_definitions(DATA_FOLDER="${PROJECT_SOURCE_DIR}/data")

function(add_test_executable name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE pinball-lib threepp::threepp ${BULLET_LIBRARIES} Catch2::Catch2)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_test_executable(test_utils)
add_test_executable(test_gameLogic)
