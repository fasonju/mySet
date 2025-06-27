#!/bin/bash

first_args=("avl" "set")
second_args=("tiny" "medium" "large")
third_args=("random" "sorted" "reverse")

bin_dir="./build/bin"

if [[ ! -d "$bin_dir" ]]; then
    echo "Error: Directory '$bin_dir' does not exist."
    exit 1
fi

for binary in "$bin_dir"/*; do
    if [[ -f "$binary" && -x "$binary" ]]; then
        for first in "${first_args[@]}"; do
            for second in "${second_args[@]}"; do
                for third in "${third_args[@]}"; do
                    echo "Running $binary with args: $first $second $third"
                    "$binary" "$first" "$second" "$third"
                done
            done
        done
    fi
done
