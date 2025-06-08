# Add source files
set(SOURCES
    src/benchmarking.cpp
)

add_executable(benchmark ${SOURCES})

# Link the libraries to the executable
target_link_libraries(benchmark PRIVATE
  container
)

target_include_directories(benchmark PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
