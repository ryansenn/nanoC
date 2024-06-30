#!/bin/bash

# Function to run tests in a given directory
run_tests() {
    local test_dir=$1
    local total_tests=0
    local passed_tests=0

    # Loop through all .c files in the test directory
    for test_file in "$test_dir"/*.c; do
        total_tests=$((total_tests + 1))

        # Extract the expected AST from the comment at the beginning of the file
        expected_ast=$(sed -n '/\/\*/,/\*\//p' "$test_file" | grep -v '\/\*\|\*\/')

        # Determine the compiler command based on the directory name
        if [ "$test_dir" = "ast" ]; then
            actual_ast=$(../cmake-build-debug/compiler "$test_file" -ast 2>&1)
        else
            actual_ast=$(../cmake-build-debug/compiler "$test_file" 2>&1)
        fi

        # Compare the expected and actual AST
        if [ "$expected_ast" = "$actual_ast" ]; then
            passed_tests=$((passed_tests + 1))
        else
            echo "Test $(basename "$test_file" .c) failed"
        fi
    done

    # Print the summary
    echo "$passed_tests/$total_tests tests passed in $test_dir"
}

# List of directories to run tests in
test_dirs=("ast" "syntax_error")

# Loop through each directory in the list and run tests
for dir in "${test_dirs[@]}"; do
    run_tests "$dir"
done