add_library(blavencia_lib
                components/cell.cpp)

target_include_directories(blavencia_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(blavencia_lib PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_executable(blavencia main.cpp)
target_link_libraries(blavencia blavencia_lib)

set_target_properties(blavencia_lib
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties(blavencia
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
