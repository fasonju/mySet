add_library(dataset INTERFACE)

target_include_directories(dataset
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
