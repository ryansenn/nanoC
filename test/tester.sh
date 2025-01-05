#!/bin/zsh

# ANSI color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Arrays to store results
declare -A results
total_passed=0
total_tests=0

# Function to run tests in a given directory
run_tests() {
    local test_dir=$1
    local dir_total_tests=0
    local dir_passed_tests=0
    local failed_tests=()

    # Loop through all .c files in the test directory
    for test_file in "$test_dir"/*.c; do
        dir_total_tests=$((dir_total_tests + 1))

        # Extract the expected AST from the comment at the beginning of the file
        expected_ast=$(sed -n '/\/\*/,/\*\//p' "$test_file" | grep -v '\/\*\|\*\/')

        # Determine the compiler command based on the directory name
        if [ "$test_dir" = "ast" ]; then
            actual_ast=$(../cmake-build-debug/compiler "$test_file" -ast 2>&1)
        elif [ "$test_dir" = "lexer" ]; then
            actual_ast=$(../cmake-build-debug/compiler "$test_file" -lexer 2>&1)
        else
            actual_ast=$(../cmake-build-debug/compiler "$test_file" 2>&1)
        fi

        # Compare the expected and actual AST
        if [ "$expected_ast" = "$actual_ast" ]; then
            dir_passed_tests=$((dir_passed_tests + 1))
        else
            failed_tests+=("$(basename "$test_file" .c)")
        fi
    done

    # Store results
    results[$test_dir]="$dir_passed_tests/$dir_total_tests"
    total_passed=$((total_passed + dir_passed_tests))
    total_tests=$((total_tests + dir_total_tests))

    # Display failed tests, if any
    if [ ${#failed_tests[@]} -ne 0 ]; then
        echo -e "${RED}Failed tests in $test_dir:${NC}"
        for test in "${failed_tests[@]}"; do
            echo "  - $test"
        done
        echo
    fi
}

# List of directories to run tests in
test_dirs=("lexer" "lexing_error" "ast" "parsing_error" "name_analysis" "type_analysis" "code_gen")

# Loop through each directory in the list and run tests
for dir in "${test_dirs[@]}"; do
    run_tests "$dir"
done

# After running all tests, print summary table and overall summary
echo -e "\nSummary Table:"
echo "--------------------"
printf "%-15s | %s\n" "Directory" "Passed/Total"
echo "--------------------"
for dir in "${test_dirs[@]}"; do
    IFS='/' read -r passed total <<< "${results[$dir]}"
    if [ "$passed" -eq "$total" ]; then
        printf "%-15s | ${GREEN}%s${NC}\n" "$dir" "${results[$dir]}"
    else
        printf "%-15s | ${RED}%s${NC}\n" "$dir" "${results[$dir]}"
    fi
done
echo "--------------------"

# Color the overall result
if [ "$total_passed" -eq "$total_tests" ]; then
    echo -e "\nOverall: ${GREEN}$total_passed/$total_tests${NC}"
else
    echo -e "\nOverall: ${RED}$total_passed/$total_tests${NC}"
fi