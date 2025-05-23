set(SOURCES
  src/array_avl_tree.cpp
  src/pointer_avl_tree.cpp
)

add_library(tree STATIC ${SOURCES})

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/
    # Include other third-party directories as needed
)
