#!/bin/bash

cd Testing

total_tests=0
passed_tests=0

for c_file in test*.c; do
    total_tests=$((total_tests + 1))
    txt_file="${c_file%.c}.txt"

    if diff -q <(../compiler "$c_file") "$txt_file" > /dev/null; then
        passed_tests=$((passed_tests + 1))
    else
        echo "$c_file: failed"
    fi
done

echo "Passed tests: $passed_tests / $total_tests"

cd ..