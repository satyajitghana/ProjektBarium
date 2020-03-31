#!/bin/bash

COLS=100

print_head () {
    print_line
    echo -e "$1\n"
}

print_line () {
    printf '=%.0s' $(seq $COLS)
    printf "\n"
}

start=$SECONDS

mkdir -p logs

print_head "performing full IR test"
./build/barium/barium test_files/test_all_ir.bar -v INFO --dump-ir |& tee logs/test_full_ir.txt

print_head "performing branch parse test"
./build/barium/barium test_files/test_branch.bar -v INFO --parse-only |& tee logs/test_branch.txt

print_head "performing io test"
./build/barium/barium test_files/test_io.bar -v INFO --parse-only |& tee logs/test_io.txt

print_head "performing area of shapes test"
./build/barium/barium test_files/test_shape_area.bar -v INFO --dump-ir |& tee logs/test_shape_area.txt

print_head "performing loops test"
./build/barium/barium test_files/test_loop.bar -v INFO --parse-only |& tee logs/test_loop.txt

print_head "performing arrays test"
./build/barium/barium test_files/test_array.bar -v INFO --parse-only |& tee logs/test_array.txt

echo -e "test output stored in logs/"

duration=$(( SECONDS - start ))
echo -e "testing took $duration seconds\n"
