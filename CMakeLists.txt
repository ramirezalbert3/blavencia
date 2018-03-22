cmake_minimum_required(VERSION 3.6)

project(blavencia VERSION 0.0.1)

enable_testing()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ROOT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(SFML 2.1 REQUIRED network audio graphics window system)

add_subdirectory(src)
add_subdirectory(test)

configure_file(dat/map1.csv ${CMAKE_BINARY_DIR}/bin)
