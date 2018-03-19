add_executable(blavencia
                    main.cpp
                    utils/matrix.cpp)

target_include_directories(blavencia PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(blavencia ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

set_target_properties(blavencia
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
