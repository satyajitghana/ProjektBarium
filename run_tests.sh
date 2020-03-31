#!/bin/bash

COLS=100

print_head () {
    print_line
    echo "$1\n"
}

print_line () {
    printf '=%.0s' $(seq $COLS)
    printf "\n"
}

start=$SECONDS

mkdir -p logs

print_head "performing full IR test"
./build/barium/barium test_files/test_all_ir.bar -v INFO --dump-ir 

print_head "performing branch parse test"
./build/barium/barium test_files/test_branch.bar -v INFO --parse-only

print_head "performing io test"
./build/barium/barium test_files/test_io.bar -v INFO --parse-only

print_head "performing area of shapes test"
./build/barium/barium test_files/test_shape_area.bar -v INFO --dump-ir

print_head "performing loops test"
./build/barium/barium test_files/test_loop.bar -v INFO --parse-only

print_head "performing arrays test"
./build/barium/barium test_files/test_array.bar -v INFO --parse-only

echo "test output stored in logs/"

duration=$(( SECONDS - start ))
echo "testing took $duration seconds\n"
