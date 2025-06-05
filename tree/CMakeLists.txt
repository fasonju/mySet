add_library(tree INTERFACE)

target_include_directories(tree
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
    # Include other third-party directories as needed
)
