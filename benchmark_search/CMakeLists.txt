# Add source files
set(SOURCES
        src/benchmarking.cpp
)

add_executable(benchmark_search ${SOURCES})

# Link the libraries to the executable
target_link_libraries(benchmark_search PRIVATE
        container
        dataset
)

