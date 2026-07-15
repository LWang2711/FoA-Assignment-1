#!/usr/bin/env bash

mkdir -p tests/test_results

is_failed=0

for test_number in 0 1 2 3
do
    actual="tests/test_results/test${test_number}_actual.txt"
    expected="tests/test_results/test${test_number}_expected.txt"

    ./build/a1 \
        < "inputs/test${test_number}.txt" \
        > "$actual"

    cat \
        expected_outputs/test${test_number}_level1_out.txt \
        expected_outputs/test${test_number}_level2_out.txt \
        expected_outputs/test${test_number}_level3_out.txt \
        expected_outputs/test${test_number}_level4_out.txt \
        > "${expected}"

    if diff -u "${expected}" "${actual}"
    then
        echo "PASS: test${test_number}"
    else
        echo "FAIL: test${test_number}"
        is_failed=1
    fi
done

exit "${is_failed}"