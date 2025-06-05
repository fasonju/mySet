set(SOURCES
  src/container.cpp
)

add_library(tree STATIC ${SOURCES})

target_include_directories(tree
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/internal/
    # Include other third-party directories as needed
)
