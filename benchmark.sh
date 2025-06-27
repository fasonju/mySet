#!/bin/bash

first_args=("avl" "set")
second_args=("tiny" "medium" "large")
third_args=("random" "sorted" "reverse")

bin_dir="./build/bin"
log_dir="./logs"
massif_dir="./massif_logs"
# Create logs directory if it doesn't exist
mkdir -p "$log_dir"
mkdir -p "$massif_dir"

if [[ ! -d "$bin_dir" ]]; then
    echo "Error: Directory '$bin_dir' does not exist."
    exit 1
fi

for binary in "$bin_dir"/*; do
    if [[ -f "$binary" && -x "$binary" ]]; then
        binary_name=$(basename "$binary")
        for first in "${first_args[@]}"; do
            for second in "${second_args[@]}"; do
                for third in "${third_args[@]}"; do
                    cmd="$binary $first $second $third"

                    echo "Running: $cmd"

                    perf_log="$log_dir/${binary_name}_${first}_${second}_${third}_perf.log"
                    valgrind_log="$log_dir/${binary_name}_${first}_${second}_${third}_valgrind.log"

                    {
                        echo "======================="
                        echo "perf run: $cmd"
                        echo "-----------------------"
                        perf stat "$binary" "$first" "$second" "$third"
                        echo "======================="
                        echo
                    } >"$perf_log" 2>&1

                    {
                        echo "======================="
                        echo "valgrind run (ms_print): $cmd"
                        echo "-----------------------"

                        massif_out_file="$massif_dir/${binary_name}_${first}_${second}_${third}.massif.out"

                        # Run massif tool quietly and output to massif_out_file
                        valgrind --tool=massif --quiet --massif-out-file="$massif_out_file" "$binary" "$first" "$second" "$third" >/dev/null 2>&1

                        # Print massif output in human-readable form to valgrind log
                        ms_print "$massif_out_file"

                        echo "======================="
                        echo
                    } >"$valgrind_log" 2>&1

                done
            done
        done
    fi
done
echo "cleaning up..."
# After all runs complete:
rm -rf "$massif_dir"
