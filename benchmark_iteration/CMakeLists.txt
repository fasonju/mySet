# Add source files
set(SOURCES
    src/benchmarking.cpp
)

add_executable(benchmark_iteration ${SOURCES})

# Link the libraries to the executable
target_link_libraries(benchmark_iteration PRIVATE
  container
  dataset
)

