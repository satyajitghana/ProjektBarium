#!/bin/bash

echo -e "performing full IR test"
./build/barium/barium test_files/test_all_ir.bar -v INFO --dump-ir

echo -e "performing branch parse test"
./build/barium/barium test_files/test_branch.bar -v INFO --parse-only