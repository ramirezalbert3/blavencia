find_package(GTest REQUIRED)

add_executable(utils_test utils_test.cpp)

target_include_directories(utils_test PRIVATE ${ROOT_SRC_DIR})
target_link_libraries(utils_test GTest::GTest GTest::Main)

add_test(NAME utils_test
            COMMAND utils_test
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_files)

set_target_properties(utils_test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
