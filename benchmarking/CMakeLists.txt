# Add source files
set(SOURCES
    src/benchmarking.cpp
)

add_executable(benchmark ${SOURCES})

# Link the libraries to the executable
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
  tree
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/internal/
)
