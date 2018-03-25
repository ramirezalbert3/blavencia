add_library(blavencia_lib
                components/cell.cpp
                engine/collision.cpp
                engine/textures.cpp)

set_property(TARGET blavencia_lib PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(blavencia_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(blavencia_lib PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_executable(blavencia main.cpp)
target_link_libraries(blavencia blavencia_lib)

install(TARGETS blavencia
            DESTINATION bin)
