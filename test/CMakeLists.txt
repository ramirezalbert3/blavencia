find_package(GTest REQUIRED)

function(generate_test test_name)

message(STATUS "Generating " ${test_name})
add_executable(${test_name} ${test_name}.cpp)

target_include_directories(${test_name} PRIVATE ${ROOT_SRC_DIR})
target_link_libraries(${test_name} GTest::GTest GTest::Main blavencia_lib)

add_test(NAME ${test_name}
            COMMAND ${test_name}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_files)
endfunction(generate_test)

generate_test(utils_test)
generate_test(components_test)
