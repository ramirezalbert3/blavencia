find_package(GTest REQUIRED)

add_executable(utils_test utils_test.cpp)

target_include_directories(utils_test PRIVATE ${ROOT_SRC_DIR})
target_link_libraries(utils_test GTest::GTest GTest::Main)

GTEST_ADD_TESTS(utils_test "" AUTO)
