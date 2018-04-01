add_library(blavencia_lib
                components/cell.cpp
                components/map.cpp
                components/character.cpp
                components/projectile.cpp
                engine/collision.cpp
                engine/textures.cpp
                engine/controls.cpp)

set_target_properties(blavencia_lib PROPERTIES
    CXX_CLANG_TIDY "${DO_CLANG_TIDY}")

target_compile_definitions(blavencia_lib PUBLIC "DBG_DAT_PATH=${DBG_DAT_PATH}")

set_property(TARGET blavencia_lib PROPERTY POSITION_INDEPENDENT_CODE ON)
target_include_directories(blavencia_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(blavencia_lib PUBLIC ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

add_executable(blavencia main.cpp)
target_link_libraries(blavencia blavencia_lib)
